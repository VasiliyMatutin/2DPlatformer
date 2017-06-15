#include "Level.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include "ManualPlatform.h"

Level::Level(std::string prefix, std::string filename):
	strong_player(nullptr),
	dexterous_player(nullptr),
	prefix(prefix)
{
	b2Vec2 gravity(0.0f, 9.8f);
	level_world = new b2World(gravity);
	my_contact_listener_ptr = new MyContactListener;
	level_world->SetContactListener(my_contact_listener_ptr);
	storage.to_destroy_list = my_contact_listener_ptr->getToDestroyListPtr();
	loadLevel(filename);
	prev_step = std::chrono::system_clock::now();
}

Level::~Level()
{
	delete level_world;
	delete my_contact_listener_ptr;
}

void Level::smthHappend(Events what_happened)
{
	switch (what_happened)
	{
	case Events::LEFTBUTTON:
		player->moveLeft();
		break;
	case Events::RIGHTBUTTON:
		player->moveRight();
		break;
	case Events::UPBUTTON:
		player->jump();
		break;
	case Events::LEFTBUTTONRELEASED:
		player->stopLeft();
		break;
	case Events::RIGHTBUTTONRELEASED:
		player->stopRight();
		break;
	case Events::IBUTTON:
		tryToSwitchLever();
		break;
	case Events::PBUTTON:
		pickUpBox();
		break;
	case Events::CBUTTON:
		changeCurrentHero();
		break;
	case Events::MOUSECLICKED:
		throwBox(MouseClickCoordinates::x, MouseClickCoordinates::y);
		break;
	case Events::ESCBUTTON:
		re = ReturnEvents::OPENLOCALMENU;
		break;
	case Events::ENTERBUTTON:
		if (storage.final_list[0]->isReach() && storage.final_list[1]->isReach())
		{
			re = ReturnEvents::WIN;
		}
		break;
	}
}

bool Level::isDoubleView()
{
	return true;
}

void Level::getLayerSize(double * width, double * height)
{
	*width = level_width*tile_width;
	*height = level_height*tile_height;
}

void Level::getLayerCenter(double * x, double * y)
{
	player->returnCoordinates(x, y);
}

void Level::changeCurrentHero()
{
	if (strong_player_now && dexterous_player)
	{
		dexterous_player->setVel(strong_player->getVel());
		strong_player->justStop();
		player = dexterous_player;
		strong_player_now = false;
	}
	else if (!strong_player_now && strong_player)
	{
		strong_player->setVel(dexterous_player->getVel());
		dexterous_player->justStop();
		player = strong_player;
		strong_player_now = true;
	}
	for (int i = 0; i < 4; ++i)
	{
		UI_objects.pop_back();
	}
	for (int i = 0; i < 3; ++i)
	{
		UI_objects.push_back(player->returnUI()->getActiveBonusesPtr(i));
	}
	UI_objects.push_back(player->returnUI()->getHealthPtr());
	text_objects.clear();
	text_objects.push_back(player->returnUI()->getPlayerName());
	text_objects.push_back(player->returnUI()->getPlayerType());
}

void Level::tryToSwitchLever()
{
	for (auto it : storage.lever_list)
	{
		it->activate();
	}
}

void Level::pickUpBox()
{
	if (strong_player_now)
	{
		strong_player->tryToPickupBox();
	}
}

void Level::throwBox(double x, double y)
{
	if (strong_player_now)
	{
		strong_player->throwBox(x,y);
	}
}

void Level::countTime()
{
	std::chrono::time_point<std::chrono::system_clock> step = std::chrono::system_clock::now();
	level_time += step - prev_step;
	prev_step = step;
}

void Level::update()
{
	level_world->Step(1.0f / 60.0f, 3, 3);
	countTime();
	int n = 0;
	for (auto it : *storage.to_destroy_list)
	{
		it->destroy();
		n++;
	}
	for (int i = 0; i < n; i++)
	{
		storage.to_destroy_list->pop_front();
	}
	for (auto it : storage.non_static_objects)
	{
		it->update();
	}
	for (auto it : storage.timer_list)
	{
		it->update();
	}
	for (auto it : storage.danger_list)
	{
		it->update();
	}
}

void Level::repause()
{
	prev_step = std::chrono::system_clock::now();
}

