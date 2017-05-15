#include "Level.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include "ManualPlatform.h"

Level::Level()
{
	b2Vec2 gravity(0.0f, 9.8f);
	level_world = new b2World(gravity);
	my_contact_listener_ptr = new MyContactListener;
	level_world->SetContactListener(my_contact_listener_ptr);
}

Level::~Level()
{
	delete level_world;
	delete player;
	delete my_contact_listener_ptr;
}

std::list<Object>& Level::getUnchangeableObjectList()
{
	return unchangeable_objects;
}

std::list<Object>& Level::getChangeableObjectList()
{
	return changeable_objects;
}

std::vector<std::string>& Level::getImagesList()
{
	return images;
}

Player * Level::returnActivePlayer()
{
	return player;
}

void Level::tryToSwitchLever()
{
	for (auto it : storage.lever_list)
	{
		it->activate();
	}
}

void Level::update()
{
	level_world->Step(1.0f / 60.0f, 5, 5);
	for (auto it : storage.non_static_objects)
	{
		it->update();
	}
	for (auto it : storage.timer_list)
	{
		it->update();
	}
	for (auto it : storage.bridge_list)
	{
		it->update();
	}
}

bool Level::loadLevel(std::string filename)
{
	//load XML-file with level description
	tinyxml2::XMLDocument level_file;
	tinyxml2::XMLError error = level_file.LoadFile(filename.c_str());


	//Error verification
	if (error != 0)
	{
		std::cout << "Loading level \"" << filename << "\" failed." << std::endl; //////////////////////////////////////////////////////////////////////////////Exeptions!!!! Won't forget!!
		return false;
	}

	//Set map parameters
	tinyxml2::XMLElement *map = level_file.FirstChildElement("map");
	loadMap(map);


	//Add objects group
	loadObjects(map);
	return 1;
}

void Level::loadMap(tinyxml2::XMLElement *map)
{
	level_width = atof(map->Attribute("width"));
	level_height = atof(map->Attribute("height"));
	tile_width = atof(map->Attribute("tilewidth"));
	tile_height = atof(map->Attribute("tileheight"));

	//Add tileset image
	std::vector <TilesetImg> image_list;
	TilesetImg tg;
	tinyxml2::XMLElement *tileset = map->FirstChildElement("tileset");
	while (tileset)
	{
		tg.first_gid = atof(tileset->Attribute("firstgid"));
		tg.columns = atof(tileset->Attribute("columns"));
		tg.last_gid = tg.first_gid + atof(tileset->Attribute("tilecount")) - 1;
		tinyxml2::XMLElement *image;
		image = tileset->FirstChildElement("image");
		images.push_back(std::string(image->Attribute("source")));
		image_list.push_back(tg);
		tileset = tileset->NextSiblingElement("tileset");
	}

	//Add layers
	tinyxml2::XMLElement *layer = map->FirstChildElement("layer");
	while (layer)
	{
		//Read tiles in CSV
		tinyxml2::XMLElement *data = layer->FirstChildElement("data");
		const char* str = data->GetText();
		std::stringstream tempss;
		tempss << str;
		Object one_tile;
		int i, j, x = 0, y = 0;
		while (tempss >> i)
		{
			j = 0;
			while (j < image_list.size())
			{
				if (i >= image_list[j].first_gid && i <= image_list[j].last_gid)
				{
					int current_gid = i - image_list[j].first_gid;
					one_tile.number_in_image_list = j;
					one_tile.top = current_gid / image_list[j].columns * tile_height;
					one_tile.height = tile_height;
					one_tile.left = current_gid % image_list[j].columns * tile_width;
					one_tile.width = tile_width;
					one_tile.x = x * tile_width;
					one_tile.y = y * tile_height;
					unchangeable_objects.push_back(one_tile);
					break;
				}
				j++;
			}
			x++;
			if (x >= level_width)
			{
				x = 0;
				y++;
			}
			if (tempss.peek() == ',') tempss.ignore();
		}
		layer = layer->NextSiblingElement("layer");
	}
}

