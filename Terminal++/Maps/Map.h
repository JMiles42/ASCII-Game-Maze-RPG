#pragma once
#include "../UniversalHeader.h"
#include "../SubWindowWithBorder.h"
#include "../JMiles42/FileIO/CSVReader.h"
#include "../JMiles42/Maths/Vectors/Vector2i.h"
class Map
{
public:
	//Type of tiles that the map can contain
	enum class TileType
	{
		Air = ' ',
		//Players Spawn Points
		//Not Rendered
		PlayerSpawn = 'p',
		//Player
		Player = 'P',
		//Walls To Render
		Wall = static_cast<int>(219),
		//Walls From File
		LoadedWall = '#',
		Teleporter = '?',
		Door = 'D',
		Chest = 'C',
		LootedChest = 'c',
		Loot = 'L',
		//Enemy Spawn Points
		//Not Rendered
		EnemySpawn = 'E',
		Enemy = '@',
		//Air from File
		//Not rendered
		LoadedAir = 'A',
	};
	//The way all tiles are stored in memory, so it can be displayed easly
	struct Tile
	{
		//Type of this tile
		TileType tile;
		//Colour of this tile
		SubWindowWithBorder::Colour colour;
		//Normal constructer
		Tile(TileType _tile)
		{
			tile = _tile;
			colour = SubWindowWithBorder::Colour::Purple;
		}
		Tile(TileType _tile, SubWindowWithBorder::Colour _colour)
		{
			tile = _tile;
			colour = _colour;
		}
		operator TileType() const
		{
			return tile;
		}
		operator char() const
		{
			return static_cast<char>(tile);
		}
		operator SubWindowWithBorder::Colour() const
		{
			return colour;
		}
		//Sets the colour to the tiles defualt
		void SetColourDefualt()
		{
			switch (tile)
			{
			case TileType::Air:
			case TileType::Wall:
			case TileType::LoadedWall:
			case TileType::LoadedAir:
			case TileType::PlayerSpawn:
			case TileType::EnemySpawn:
			default:
				colour = SubWindowWithBorder::Colour::Purple;
				break;
			case TileType::Door:
			case TileType::Teleporter:
				colour = SubWindowWithBorder::Colour::Green;
				break;
			case TileType::Chest:
			case TileType::LootedChest:
			case TileType::Loot:
				colour = SubWindowWithBorder::Colour::Yellow;
				break;
			}
		}
	};
	//Player posable Spawn Points Cords
	//So even if the same map loads spawns should be differant, as c Rand is used to choose here
	std::vector<Vector2i> spawnPoint;
	//The Map Data
	std::vector<std::vector<Tile>> LevelData;
	//Enemy Spawn Points Cords
	std::vector<Vector2i> enemySpawns;
	//The teleporter Cords
	std::vector<Vector2i> teleporters;
	Map();
	Map(int seed);
	Map(bool seed);
	Map(std::vector<std::string> fileData);
	Map(std::vector<std::vector<Tile>> _LevelData);
	~Map();
	//Gets one spawn Point
	Vector2i GetSpawnPoint();
	//Gets One teleport point
	Vector2i GetTeleporterPoint();
	//Creates a fully air map, used mainly for init
	static std::vector<std::vector<Tile>> CreateBlankMap();
	//Get Tile At point
	Tile GetTileAtPos(Vector2i &pos);
	//Calls calculat colour on all tiles
	void CalculateColour();
	//Retunrs a row of tiles
	//Not realy used
	//Use the vecter version of this overload
	std::vector<Tile> * operator [](const int yPos);
	//Added way to late into the projects development this is the easyest way to get a tile, as its already how all the positions are stored
	Tile * operator [](const Vector2i pos);
};
