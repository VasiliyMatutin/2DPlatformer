#include "Level.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>

enum class BodyType
{
	STATIC,
	KINEMATIC,
	DYNAMIC,
};

Level::Level()
{
	b2Vec2 gravity(0.0f, 1.0f);
	level_world = new b2World(gravity);
	my_contact_listener_ptr = new MyContactListener;
	level_world->SetContactListener(my_contact_listener_ptr);
}

Level::~Level()
{
	delete level_world;
	delete player;
	delete my_contact_listener_ptr;
	for (auto it : platform_list)
	{
		delete it;
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
	tinyxml2::XMLElement *objectgroup = map->FirstChildElement("objectgroup");
	loadObjects(objectgroup);
	return 1;
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

void Level::update()
{
	level_world->Step(1.0f / 60.0f, 1, 1);
	for (auto it : non_static_objects)
	{
		it->update();
	}
}

void Level::loadMap(tinyxml2::XMLElement *map)
{
	level_width = atoi(map->Attribute("width"));
	level_height = atoi(map->Attribute("height"));
	tile_width = atoi(map->Attribute("tilewidth"));
	tile_height = atoi(map->Attribute("tileheight"));

	//Add tileset image
	std::vector <TilesetImg> image_list;
	TilesetImg tg;
	tinyxml2::XMLElement *tileset = map->FirstChildElement("tileset");
	while (tileset)
	{
		tg.first_gid = atoi(tileset->Attribute("firstgid"));
		tg.columns = atoi(tileset->Attribute("columns"));
		tg.last_gid = tg.first_gid + atoi(tileset->Attribute("tilecount")) - 1;
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

void Level::loadObjects(tinyxml2::XMLElement * objectgroup)
{
	while (objectgroup)
	{
		Object tmp_obj;
		tmp_obj.top = 0;
		tmp_obj.left = 0;

		BodyType b_type;
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
			body_def.fixedRotation = true;
			switch (b_type)
			{
			case BodyType::STATIC:
				body_def.type = b2_staticBody;
				break;
			case BodyType::KINEMATIC:
				body_def.type = b2_kinematicBody;
				break;
			case BodyType::DYNAMIC:
				body_def.type = b2_dynamicBody;
				break;
			}
			tmp_obj.width = atoi(object->Attribute("width"));
			tmp_obj.height = atoi(object->Attribute("height"));
			tmp_obj.x = atoi(object->Attribute("x")) + tmp_obj.width / 2;
			tmp_obj.y = atoi(object->Attribute("y")) + tmp_obj.height / 2;
			body_def.position.Set(tmp_obj.x, tmp_obj.y);
			shape.SetAsBox(tmp_obj.width / 2, tmp_obj.height / 2);
			b2Body* body = level_world->CreateBody(&body_def);
			if (b_type != BodyType::STATIC)
			{
				tinyxml2::XMLElement *properties = object->FirstChildElement("properties");
				images.push_back(findAmongSiblings(properties->FirstChildElement("property"), std::string("image"))->Attribute("value"));
				tmp_obj.number_in_image_list = images.size() - 1;

				b2FixtureDef fixture_def;
				fixture_def.shape = &shape;
				body->CreateFixture(&fixture_def);
				changeable_objects.push_back(tmp_obj);

				if (std::string(object->Attribute("type")) == std::string("player"))
				{
					player = new Player(8, level_width*tile_width, level_height*tile_height, 0.1 / 10, body, &changeable_objects.back(), 10);
					non_static_objects.push_back(player);
				}
				else if (std::string(object->Attribute("type")) == std::string("platform")) // create platform using xml file
				{
					bool is_rounded = 0;
					std::vector<std::pair<int, int>> traj_coord = buildTrajectory(objectgroup, findAmongSiblings(properties->FirstChildElement("property"), std::string("trajectory"))->Attribute("value"), &is_rounded);
					Platform* platform = new Platform(level_width*tile_width, level_height*tile_height, body, &changeable_objects.back(), traj_coord, atoi(findAmongSiblings(properties->FirstChildElement("property"), std::string("speed"))->Attribute("value")), is_rounded);
					platform_list.push_back(platform);
					non_static_objects.push_back(platform_list.back());
				}
			}
			else
			{
				body->CreateFixture(&shape, 1.0f);
			}
			object = object->NextSiblingElement("object");
		}
		objectgroup = objectgroup->NextSiblingElement("objectgroup");
	}
}

tinyxml2::XMLElement* Level::findAmongSiblings(tinyxml2::XMLElement* element, std::string name)
{
	while (element)
	{
		if (std::string(element->Attribute("name")) == name) return element;
		element = element->NextSiblingElement();
	}
	return nullptr;
}

std::vector<std::pair<int, int>> Level::buildTrajectory(tinyxml2::XMLElement * objectgroup, std::string trajectory_name, bool* is_rounded)
{
	tinyxml2::XMLElement *trajectory = findAmongSiblings(objectgroup->FirstChildElement("object"), trajectory_name); // build trajectory for platform 
	if (!trajectory)
	{
		throw "No trajectory for this platform"; /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	int init_x = atoi(trajectory->Attribute("x"));
	int init_y = atoi(trajectory->Attribute("y"));
	std::string polyline = trajectory->FirstChildElement("polyline")->Attribute("points");
	std::istringstream iss(polyline);
	std::vector<std::string> results((std::istream_iterator<std::string>(iss)), {});
	std::vector<std::pair<int, int>> coord_set;
	for (auto it : results)
	{
		std::string::size_type pos = it.find(','); // devide x & y coordinates
		int tmp_x = init_x + stoi(it.substr(0, pos)); // in poliline point
		int tmp_y = init_y + stoi(it.substr(pos + 1));
		std::pair<int, int> point(tmp_x, tmp_y);
		coord_set.push_back(point);
	}
	*is_rounded = atoi(findAmongSiblings(trajectory->FirstChildElement("properties")->FirstChildElement("property"), std::string("is_rounded"))->Attribute("value"));
	return coord_set;
}