void Level::loadObjects(tinyxml2::XMLElement *map)
{
	tinyxml2::XMLElement *objectgroup = map->FirstChildElement("objectgroup");
	BodyType b_type;
	while (objectgroup)
	{
		if (std::string(objectgroup->Attribute("name")) == std::string("Static"))
		{
			b_type = BodyType::STATIC;
		}
		else if (std::string(objectgroup->Attribute("name")) == std::string("Kinematic"))
		{
			b_type = BodyType::KINEMATIC;
		}
		else if (std::string(objectgroup->Attribute("name")) == std::string("Dynamic"))
		{
			b_type = BodyType::DYNAMIC;
		}
		else if (std::string(objectgroup->Attribute("name")) == std::string("Sensors"))
		{
			//process sensors at the end
			objectgroup = objectgroup->NextSiblingElement("objectgroup");
			continue;
		}
		loadObject(objectgroup, b_type);
		objectgroup = objectgroup->NextSiblingElement("objectgroup");
	}
	//process sensors
	objectgroup = findAmongSiblings(map->FirstChildElement("objectgroup"), std::string("Sensors"));
	b_type = BodyType::SENSOR;
	loadObject(objectgroup, b_type);
}

void Level::loadObject(tinyxml2::XMLElement *objectgroup, BodyType b_type)
{
	Object tmp_obj;
	tmp_obj.top = 0;
	tmp_obj.left = 0;

	tinyxml2::XMLElement *object = objectgroup->FirstChildElement("object");

	while (object)
	{
		if (b_type == BodyType::KINEMATIC && !object->Attribute("type")) //////////////////////////////////////////crutch
		{
			object = object->NextSiblingElement("object");
			continue;
		}
		b2BodyDef body_def;
		b2PolygonShape shape;
		switch (b_type)
		{
		case BodyType::STATIC:
		case BodyType::SENSOR:
			body_def.type = b2_staticBody;
			break;
		case BodyType::KINEMATIC:
			body_def.type = b2_kinematicBody;
			break;
		case BodyType::DYNAMIC:
			body_def.type = b2_dynamicBody;
			break;
		}
		tmp_obj.rotation = 0;
		tmp_obj.width = atof(object->Attribute("width"));
		tmp_obj.height = atof(object->Attribute("height"));
		tmp_obj.x = atof(object->Attribute("x")) + tmp_obj.width / 2;
		tmp_obj.y = atof(object->Attribute("y")) + tmp_obj.height / 2;
		body_def.position.Set(tmp_obj.x / PIXEL_PER_METER, tmp_obj.y / PIXEL_PER_METER);
		shape.SetAsBox(tmp_obj.width / 2 / PIXEL_PER_METER, tmp_obj.height / 2 / PIXEL_PER_METER);
		if (b_type == BodyType::DYNAMIC)
		{
			double rotation = 0;
			if (object->Attribute("rotation") != nullptr)
			{
				rotation = atof(object->Attribute("rotation"));
			}
			body_def.angle = rotation * GRADTORAD;
			body_def.fixedRotation = false;
		}
		else
		{
			body_def.fixedRotation = true;
		}
		b2Body* body = level_world->CreateBody(&body_def);
		if (b_type != BodyType::STATIC && b_type != BodyType::SENSOR)
		{
			images.push_back(findAmongSiblings(object->FirstChildElement("properties")->FirstChildElement("property"), std::string("image"))->Attribute("value"));
			tmp_obj.number_in_image_list = images.size() - 1;

			b2FixtureDef fixture_def;
			fixture_def.shape = &shape;
			body->CreateFixture(&fixture_def);
			changeable_objects.push_back(tmp_obj);

			if (std::string(object->Attribute("type")) == std::string("player"))
			{
				player = new Player(8, level_width*tile_width, level_height*tile_height, 0.2, body, &changeable_objects.back(), 4);
				storage.non_static_objects.push_back(player);
			}
			else if (std::string(object->Attribute("type")) == std::string("platform"))
			{
				parsePlatform(object,objectgroup,body);
			}
			else if (std::string(object->Attribute("type")) == std::string("revolute_bridge"))
			{
				shape.SetAsBox(0.01, 0.01);
				parseBridge(object, body, &body_def, &tmp_obj);
			}
		}
		else
		{
			if (b_type == BodyType::SENSOR)
			{
				tinyxml2::XMLElement *stages = findAmongSiblings(object->FirstChildElement("properties")->FirstChildElement("property"), std::string("stages"));
				std::vector<Action> s_stages;
				if (stages != nullptr)
				{
					s_stages = sensorStagesParser(stringDelimiter(stages->Attribute("value")));
				}
				if (std::string(object->Attribute("type")) != std::string("timer"))
				{
					//create sensor or lever
					body_def.type = b2_dynamicBody;
					b2Body* body2 = level_world->CreateBody(&body_def);
					b2WeldJointDef wjd;
					wjd.Initialize(body, body2, b2Vec2(0, 0));
					level_world->CreateJoint(&wjd);
					b2FixtureDef fixture_def;
					fixture_def.shape = &shape;
					fixture_def.isSensor = true;
					body2->CreateFixture(&fixture_def);
					changeable_objects.push_front(tmp_obj);
					parseSensor(object, body2, s_stages);
				}
				else
				{
					//create timer
					parseTimer(object, s_stages);
					level_world->DestroyBody(body);
				}
			}
			else
			{
				body->CreateFixture(&shape, 1.0f);
			}
		}
		object = object->NextSiblingElement("object");
	}
}

