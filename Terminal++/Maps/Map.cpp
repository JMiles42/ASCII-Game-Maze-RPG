#include "Map.h"
#include "../MapGenerator.h"
Map::Map()
{
	MapGenerator gen = MapGenerator(time(nullptr));
	*this = gen.GenerateMap();
	CalculateColour();
}
Map::Map(int seed)
{
	MapGenerator gen = MapGenerator(seed);
	*this = gen.GenerateMap();
	CalculateColour();
}
Map::Map(bool seed)
{
	LevelData = CreateBlankMap();
}
Map::Map(std::vector<std::string> fileData)
{
	LevelData = CreateBlankMap();
	for (int y = 0; y < fileData.size(); y++)
		for (int x = 0; x < fileData[y].size(); x++)
			LevelData[y][x] = static_cast<TileType>(fileData[y][x]);
	CalculateColour();
}
Map::Map(std::vector<std::vector<Tile>> _LevelData)
{
	LevelData = _LevelData;
}
Map::~Map() {}
Vector2i Map::GetSpawnPoint()
{
	if (spawnPoint.size() > 0)
		return spawnPoint[rand() % spawnPoint.size()];
	return Vector2i(1);
}
Vector2i Map::GetTeleporterPoint()
{
	if (teleporters.size() > 0)
		return teleporters[rand() % teleporters.size()];
	return Vector2i(1);
}
std::vector<std::vector<Map::Tile>> Map::CreateBlankMap()
{
	std::vector<std::vector<Tile>> data;
	for (int y = 0; y < 20; y++)
	{
		std::vector<Tile> Row;
		for (int x = 0; x < 58; x++)
			Row.push_back(TileType::Air);
		data.push_back(Row);
	}
	return data;
}
//Use the operator[Vector2i]
Map::Tile Map::GetTileAtPos(Vector2i &pos)
{
	return LevelData[pos.yPos][pos.xPos];
}
void Map::CalculateColour()
{
	teleporters.clear();
	spawnPoint.clear();
	enemySpawns.clear();
	for (int y = 0; y < 20; y++)
		for (int x = 0; x < 58; x++)
		{
			//For each tile set its symbol, if its a special tile add it to its vector
			//Then colour it
			switch (static_cast<TileType>(LevelData[y][x]))
			{
			case TileType::Air:
			case TileType::Wall:
				LevelData[y][x] = static_cast<TileType>(LevelData[y][x]);
				break;
			case TileType::LoadedWall:
				LevelData[y][x] = TileType::Wall;
				break;
			case TileType::Door:
				LevelData[y][x] = static_cast<TileType>(LevelData[y][x]);
				break;
			case TileType::Teleporter:
				teleporters.push_back(Vector2i(y, x));
				LevelData[y][x] = static_cast<TileType>(LevelData[y][x]);
				break;
			case TileType::Chest:
			case TileType::LootedChest:
			case TileType::Loot:
				LevelData[y][x] = static_cast<TileType>(LevelData[y][x]);
				break;
			case TileType::PlayerSpawn:
				spawnPoint.push_back(Vector2i(y, x));
				LevelData[y][x] = TileType::Air;
				break;
			case TileType::LoadedAir:
				LevelData[y][x] = TileType::Air;
				break;
			case TileType::EnemySpawn:
				enemySpawns.push_back(Vector2i(y, x));
				LevelData[y][x] = TileType::Air;
				break;
			default:
				break;
			}
			LevelData[y][x].SetColourDefualt();
		}
}
std::vector<Map::Tile> * Map::operator[](const int yPos)
{
	return &LevelData[yPos];
}
Map::Tile * Map::operator[](const Vector2i pos)
{
	return &LevelData[pos.yPos][pos.xPos];
}