std::string Level::fileExistsTest(const std::string& name)
{
	std::ifstream f(name.c_str());
	if (!f.good())
	{
		throw std::string("Loading image \"" + name + "\" failed. \n\t\t\t\t\t\t Couldn't find file");
	}
	return name;
}

void Level::loadLevel(std::string filename)
{
	//load XML-file with level description
	tinyxml2::XMLDocument level_file;
	tinyxml2::XMLError error = level_file.LoadFile(filename.c_str());


	//Error verification
	if (error != 0)
	{
		throw std::string("Loading level \"" + filename + "\" failed. \n\t\t\t\t\t\t Couldn't find file");
	}

	//Set map parameters
	tinyxml2::XMLElement *map = level_file.FirstChildElement("map");
	loadMap(map);


	//Add objects group
	loadObjects(map);

	if (strong_player == nullptr)
	{
		throw std::string("Strong player hasn't been found at this level");
	}
	else if (dexterous_player == nullptr)
	{
		throw std::string("Dexterous player hasn't been found at this level");
	}
	else if (storage.final_list[0] == nullptr)
	{
		throw std::string("Final point for strong player \n\t hasn't been found at this level");
	}
	else if (storage.final_list[1] == nullptr)
	{
		throw std::string("Final point for dexterous player \n\t hasn't been found at this level");
	}

	addUIToLevel();
}