//load platform definition
void Level::parsePlatform(tinyxml2::XMLElement * object, tinyxml2::XMLElement * objectgroup, b2Body * body)
{
	tinyxml2::XMLElement *properties = object->FirstChildElement("properties");
	bool is_rounded = 0;
	std::vector<std::pair<double, double>> traj_coord = buildTrajectory(objectgroup, findAmongSiblings(properties->FirstChildElement("property"), std::string("trajectory"))->Attribute("value"), &is_rounded);
	int speed = atoi(findAmongSiblings(properties->FirstChildElement("property"), std::string("speed"))->Attribute("value"));
	int steps = atoi(findAmongSiblings(properties->FirstChildElement("property"), std::string("steps"))->Attribute("value"));
	if (atoi(findAmongSiblings(properties->FirstChildElement("property"), std::string("is_auto"))->Attribute("value")))
	{
		//create auto platform
		Platform* platform;
		platform = new Platform(level_width*tile_width, level_height*tile_height, body, &changeable_objects.back(), traj_coord, speed, is_rounded, steps);
		storage.platform_list.push_back(platform);
		storage.non_static_objects.push_back(storage.platform_list.back());
	}
	else
	{
		//create platfrom controlling by sensor
		ManualPlatform* platform = new ManualPlatform(level_width*tile_width, level_height*tile_height, body, &changeable_objects.back(), traj_coord, speed, is_rounded, steps);
		storage.platform_list.push_back(platform);
		storage.non_static_objects.push_back(storage.platform_list.back());
		storage.future_observables.insert(std::pair<std::string, ManualSwitchObj*>(std::string(object->Attribute("name")), platform));
	}
}

