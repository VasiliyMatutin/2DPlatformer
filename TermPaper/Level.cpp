#include "Level.h"
#include "tinyxml2.h"
#include <iostream>
#include <sstream>
#include <vector>

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
}

bool Level::loadLevel(std::string filename)
{
	//load XML-file with level description
	tinyxml2::XMLDocument level_file;
	tinyxml2::XMLError error = level_file.LoadFile(filename.c_str());


	//Error verification
	if (error != 0)
	{
		std::cout << "Loading level \"" << filename << "\" failed." << std::endl; ///Exeptions!!!! Won't forget!!
		return false;
	}

	//Set map parameters
	tinyxml2::XMLElement *map = level_file.FirstChildElement("map");
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
		const char* str=data->GetText();
		std::stringstream tempss;
		tempss << str;
		Object one_tile;
		int i,j, x=0, y=0;
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

	//Add objects group
	tinyxml2::XMLElement *objectgroup = map->FirstChildElement("objectgroup");
	while (objectgroup)
	{
		images.push_back("1.png");//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		Object tmp_obj;
		tmp_obj.number_in_image_list = images.size() - 1;
		tmp_obj.top = 0;
		tmp_obj.left = 0;

		bool is_static = 1;
		if (std::string(objectgroup->Attribute("name")) != std::string("Static")) is_static = 0;
		tinyxml2::XMLElement *object = objectgroup->FirstChildElement("object");
		while (object)
		{
			b2BodyDef body_def;
			b2PolygonShape shape;
			body_def.fixedRotation = true;
			if (is_static) body_def.type = b2_staticBody;
			else body_def.type = b2_dynamicBody;
			//tinyxml2::XMLElement *polygon = object->FirstChildElement("polygon");
			//if (!polygon)
			//{
			tmp_obj.width = atoi(object->Attribute("width"));
			tmp_obj.height = atoi(object->Attribute("height"));
			tmp_obj.x = atoi(object->Attribute("x")) + tmp_obj.width / 2;
			tmp_obj.y = atoi(object->Attribute("y")) + tmp_obj.height / 2;
			body_def.position.Set(tmp_obj.x, tmp_obj.y);
			shape.SetAsBox(tmp_obj.width/2, tmp_obj.height/2);
			//}
			/*else
			{
				body_def.position.Set(x, y);
				const char* str = polygon->Attribute("points");
				std::stringstream tempss;
				tempss << str;
				int xi,yi;
				std::vector<std::pair<int, int>> tmp_vertex;
				while (tempss >> xi)
				{
					tempss.ignore();
					tempss >> yi;
					tmp_vertex.push_back(std::make_pair(x+xi, y+yi));
				}
				b2Vec2 tmp_vec(x,y), a(x,y);
				for (int i = 0; i < tmp_vertex.size(); i++)
				{
					a.Set(tmp_vertex[i].first, tmp_vertex[i].second);
					tmp_vec += a;
				}
				shape.Set(&tmp_vec, tmp_vec.Length());
			}*/
			b2Body* body = level_world->CreateBody(&body_def);
			if (!is_static)
			{
				b2FixtureDef fixture_def;
				fixture_def.shape = &shape;
				fixture_def.density = 1.0f;
				fixture_def.friction = 0.3f;
				body->CreateFixture(&fixture_def);
				changeable_objects.push_back(tmp_obj);
				player = new DynamicObj(8, level_width*tile_width, level_height*tile_height, 0.1 / 10, body, &changeable_objects[changeable_objects.size() - 1]);
			}
			else
				body->CreateFixture(&shape, 1.0f);
			object = object->NextSiblingElement("object");
		}
		objectgroup = objectgroup->NextSiblingElement("objectgroup");
	}
	return 1;
}

std::vector<Object>& Level::getUnchangeableObjectList()
{
	return unchangeable_objects;
}

std::vector<Object>& Level::getChangeableObjectList()
{
	return changeable_objects;
}

std::vector<std::string>& Level::getImagesList()
{
	return images;
}

DynamicObj * Level::returnActivePlayer()
{
	return player;
}

void Level::update()
{
	level_world->Step(1.0f / 60.0f, 1, 1);
	player->update();
}