void Level::loadMap(tinyxml2::XMLElement *map)
{
	level_width = atof(checkElementExistence(map->Attribute("width"),"Level has no width"));
	level_height = atof(checkElementExistence(map->Attribute("height"), "Level has no height"));
	tile_width = atof(checkElementExistence(map->Attribute("tilewidth"), "Unknown tile width"));
	tile_height = atof(checkElementExistence(map->Attribute("tileheight"), "Unknown tile height"));

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
		images.push_back(fileExistsTest(prefix+image->Attribute("source")));
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
		int i, j, x = 0, y = 0;
		while (tempss >> i)
		{
			j = 0;
			while (j < image_list.size())
			{
				if (i >= image_list[j].first_gid && i <= image_list[j].last_gid)
				{
					int current_gid = i - image_list[j].first_gid;
					Object one_tile{ j, current_gid / image_list[j].columns * tile_height, current_gid % image_list[j].columns * tile_width, x * tile_width, y * tile_height, tile_height, tile_width, 0, true, 255 };
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
		if (std::string(checkElementExistence(objectgroup->Attribute("name"), "No objectgroup name found")) == std::string("Static"))
		{
			b_type = BodyType::STATIC;
		}
		else if (std::string(checkElementExistence(objectgroup->Attribute("name"), "No objectgroup name found")) == std::string("Kinematic"))
		{
			b_type = BodyType::KINEMATIC;
		}
		else if (std::string(checkElementExistence(objectgroup->Attribute("name"), "No objectgroup name found")) == std::string("Dynamic"))
		{
			b_type = BodyType::DYNAMIC;
		}
		else if (std::string(checkElementExistence(objectgroup->Attribute("name"), "No objectgroup name found")) == std::string("Sensors") || std::string(checkElementExistence(objectgroup->Attribute("name"), "No objectgroup name found")) == std::string("Dangers"))
		{
			//process sensors at the end
			objectgroup = objectgroup->NextSiblingElement("objectgroup");
			continue;
		}
		else
		{
			throw std::string("Incorrect objectgroup name");
		}
		loadObject(objectgroup, b_type);
		objectgroup = objectgroup->NextSiblingElement("objectgroup");
	}
	//process sensors
	objectgroup = findAmongSiblings(map->FirstChildElement("objectgroup"), std::string("Sensors"));
	b_type = BodyType::SENSOR;
	loadObject(objectgroup, b_type);
	objectgroup = findAmongSiblings(map->FirstChildElement("objectgroup"), std::string("Dangers"));
	b_type = BodyType::DANGER;
	loadObject(objectgroup, b_type);
}

void Level::loadObject(tinyxml2::XMLElement *objectgroup, BodyType b_type)
{
	if (objectgroup == nullptr)
	{
		return;
	}
	Object tmp_obj;
	tmp_obj.top = 0;
	tmp_obj.left = 0;

	tinyxml2::XMLElement *object = objectgroup->FirstChildElement("object");

	while (object)
	{
		if (b_type == BodyType::KINEMATIC && !object->Attribute("type")) 
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
		case BodyType::DANGER:
		case BodyType::KINEMATIC:
			body_def.type = b2_kinematicBody;
			break;
		case BodyType::DYNAMIC:
			body_def.type = b2_dynamicBody;
			break;
		}
		tmp_obj.rotation = 0;
		tmp_obj.width = 0;
		tmp_obj.height = 0;
		if (object->Attribute("width") && object->Attribute("height"))
		{
			tmp_obj.width = atof(object->Attribute("width"));
			tmp_obj.height = atof(object->Attribute("height"));
		}
		tmp_obj.x = atof(object->Attribute("x")) + tmp_obj.width / 2;
		tmp_obj.y = atof(object->Attribute("y")) + tmp_obj.height / 2;
		tmp_obj.transparensy = 255;
		body_def.position.Set(tmp_obj.x / PIXEL_PER_METER, tmp_obj.y / PIXEL_PER_METER);
		shape.SetAsBox(tmp_obj.width / 2 / PIXEL_PER_METER, tmp_obj.height / 2 / PIXEL_PER_METER);
		body_def.fixedRotation = true;
		b2Body* body = level_world->CreateBody(&body_def);

		b2FixtureDef fixture_def;
		fixture_def.filter.categoryBits = OTHERS;
		fixture_def.filter.maskBits = MASK_OTHERS;

		switch (b_type)
		{
		case BodyType::STATIC:
		{
			fixture_def.shape = &shape;
			fixture_def.friction = 0.3f;
			body->CreateFixture(&fixture_def);
			if (object->Attribute("type"))
			{
				if (object->Attribute("type") == std::string("danger"))
				{
					body->SetUserData(&body);
				}
			}
		}
		break;
		case BodyType::SENSOR:
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
		break;
		case BodyType::DYNAMIC:
		{
			double rotation = 0;
			if (object->Attribute("rotation") != nullptr)
			{
				rotation = atof(object->Attribute("rotation"));
			}
			body->SetTransform(body->GetPosition(), rotation * GRADTORAD);
			body->SetFixedRotation(false);
		}
		case BodyType::KINEMATIC:
		{
			images.push_back(fileExistsTest(prefix + (checkElementExistence(findAmongSiblings(object->FirstChildElement("properties")->FirstChildElement("property"), std::string("image")), "No image was found for one of the kinematic object")->Attribute("value"))));
			tmp_obj.number_in_image_list = images.size() - 1;

			fixture_def.shape = &shape;
			fixture_def.friction = 0.3f;
			body->CreateFixture(&fixture_def);
			changeable_objects.push_back(tmp_obj);

			if (object->Attribute("type") == nullptr)
			{
				body->GetFixtureList()->SetDensity(std::stod(checkElementExistence(findAmongSiblings(object->FirstChildElement("properties")->FirstChildElement("property"), std::string("density")), "No density for box was found")->Attribute("value")));
				body->GetFixtureList()->SetFriction(2.0f);
				body->ResetMassData();
				NonStaticObj* nso = new NonStaticObj(body, &changeable_objects.back(), ObjectType::BOX);
				body->SetUserData(nso);
				storage.non_static_objects.push_back(nso);
				break;
			}

			if (std::string(object->Attribute("type")) == std::string("player"))
			{
				int health = std::stoi(checkElementExistence(findAmongSiblings(object->FirstChildElement("properties")->FirstChildElement("property"), std::string("health")), "No health description for player was found")->Attribute("value"));
				if (std::string(object->Attribute("name")) == std::string("strong_player"))
				{
					strong_player = new StrongPlayer(level_width*tile_width, level_height*tile_height, body, &changeable_objects.back(), health, &re);
					player = strong_player;
					strong_player_now = true;
				}
				else
				{
					dexterous_player = new DexterousPlayer(level_width*tile_width, level_height*tile_height, body, &changeable_objects.back(), health, &re);
					player = dexterous_player;
					strong_player_now = false;
				}
				storage.non_static_objects.push_back(player);
				PlayerSensor* ps = new PlayerSensor(player, createBorderSensor(body, &changeable_objects.back(), Sides::DOWN));
				storage.players_sensors_list.push_back(ps);
			}
			else if (std::string(object->Attribute("type")) == std::string("platform"))
			{
				parsePlatform(object, objectgroup, body);
			}
			else if (object->Attribute("type") == std::string("bonus"))
			{
				BonusType bt;
				double time = 0;
				std::string string_bt = checkElementExistence(findAmongSiblings(object->FirstChildElement("properties")->FirstChildElement("property"), std::string("type")), "No bonus type was found")->Attribute("value");
				if (string_bt == "health")
				{
					bt = BonusType::HEALTH;
				}
				else if (string_bt == "speed")
				{
					bt = BonusType::RUN;
					time = std::stod(checkElementExistence(findAmongSiblings(object->FirstChildElement("properties")->FirstChildElement("property"), std::string("time")), "No time duration for bonus was found")->Attribute("value"));
				}
				else if (string_bt == "jump")
				{
					bt = BonusType::JUMP;
					time = std::stod(checkElementExistence(findAmongSiblings(object->FirstChildElement("properties")->FirstChildElement("property"), std::string("time")), "No time duration for bonus is found")->Attribute("value"));
				}
				double modificator = std::stod(checkElementExistence(findAmongSiblings(object->FirstChildElement("properties")->FirstChildElement("property"), std::string("modificator")), "No bonus modificator is found")->Attribute("value"));
				Bonus* bn = new Bonus(modificator, time, bt, &player, body, &changeable_objects.back(), &level_time);
			}
			else if (std::string(object->Attribute("type")) == std::string("revolute_bridge") || std::string(object->Attribute("type")) == std::string("partition"))
			{
				parseBridge(object, body, &body_def, &tmp_obj);
			}
		}
		break;
		case BodyType::DANGER:
		{
			fixture_def.shape = &shape;
			body->CreateFixture(&fixture_def);
			parseDangerObject(object, body, &tmp_obj, objectgroup);
		}
		break;
		}
		object = object->NextSiblingElement("object");
	}
}

//load platform definition
void Level::parsePlatform(tinyxml2::XMLElement * object, tinyxml2::XMLElement * objectgroup, b2Body * body)
{
	tinyxml2::XMLElement *properties = object->FirstChildElement("properties");
	bool is_rounded = 0;
	std::vector<std::pair<double, double>> traj_coord = buildTrajectory(objectgroup, checkElementExistence(findAmongSiblings(properties->FirstChildElement("property"), std::string("trajectory")), "No trajectory for platform was found")->Attribute("value"), &is_rounded);
	int speed = atoi(checkElementExistence(findAmongSiblings(properties->FirstChildElement("property"), std::string("speed")),"No speed for platform was found")->Attribute("value"));
	int steps = atoi(checkElementExistence(findAmongSiblings(properties->FirstChildElement("property"), std::string("steps")),"No steps for platdorm was found")->Attribute("value"));
	if (checkElementExistence(findAmongSiblings(properties->FirstChildElement("property"), std::string("is_auto")),"Unknown automatic platform or no")->BoolAttribute("value"))
	{
		//create auto platform
		Platform* platform;
		platform = new Platform(level_width*tile_width, level_height*tile_height, body, &changeable_objects.back(), traj_coord, speed, is_rounded, steps);
		storage.non_static_objects.push_back(platform);
	}
	else
	{
		//create platfrom controlling by sensor
		ManualPlatform* platform = new ManualPlatform(level_width*tile_width, level_height*tile_height, body, &changeable_objects.back(), traj_coord, speed, is_rounded, steps);
		storage.non_static_objects.push_back(platform);
		storage.future_observables.insert(std::pair<std::string, ManualSwitchObj*>(std::string(checkElementExistence(object->Attribute("name"),"Platform has no name")), platform));
	}
}

//load sensor or lever defenition from xml-file
void Level::parseSensor(tinyxml2::XMLElement * object, b2Body * body, std::vector<Action> stages)
{
	tinyxml2::XMLElement *property = object->FirstChildElement("properties")->FirstChildElement("property");
	checkElementExistence(object->Attribute("type"), "Incorrect sensor type");
	if (object->Attribute("type") == std::string("final"))
	{
		images.push_back(fileExistsTest(prefix + (checkElementExistence(findAmongSiblings(property, std::string("image")),"No image for final point was found")->Attribute("value"))));
		changeable_objects.front().number_in_image_list = images.size() - 1;
		if (checkElementExistence(findAmongSiblings(property, std::string("player")), "No player type for final point was found")->Attribute("value") == std::string("strong"))
		{
			Final* final = new Final(body, true);
			storage.final_list[0] = final;
		} 
		else
		{
			Final* final = new Final(body, false);
			storage.final_list[1] = final;
		}
		return;
	}
	bool repeated_allowed = checkElementExistence(findAmongSiblings(property, std::string("repeat_allowed")), "Can't define repeat modificator for sensor")->BoolAttribute("value");
	tinyxml2::XMLElement *observables_property = findAmongSiblings(property, std::string("observables"));
	std::list<ManualSwitchObj*> observables;
	if (observables_property)
	{
		//add observable element
		std::vector<std::string> results = stringDelimiter(observables_property->Attribute("value"));
		for (auto it : results)
		{
			auto obser = storage.future_observables.find(it);
			if (obser == storage.future_observables.end())
			{
				throw std::string("Observable object for sensor wasn't found");
			}
			observables.push_back(obser->second);
		}
	}
	if (object->Attribute("type") == std::string("sensor"))
	{
		//create sensor
		bool is_keeping = checkElementExistence(findAmongSiblings(property, std::string("is_keeping")),"Can't define keep modificator for sensor")->BoolAttribute("value");
		bool is_visible = checkElementExistence(findAmongSiblings(property, std::string("is_visible")), "Can't define visibility modificator for sensor")->BoolAttribute("value");
		Sensor* sensor;
		if (is_visible)
		{
			//visible sensor
			images.push_back(fileExistsTest(prefix + (checkElementExistence(findAmongSiblings(property, std::string("image")),"No image for sensor was found")->Attribute("value"))));
			changeable_objects.front().number_in_image_list = images.size() - 1;
			sensor = new VisibleSensor(observables, repeated_allowed, is_keeping, body, &changeable_objects.front(), stages);
		}
		else
		{
			//invisible sensor
			sensor = new Sensor(observables, repeated_allowed, is_keeping, body, stages);
			changeable_objects.pop_front();
		}
	}
	else if (object->Attribute("type") == std::string("lever"))
	{
		//create lever - sensor switching by player
		images.push_back(fileExistsTest(prefix + (checkElementExistence(findAmongSiblings(property, std::string("image")), "No image for lever was found")->Attribute("value"))));
		changeable_objects.front().number_in_image_list = images.size() - 1;
		Lever* lever = new Lever(observables, repeated_allowed, body, &changeable_objects.front(), &player, stages);
		storage.lever_list.push_back(lever);
	}
}

//load timer
void Level::parseTimer(tinyxml2::XMLElement * object, std::vector<Action> stages)
{
	tinyxml2::XMLElement *property = object->FirstChildElement("properties")->FirstChildElement("property");
	bool is_rounded = checkElementExistence(findAmongSiblings(property, std::string("is_rounded")), "Can't define round modificator for timer")->BoolAttribute("value");
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
	Timer* timer = new Timer(observables, stages_duration, is_rounded, stages, &level_time);
	storage.timer_list.push_back(timer);
}

//load bridge or partition
void Level::parseBridge(tinyxml2::XMLElement * object, b2Body * body, b2BodyDef* body_def, Object* tmp_obj)
{
	body->GetFixtureList()->SetDensity(20.0f);
	body->ResetMassData();
	body->SetFixedRotation(false);

	tinyxml2::XMLElement *property = object->FirstChildElement("properties")->FirstChildElement("property");
	std::string ancor = checkElementExistence(findAmongSiblings(property, "ancor"), "Can't find ancor value for partition or bridge")->Attribute("value");
	std::string::size_type pos = ancor.find(' '); // devide x & y coordinates
	double tmpx = stod(ancor.substr(0, pos))*tmp_obj->width / 2;
	double tmpy = stod(ancor.substr(pos + 1))*tmp_obj->height / 2;
	body_def->position.Set((tmp_obj->x + tmpx) / PIXEL_PER_METER, (tmp_obj->y + tmpy) / PIXEL_PER_METER);
	body_def->type = b2_staticBody;
	b2Body* body2 = level_world->CreateBody(body_def);
	b2RevoluteJointDef rev_def;
	rev_def.bodyA = body;
	rev_def.bodyB = body2;

	rev_def.localAnchorA.Set(tmpx / PIXEL_PER_METER, tmpy / PIXEL_PER_METER);
	// establish a limit minimum corner
	rev_def.lowerAngle = std::stod(checkElementExistence(findAmongSiblings(property, "min_angle"),"Can't find min_angle for bridge or partition")->Attribute("value"));
	rev_def.upperAngle = std::stod(checkElementExistence(findAmongSiblings(property, "max_angle"), "Can't find max_angle for bridge or partition")->Attribute("value"));
	rev_def.enableLimit = true;
	if (rev_def.lowerAngle == 0 && rev_def.upperAngle == 360)
	{
		rev_def.enableLimit = false;
	}
	rev_def.lowerAngle *= GRADTORAD;
	rev_def.upperAngle *= GRADTORAD;
	// include application of limits of corners
	b2RevoluteJoint* bridge_joint = (b2RevoluteJoint*)level_world->CreateJoint(&rev_def);

	if (std::string(object->Attribute("type")) == std::string("revolute_bridge"))
	{
		// expose the moment of force (motor power)
		bridge_joint->SetMaxMotorTorque(body->GetGravityScale()*body->GetMass() * 1000);
		// angular speed
		double motor_speed = std::stod(checkElementExistence(findAmongSiblings(property, "speed"), "Can't find speed for bridge")->Attribute("value"));
		if (abs(rev_def.lowerAngle) > abs(rev_def.upperAngle))
		{
			motor_speed = -motor_speed;
		}
		//create bridge
		RevoluteBridge* rb = new RevoluteBridge(body, &changeable_objects.back(), bridge_joint, motor_speed);
		storage.non_static_objects.push_back(rb);
		storage.future_observables.insert(std::pair<std::string, ManualSwitchObj*>(std::string(object->Attribute("name")), rb));
		//make initial action
		std::string init_state = checkElementExistence(findAmongSiblings(property, "init_state"), "Can't find init_state for bridge")->Attribute("value");
		if (init_state == std::string("up"))
		{
			rb->makeAction(Action::UP);
		}
		else if (init_state == std::string("down"))
		{
			rb->makeAction(Action::DOWN);
		}
		else
		{
			rb->makeAction(Action::OFF);
		}
	}
	else
	{
		NonStaticObj* partiton = new NonStaticObj(body, &changeable_objects.back(), ObjectType::BRIDGE_PARTITION);
		storage.non_static_objects.push_back(partiton);
		body->SetUserData(partiton);
	}
}

void Level::parseDangerObject(tinyxml2::XMLElement * object, b2Body * body, Object* tmp_obj, tinyxml2::XMLElement * objectgroup)
{
	tinyxml2::XMLElement *property = object->FirstChildElement("properties")->FirstChildElement("property");
	double damage = std::stod(checkElementExistence(findAmongSiblings(property, "damage"), "Damage modificator for danger object wasn't found")->Attribute("value"));

	images.push_back(fileExistsTest(prefix + (checkElementExistence(findAmongSiblings(object->FirstChildElement("properties")->FirstChildElement("property"), std::string("image")),"Can't find image for danger object")->Attribute("value"))));

	if (checkElementExistence(findAmongSiblings(property, "is_movable"),"Can't define movable modificator for danger object")->BoolAttribute("value"))
	{
		level_world->DestroyBody(body);
		ManualPlatform* man_platf = static_cast<ManualPlatform*>(storage.future_observables.find(checkElementExistence(findAmongSiblings(property, "stick_platform"), "Stick platdorm wasn't found")->Attribute("value"))->second);
		body = man_platf->getBody();
		tmp_obj = man_platf->getObject();
		tmp_obj->number_in_image_list = images.size() - 1;
	}
	else
	{
		tmp_obj->number_in_image_list = images.size() - 1;
		changeable_objects.push_back(*tmp_obj);
	}

	std::list<b2Body*> boundaries;

	if (checkElementExistence(findAmongSiblings(property, "left_side"),"The left_side midificator wasn't found")->BoolAttribute("value"))
	{
		boundaries.push_back(createBorderSensor(body, &changeable_objects.back(), Sides::LEFT));
	}
	if (checkElementExistence(findAmongSiblings(property, "up_side"), "The up_side midificator wasn't found")->BoolAttribute("value"))
	{
		boundaries.push_back(createBorderSensor(body, &changeable_objects.back(), Sides::UP));
	}
	if (checkElementExistence(findAmongSiblings(property, "right_side"), "The right_side midificator wasn't found")->BoolAttribute("value"))
	{
		boundaries.push_back(createBorderSensor(body, &changeable_objects.back(), Sides::RIGHT));
	}
	if (checkElementExistence(findAmongSiblings(property, "down_side"), "The down_side midificator wasn't found")->BoolAttribute("value"))
	{
		boundaries.push_back(createBorderSensor(body, &changeable_objects.back(), Sides::DOWN));
	}
	DangerObject* d_obj = new DangerObject(boundaries, damage, body, &level_time);
	storage.danger_list.push_back(d_obj);
}

b2Body* Level::createBorderSensor(b2Body * body, Object * tmp_obj, Sides side)
{
	b2BodyDef body_def;
	body_def.type = b2_dynamicBody;
	body_def.position = b2Vec2(0, 0);
	b2WeldJointDef wjd;
	wjd.bodyA = body;
	b2FixtureDef fixture_def;
	fixture_def.density = 0.01f;
	fixture_def.isSensor = true;
	b2PolygonShape shape;

	double tmpx = tmp_obj->width / 2 / PIXEL_PER_METER;
	double tmpy = tmp_obj->height / 2 / PIXEL_PER_METER;

	switch (side)
	{
		case Sides::DOWN:
		{
			wjd.localAnchorA.Set(0, tmpy);
			shape.SetAsBox(tmpx - 0.01, 0.01);
			break;
		}
		case Sides::UP:
		{
			wjd.localAnchorA.Set(0, -tmpy);
			shape.SetAsBox(tmpx - 0.01, 0.01);
			break;
		}
		case Sides::LEFT:
		{
			wjd.localAnchorA.Set(-tmpx, 0);
			shape.SetAsBox(0.01, tmpy - 0.01);
			break;
		}
		case Sides::RIGHT:
		{
			wjd.localAnchorA.Set(tmpx, 0);
			shape.SetAsBox(0.01, tmpy - 0.01);
			break;
		}
	}
	fixture_def.shape = &shape;
	b2Body* body2 = level_world->CreateBody(&body_def);
	body2->CreateFixture(&fixture_def);
	wjd.bodyB = body2;
	level_world->CreateJoint(&wjd);
	return body2;
}

void Level::addUIToLevel()
{
	images.push_back("Images/Level/board.png");
	Object board{images.size() - 1, 0, 0, 0, 0, 110, 140, 0, true, 255};
	static_UI_objects.push_back(board);
	UI_objects.push_back(&static_UI_objects.back());
	images.push_back("Images/Level/bar.png");
	Object bar{ images.size() - 1, 0, 0, 5, 46, 24, 128, 0, true, 255};
	static_UI_objects.push_back(bar);
	UI_objects.push_back(&static_UI_objects.back());
	images.push_back("Images/Level/health_line.png");
	strong_player->returnUI()->setHealthLineImg(images.size() - 1);
	dexterous_player->returnUI()->setHealthLineImg(images.size() - 1);
	for (int i = 0; i < 3; ++i)
	{
		UI_objects.push_back(player->returnUI()->getActiveBonusesPtr(i));
	}
	UI_objects.push_back(player->returnUI()->getHealthPtr());
	text_objects.push_back(player->returnUI()->getPlayerName());
	text_objects.push_back(player->returnUI()->getPlayerType());
}

std::vector<Action> Level::sensorStagesParser(std::vector<std::string> stages)
{
	std::vector<Action> result;
	for (auto it : stages)
	{
		if (it == std::string("up"))
		{
			result.push_back(Action::UP);
		}
		else if (it == std::string("down"))
		{
			result.push_back(Action::DOWN);
		}
		else if (it == std::string("off"))
		{
			result.push_back(Action::OFF);
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
	*is_rounded = checkElementExistence(findAmongSiblings(trajectory->FirstChildElement("properties")->FirstChildElement("property"), std::string("is_rounded")), "Round modificator for trajectory wasn't found")->BoolAttribute("value");
	return coord_set;
}