//load sensor or lever defenition from xml-file
void Level::parseSensor(tinyxml2::XMLElement * object, b2Body * body, std::vector<Action> stages)
{
	tinyxml2::XMLElement *property = object->FirstChildElement("properties")->FirstChildElement("property");
	bool repeated_allowed = findAmongSiblings(property, std::string("repeat_allowed"))->BoolAttribute("value");
	tinyxml2::XMLElement *observables_property = findAmongSiblings(property, std::string("observables"));
	std::list<ManualSwitchObj*> observables;
	if (observables_property)
	{
		//add observable element
		std::vector<std::string> results = stringDelimiter(observables_property->Attribute("value"));
		for (auto it : results)
		{
			observables.push_back(storage.future_observables.find(it)->second);
		}
	}
	if (object->Attribute("type") == std::string("sensor"))
	{
		//create sensor
		bool is_keeping = findAmongSiblings(property, std::string("is_keeping"))->BoolAttribute("value");
		bool is_visible = findAmongSiblings(property, std::string("is_visible"))->BoolAttribute("value");
		Sensor* sensor;
		if (is_visible)
		{
			//visible sensor
			images.push_back(findAmongSiblings(property, std::string("image"))->Attribute("value"));
			changeable_objects.front().number_in_image_list = images.size() - 1;
			sensor = new VisibleSensor(observables, repeated_allowed, is_keeping, body, &changeable_objects.front(), stages);
		}
		else
		{
			//invisible sensor
			sensor = new Sensor(observables, repeated_allowed, is_keeping, body, stages);
			changeable_objects.pop_front();
		}
		storage.sensor_list.push_back(sensor);
	}
	else
	{
		//create lever - sensor switching by player
		images.push_back(findAmongSiblings(property, std::string("image"))->Attribute("value"));
		changeable_objects.front().number_in_image_list = images.size() - 1;
		Lever* lever = new Lever(observables, repeated_allowed, body, &changeable_objects.front(), &player, stages);
		storage.lever_list.push_back(lever);
	}
}

//load timer
void Level::parseTimer(tinyxml2::XMLElement * object, std::vector<Action> stages)
{
	tinyxml2::XMLElement *property = object->FirstChildElement("properties")->FirstChildElement("property");
	bool is_rounded = findAmongSiblings(property, std::string("is_rounded"))->BoolAttribute("value");
	tinyxml2::XMLElement *observables_property = findAmongSiblings(property, std::string("observables"));
	std::list<ManualSwitchObj*> observables;
	if (observables_property)
	{
		std::vector<std::string> results = stringDelimiter(observables_property->Attribute("value"));
		for (auto it : results)
		{
			observables.push_back(storage.future_observables.find(it)->second);
		}
	}
	//load timer stages in seconds
	std::vector<double> stages_duration;
	std::vector<std::string> results = stringDelimiter(findAmongSiblings(property, std::string("time_stages"))->Attribute("value"));
	for (auto it : results)
	{
		stages_duration.push_back(stod(it));
	}
	Timer* timer = new Timer(observables,stages_duration,is_rounded, stages);
	storage.timer_list.push_back(timer);
}

