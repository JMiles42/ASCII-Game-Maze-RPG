#include "MapGenerator.h"
#include "Maps/Map.h"
//#define cMapGen
MapGenerator::MapGenerator(int seed)
{
	mapSeed = seed;
}
MapGenerator::~MapGenerator() {}
Map MapGenerator::GenerateMap(int seed) const
{
#ifdef cMapGen
	srand(mapSeed);
#endif
	return GetBuiltMap(mapSeed);
}
std::vector<std::vector<Map::Tile>> MapGenerator::GetBuiltMap(int seed)
{
	//Sets up the empty corectly sized map
	std::vector<std::vector<int>> map = CreateBlankMap();
	//Randomly fills the map with walls
	RandomFillMap(map, seed);
	//Smooths the map to make walls, and paths rather the just random tiles every where
	for (int i = 0; i < 5; ++i)
		SmothMap(map);
	//Addeds the extra tiles like spawn and loot
	FinalMapProcesser(map, seed);
	//Returns the map into its converted form that is used by the map class
	return GetMapFromIntVector(map);
}
//Creates a vecter of vectors the size of the map that are all "Air"
std::vector<std::vector<int>> MapGenerator::CreateBlankMap()
{
	std::vector<std::vector<int>> data;
	for (int y = 0; y < 20; y++)
	{
		std::vector<int> Row;
		for (int x = 0; x < 58; x++)
			Row.push_back(0);
		data.push_back(Row);
	}
	return data;
}
//Creates a vector of empty positions 
std::vector<std::vector<Vector2i>> MapGenerator::CreateBlankVectorMap()
{
	std::vector<std::vector<Vector2i>> data;
	for (int y = 0; y < 20; y++)
	{
		std::vector<Vector2i> Row;
		for (int x = 0; x < 58; x++)
			Row.push_back(0);
		data.push_back(Row);
	}
	return data;
}
//Converts the int map to the tilemap the Map class requires
std::vector<std::vector<Map::Tile>> MapGenerator::GetMapFromIntVector(std::vector<std::vector<int>> &map)
{
	std::vector<std::vector<Map::Tile>> newMap = Map::CreateBlankMap();
	for (int y = 0; y < 20; y++)
	{
		std::vector<int> Row;
		for (int x = 0; x < 58; x++)
		{
			switch (map[y][x])
			{
			case 0:
				newMap[y][x] = Map::TileType::Air;
				break;
			case 1:
				newMap[y][x] = Map::TileType::Wall;
				break;
			case 2:
				newMap[y][x] = Map::TileType::PlayerSpawn;
				break;
			case 3:
				newMap[y][x] = Map::TileType::EnemySpawn;
				break;
			case 4:
				newMap[y][x] = Map::TileType::Loot;
				break;
			case 5:
				newMap[y][x] = Map::TileType::Chest;
				break;
			case 6:
				newMap[y][x] = Map::TileType::Door;
				break;
			case 7:
				newMap[y][x] = Map::TileType::Teleporter;
				break;
			default:
				newMap[y][x] = Map::TileType::Air;
				break;
			}
		}
	}
	return newMap;
}
void MapGenerator::RandomFillMap(std::vector<std::vector<int>> &map, int seed, int fillAmount)
{
	std::vector<std::vector<int>> data;
#ifdef cMapGen
	for (int y = 0; y < 20; y++)
	{
		std::vector<int> Row;
		for (int x = 0; x < 58; x++)
			rand() % 2 == 0 ? Row.push_back(1) : Row.push_back(0);
		data.push_back(Row);
	}
#endif // !cMapGen
#ifndef cMapGen
	//Psudo rng
	std::mt19937 eng = std::mt19937(seed);
	//Range of output
	//Yes its 101 numbers I know
	std::uniform_int_distribution<int> dist(0, 100);
	for (int y = 0; y < 20; y++)
	{
		std::vector<int> Row;
		for (int x = 0; x < 58; x++)
			dist(eng) > fillAmount ? Row.push_back(1) : Row.push_back(0);
		data.push_back(Row);
	}
#endif // cMapGen
	map = data;
}
//Smooths map, by checking neighbers and if it has mostly walls set it to a wall as well, or set it to air
void MapGenerator::SmothMap(std::vector<std::vector<int>> &map)
{
	for (int y = 0; y < 20; y++)
		for (int x = 0; x < 58; x++)
		{
			int neighbourWalls = GetSurroundingWallCount(map, y, x);
			//if (neighbourWalls < 2)
			if (neighbourWalls < 2)
				map[y][x] = 1;
			else
				map[y][x] = 0;
		}
}
//Gets the amount of walls around it
int MapGenerator::GetSurroundingWallCount(std::vector<std::vector<int>> &map, int lookAtY, int lookAtX)
{
	int wallCount = 0;
	for (int y = lookAtY - 1; y <= lookAtY + 1; y++)
		for (int x = lookAtX - 1; x <= lookAtX + 1; x++)
		{
			if (IsInMapRange(y, x))
			{
				if (x != lookAtX && y != lookAtY)
					wallCount += map[y][x];
			}
		}
	return wallCount;
}
//Gets the amount of walls around it
int MapGenerator::GetSurroundingWallCount(std::vector<std::vector<Map::Tile>> &map, int lookAtY, int lookAtX)
{
	int wallCount = 0;
	for (int y = lookAtY - 1; y <= lookAtY + 1; y++)
		for (int x = lookAtX - 1; x <= lookAtX + 1; x++)
		{
			if (IsInMapRange(y, x))
			{
				if (x != lookAtX && y != lookAtY)
					if (map[y][x] == Map::TileType::Wall)
						wallCount += 1;
			}
		}
	return wallCount;
}
//Checks in the pos is in map range
bool MapGenerator::IsInMapRange(int y, int x)
{
	return (x >= 0 && x < 58 && y >= 0 && y < 20);
}
//Gets the each air region in the map
std::vector<std::vector<Vector2i>> MapGenerator::GetRegions(std::vector<std::vector<int>> &map, int tileType)
{
	std::vector<std::vector<Vector2i>> regions = CreateBlankVectorMap();
	std::vector<std::vector<int>> mapFlags = CreateBlankMap();
	for (int y = 0; y < 20; y++)
		for (int x = 0; x < 58; x++)
			if (mapFlags[y][x] == 0 && mapFlags[y][x] == tileType)
			{
				std::vector<Vector2i> newRegion = GetRegionTiles(map, y, x);
				regions.push_back(newRegion);
				for (auto &pos : newRegion)
					mapFlags[pos.yPos][pos.xPos] = 1;
			}
	return regions;
}
//Gets all the tiles in a region
std::vector<Vector2i> MapGenerator::GetRegionTiles(std::vector<std::vector<int>> &map, int y, int x)
{
	std::vector<Vector2i> tiles;
	std::vector<std::vector<int>> mapFlags = CreateBlankMap();
	int tileType = map[y][x];
	std::queue<Vector2i> queue;
	queue.emplace(Vector2i(y, x));
	mapFlags[y][x] = 1;
	while (queue.size() > 0)
	{
		Vector2i tile = queue.front();
		queue.pop();
		tiles.push_back(tile);
		for (int yCount = tile.yPos - 1; yCount <= tile.yPos + 1; yCount++)
		{
			for (int xCount = tile.xPos - 1; xCount <= tile.xPos + 1; xCount++)
			{
				if (IsInMapRange(yCount, xCount) && (yCount == tile.yPos || xCount == tile.xPos))
				{
					if (mapFlags[yCount][xCount] == 0 && map[yCount][xCount] == tileType)
					{
						mapFlags[yCount][xCount] = 1;
						queue.push(Vector2i(yCount, xCount));
					}
				}
			}
		}
	}
	return tiles;
}
//Does most of the work
void MapGenerator::FinalMapProcesser(std::vector<std::vector<int>> &map, int seed)
{
	//Map regions
	auto wallRegions = GetRegions(map, 1);
	//Threshold to remove wall sections if they are smaller
	int wallThresholdSize = 10;
	for (auto &wallRegion : wallRegions)
		if (wallRegion.size() < wallThresholdSize)
			for (auto &tile : wallRegion)
				map[tile.yPos][tile.xPos] = 0;
	//Gets remaining rooms
	auto roomRegions = GetRegions(map, 0);
	//Threshold to Removes rooms 
	int roomThresholdSize = 6;
	std::vector<Room> survivingRooms;
	for (auto &roomRegion : roomRegions)
		if (roomRegion.size() < roomThresholdSize)
			for (auto &tile : roomRegion)
				map[tile.yPos][tile.xPos] = 1;
		else
			survivingRooms.push_back(Room(map, roomRegion));
	ConnectClosestRooms(map, survivingRooms);
	CreateSpecialTiles(map, seed);
}
void MapGenerator::ConnectClosestRooms(std::vector<std::vector<int>> &map, std::vector<Room> allRooms)
{
	int bestDistance = 0;
	Vector2i bestTileA;
	Vector2i bestTileB;
	Room bestRoomA;
	Room bestRoomB;
	bool possableRoom = false;
	//For every room
	for (auto &roomA : allRooms)
	{
		possableRoom = false;
		//Check every room
		for (auto &roomB : allRooms)
		{
			//Skip if room is self
			if (roomA == roomB)
				continue;
			//Skip if room is joind already
			if (roomA.IsConnected(roomB))
			{
				possableRoom = false;
				break;
			}
			//For every tile check every tile in each room compair there distance
			for (int tileIndexA = 0; tileIndexA < roomA.edgeTiles.size(); tileIndexA++)
			{
				for (int tileIndexB = 0; tileIndexB < roomB.edgeTiles.size(); tileIndexB++)
				{
					Vector2i tileA = roomA.edgeTiles[tileIndexA];
					Vector2i tileB = roomB.edgeTiles[tileIndexB];
					//Caculate distance
					int distanceBetweenRooms = static_cast<int>(std::pow(tileA.xPos - tileB.xPos, 2) + std::pow(tileA.yPos - tileB.yPos, 2));
					//If its smaller the best distance or there is no room connecte
					//Conect rooms
					if (distanceBetweenRooms < bestDistance || !possableRoom)
					{
						bestDistance = distanceBetweenRooms;
						possableRoom = true;
						bestTileA = tileA;
						bestTileB = tileB;
						bestRoomA = roomA;
						bestRoomB = roomB;
					}
				}
			}
		}
		if (possableRoom)
			CreatePassage(map, bestRoomA, bestRoomB, bestTileA, bestTileB);
	}
}
void MapGenerator::CreatePassage(std::vector<std::vector<int>> &map, Room roomA, Room roomB, Vector2i tileA, Vector2i tileB)
{
	//Connect room a & b
	Room::ConnectRooms(roomA, roomB);
	//My sort of wroking join system
	//On my small maps that i generate it works most of the time
	map[tileA.yPos][tileA.xPos] = 0;
	map[tileB.yPos][tileB.xPos] = 0;
}
MapGenerator::Room::Room() {}
bool MapGenerator::Room::operator==(const Room &otherRoom)
{
	//Simple comparison
	return (this->roomSize == otherRoom.roomSize && this->tiles[0] == otherRoom.tiles[0]);
}
MapGenerator::Room::Room(std::vector<std::vector<int>> &map, std::vector<Vector2i> _tiles)
{
	tiles = _tiles;
	roomSize = tiles.size();
	connectedRooms = std::vector<Room>();
	edgeTiles = std::vector<Vector2i>();
	//I can't remember exactly what this does XD
	//I think it is finding the walls, most of this map generater system is for a min 200/200 cave generator for unity in c#,
	//Making alot of these checks redundent as my walls are generaly only 1 thick
	for (auto &tile : tiles)
		for (int y = tile.yPos - 1; y <= tile.yPos + 1; y++)
			for (int x = tile.xPos - 1; x <= tile.xPos + 1; x++)
				if (IsInMapRange(y, x))
					if (x == tile.xPos || y == tile.yPos)
						if (map[y][x] == 1)
							if (std::find(edgeTiles.begin(), edgeTiles.end(), tile) == edgeTiles.end())
								edgeTiles.push_back(tile);
}
void MapGenerator::Room::ConnectRooms(Room roomA, Room roomB)
{
	roomA.connectedRooms.push_back(roomB);
	roomB.connectedRooms.push_back(roomA);
}
bool MapGenerator::Room::IsConnected(Room otherRooms)
{
	return (std::find(connectedRooms.begin(), connectedRooms.end(), otherRooms) != connectedRooms.end());
}
void MapGenerator::CreateSpecialTiles(std::vector<std::vector<int>> &map, int seed)
{
	bool noPlayerSpawnPoints = true;
	bool noEnemySpawnPoints = true;
	bool noLoot = true;
	bool noChest = true;
	bool noTeleporters = true;
	bool noDoor = true;
	std::mt19937 eng = std::mt19937(seed);
	//Howmany tiles to generate
	std::uniform_int_distribution<int> tileAmount(1, 5);
	//Map pos randoms
	std::uniform_int_distribution<int> yAmount(0, 19);
	std::uniform_int_distribution<int> xAmount(0, 57);
	//For every special tile
	//Get a number to spawn
	//Then for each one it should spawn, generate cords, check if there air, if they are put tile there else get a new pos
	while (noPlayerSpawnPoints)
	{
		int num = tileAmount(eng);
		for (int i = 0; i < num; i++)
		{
			int lookAtY = yAmount(eng);
			int lookAtX = xAmount(eng);
			while (map[lookAtY][lookAtX] != 0)
			{
				lookAtY = yAmount(eng);
				lookAtX = xAmount(eng);
			}
			map[lookAtY][lookAtX] = 2;
		}
		noPlayerSpawnPoints = false;
	}
	while (noEnemySpawnPoints)
	{
		int num = tileAmount(eng) * 2;
		for (int i = 0; i < num; i++)
		{
			int lookAtY = yAmount(eng);
			int lookAtX = xAmount(eng);
			while (map[lookAtY][lookAtX] != 0)
			{
				lookAtY = yAmount(eng);
				lookAtX = xAmount(eng);
			}
			map[lookAtY][lookAtX] = 3;
		}
		noEnemySpawnPoints = false;
	}
	while (noLoot)
	{
		int num = tileAmount(eng);
		num *= 2;
		for (int i = 0; i < num; i++)
		{
			int lookAtY = yAmount(eng);
			int lookAtX = xAmount(eng);
			while (map[lookAtY][lookAtX] != 0)
			{
				lookAtY = yAmount(eng);
				lookAtX = xAmount(eng);
			}
			map[lookAtY][lookAtX] = 4;
		}
		noLoot = false;
	}
	while (noChest)
	{
		int num = static_cast<int>(tileAmount(eng) / 2);
		for (int i = 0; i < num; i++)
		{
			int lookAtY = yAmount(eng);
			int lookAtX = xAmount(eng);
			while (map[lookAtY][lookAtX] != 0)
			{
				lookAtY = yAmount(eng);
				lookAtX = xAmount(eng);
			}
			map[lookAtY][lookAtX] = 5;
		}
		noChest = false;
	}
	while (noTeleporters)
	{
		int num = static_cast<int>(tileAmount(eng) * 2);
		for (int i = 0; i < num; i++)
		{
			int lookAtY = yAmount(eng);
			int lookAtX = xAmount(eng);
			while (map[lookAtY][lookAtX] != 0)
			{
				lookAtY = yAmount(eng);
				lookAtX = xAmount(eng);
			}
			map[lookAtY][lookAtX] = 7;
		}
		noTeleporters = false;
	}
	while (noDoor)
	{
		int num = tileAmount(eng);
		int lookAtY = yAmount(eng);
		int lookAtX = xAmount(eng);
		while (map[lookAtY][lookAtX] != 0)
		{
			lookAtY = yAmount(eng);
			lookAtX = xAmount(eng);
		}
		map[lookAtY][lookAtX] = 6;
		noDoor = false;
	}
}
