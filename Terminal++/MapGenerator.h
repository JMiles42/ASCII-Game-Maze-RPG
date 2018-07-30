#pragma once
#include "UniversalHeader.h"
#include "Maps/Map.h"
class MapGenerator
{
public:
	MapGenerator(int seed);
	~MapGenerator();
	Map GenerateMap(int seed = 1) const;
	class Room
	{
	public:
		std::vector<Vector2i> tiles;
		std::vector<Vector2i> edgeTiles;
		std::vector<Room> connectedRooms;
		int roomSize;
		Room();
		Room(std::vector<std::vector<int>> &map, std::vector<Vector2i> _tiles);
		static void ConnectRooms(Room roomA, Room roomB);
		bool IsConnected(Room otherRooms);
		bool operator ==(const Room &otherRoom);
	};
	//private:
	int mapSeed;
	static std::vector<std::vector<Map::Tile>> GetBuiltMap(int seed);
	static std::vector<std::vector<int>> CreateBlankMap();
	static std::vector<std::vector<Vector2i>> CreateBlankVectorMap();
	static std::vector<std::vector<Map::Tile>> GetMapFromIntVector(std::vector<std::vector<int>> &map);
	static void RandomFillMap(std::vector<std::vector<int>> &map, int seed, int fillAmount = 50);
	static void SmothMap(std::vector<std::vector<int>> &map);
	static int GetSurroundingWallCount(std::vector<std::vector<int>> &map, int y, int x);
	static int GetSurroundingWallCount(std::vector<std::vector<Map::Tile>> &map, int y, int x);
	static bool IsInMapRange(int y, int x);
	static void FinalMapProcesser(std::vector<std::vector<int>> &map, int seed);
	static std::vector<std::vector<Vector2i>> GetRegions(std::vector<std::vector<int>> &map, int tileType);
	static std::vector<Vector2i> GetRegionTiles(std::vector<std::vector<int>> &map, int y, int x);
	static void ConnectClosestRooms(std::vector<std::vector<int>> &map, std::vector<Room> allRooms);
	static void CreatePassage(std::vector<std::vector<int>> &map, Room roomA, Room roomB, Vector2i tileA, Vector2i tileB);
	static void CreateSpecialTiles(std::vector<std::vector<int>> &map, int seed);
};