//load bridge
void Level::parseBridge(tinyxml2::XMLElement * object, b2Body * body, b2BodyDef* body_def, Object* tmp_obj)
{
	tinyxml2::XMLElement *property = object->FirstChildElement("properties")->FirstChildElement("property");
	std::string ancor = findAmongSiblings(property, "ancor")->Attribute("value");
	double tmpx = 0, tmpy = 0;
	std::string::size_type pos = ancor.find(','); // devide x & y coordinates
	bool x_left = stoi(ancor.substr(0, pos)); // in poliline point
	bool y_top = stoi(ancor.substr(pos + 1));
	if (x_left)
	{
		tmpx = 1;
	}
	else
	{
		tmpx = -1;
	}
	if (y_top)
	{
		tmpy = 1;
	}
	else
	{
		tmpy = -1;
	}
	tmpx = tmpx*tmp_obj->width / 2;
	tmpy = tmpy*tmp_obj->height / 2;

	body_def->position.Set((tmp_obj->x + tmpx) / PIXEL_PER_METER, (tmp_obj->y + tmpy) / PIXEL_PER_METER);
	body_def->type = b2_staticBody;
	b2Body* body2 = level_world->CreateBody(body_def);
	b2RevoluteJointDef rev_def;
	rev_def.bodyA = body;
	rev_def.bodyB = body2;

	rev_def.localAnchorA.Set(tmpx / PIXEL_PER_METER, tmpy / PIXEL_PER_METER);
	// establish a limit minimum corner
	rev_def.lowerAngle = std::stod(findAmongSiblings(property, "min_angle")->Attribute("value"))*GRADTORAD;
	rev_def.upperAngle = std::stod(findAmongSiblings(property, "max_angle")->Attribute("value"))*GRADTORAD;
	// include application of limits of corners
	rev_def.enableLimit = true;
	// expose the moment of force (motor power)
	rev_def.maxMotorTorque = body->GetGravityScale()*body->GetMass()*1000;
	// angular speed
	rev_def.motorSpeed = std::stod(findAmongSiblings(property, "speed")->Attribute("value"));
	b2RevoluteJoint* bridge_joint = (b2RevoluteJoint*)level_world->CreateJoint(&rev_def);
	double motor_speed = rev_def.motorSpeed;
	if (abs(rev_def.lowerAngle) > abs(rev_def.upperAngle))
	{
		motor_speed = -motor_speed;
	}
	//create bridge
	RevoluteBridge* rb = new RevoluteBridge(body, &changeable_objects.back(), bridge_joint, motor_speed);
	storage.bridge_list.push_back(rb);
	storage.future_observables.insert(std::pair<std::string, ManualSwitchObj*>(std::string(object->Attribute("name")), rb));
	//make initial action
	std::string init_state = findAmongSiblings(property, "init_state")->Attribute("value");
	if (init_state == std::string("up"))
	{
		rb->makeAction(Action::Up);
	}
	else if (init_state == std::string("down"))
	{
		rb->makeAction(Action::Down);
	}
	else
	{
		rb->makeAction(Action::Off);
	}
}

std::vector<Action> Level::sensorStagesParser(std::vector<std::string> stages)
{
	std::vector<Action> result;
	for (auto it : stages)
	{
		if (it == std::string("up"))
		{
			result.push_back(Action::Up);
		}
		else if (it == std::string("down"))
		{
			result.push_back(Action::Down);
		}
		else if (it == std::string("off"))
		{
			result.push_back(Action::Off);
		}
	}
	return result;
}

std::vector<std::string> Level::stringDelimiter(std::string init_str)
{
	std::istringstream iss(init_str);
	std::vector<std::string> results((std::istream_iterator<std::string>(iss)), {});
	return results;
}

//find an element in XML-file among similar
tinyxml2::XMLElement* Level::findAmongSiblings(tinyxml2::XMLElement* element, std::string name)
{
	while (element)
	{
		if (std::string(element->Attribute("name")) == name) return element;
		element = element->NextSiblingElement();
	}
	return nullptr;
}

//load trajectory for platform
std::vector<std::pair<double, double>> Level::buildTrajectory(tinyxml2::XMLElement * objectgroup, std::string trajectory_name, bool* is_rounded)
{
	tinyxml2::XMLElement *trajectory = findAmongSiblings(objectgroup->FirstChildElement("object"), trajectory_name); // build trajectory for platform 
	if (!trajectory)
	{
		throw "No trajectory for this platform"; /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	double init_x = atof(trajectory->Attribute("x"));
	double init_y = atof(trajectory->Attribute("y"));
	std::string polyline = trajectory->FirstChildElement("polyline")->Attribute("points");
	std::istringstream iss(polyline);
	std::vector<std::string> results((std::istream_iterator<std::string>(iss)), {});
	std::vector<std::pair<double, double>> coord_set;
	for (auto it : results)
	{
		std::string::size_type pos = it.find(','); // devide x & y coordinates
		double tmp_x = init_x + stoi(it.substr(0, pos)); // in poliline point
		double tmp_y = init_y + stoi(it.substr(pos + 1));
		std::pair<double, double> point(tmp_x / PIXEL_PER_METER, tmp_y / PIXEL_PER_METER);
		coord_set.push_back(point);
	}
	*is_rounded = atoi(findAmongSiblings(trajectory->FirstChildElement("properties")->FirstChildElement("property"), std::string("is_rounded"))->Attribute("value"));
	return coord_set;
}

