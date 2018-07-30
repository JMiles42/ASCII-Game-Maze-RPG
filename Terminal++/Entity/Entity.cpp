#include "Entity.h"
#include "../RequiredVariables.h"
Entity::~Entity() { }
void Entity::MovePos(Vector2i newPos, bool RelitiveMove)
{
	oldPosition = position;
	if (RelitiveMove)
		position += newPos;
	else
		position = newPos;
}
void Entity::MoveInDirection(Direction dir)
{
	oldPosition = position;
	position += dir;
}
bool Entity::CanMoveInDirection(Direction dir) const
{
	Vector2i newPos = position + dir;
	ClampVector(newPos);
	Map::Tile *tile = currentMap[newPos];
	switch (tile->tile)
	{
	case Map::TileType::Wall:
		return false;
	default:
		return true;
	}
}
void Entity::ClampVector(Vector2i &vecToClamp)
{
	Vector2i::ClampVector(vecToClamp);
}
