#include "EnemySimple.h"
EnemySimple::EnemySimple():
	Person(5)
{
	rd = std::mt19937(time(nullptr));
	EnQueuePath();
	walkLength = (dist(rd) + 1) * 3;
	state = EnemyState::Idle;
	prevDir = static_cast<Direction>(dist(rd));;
}
EnemySimple::EnemySimple(Vector2i pos, int seed) :
	Person(5)
{
	rd = std::mt19937(seed);
	position = pos;
	EnQueuePath();
	walkLength = (dist(rd) + 1) * 3;
	state = EnemyState::Idle;
	prevDir = static_cast<Direction>(dist(rd));;
}
EnemySimple::~EnemySimple() {}
bool EnemySimple::TakeDamage(int amount)
{
	bool b = Person::TakeDamage(amount);
	state = EnemyState::Attacking;
	return b;
}
bool EnemySimple::Update()
{
	//Check if it is still walking to its spot
	if (currentWalkLength <= walkLength)
	{
		state = EnemyState::Walking;
		position += prevDir;
		position.ClampVector();
	}
	else
	{
		state = EnemyState::Idle;
		if (currentWalkLength > walkLength + 2)
		{
			//Set walking stats to the next in the queue, then readd it to the queue
			auto pair = path.front();
			prevDir = pair.first;
			walkLength = pair.second;
			path.pop();
			path.push(pair);
			currentWalkLength = 0;
		}
	}
	++currentWalkLength;

	Map::Tile *tile = currentMap[position];
	switch (tile->tile)
	{
	case Map::TileType::Wall:
		tile->tile = Map::TileType::Air;
		break;
	case Map::TileType::Teleporter:
		position = currentMap.GetTeleporterPoint();
		break;
	default:
		break;
	}
	if (position == player.position)
		playerDead = player.TakeDamage(5);
	return true;
}
Direction EnemySimple::GetNewDir() const
{
	Direction dir = prevDir;
	switch (dir)
	{
	case Direction::Up:
		dir = Direction::Left;
		break;
	case Direction::Left:
		dir = Direction::Down;
		break;
	case Direction::Down:
		dir = Direction::Right;
		break;
	case Direction::Right:
		dir = Direction::Up;
		break;
	default:
		break;
	}
	return dir;
}
void EnemySimple::EnQueuePath()
{
	//Add random dir and lenth to path
	for (int i = 0; i < 6; ++i)
		path.push(std::pair<Direction, int>(static_cast<Direction>(dist(rd)), dist(rd)));
}
