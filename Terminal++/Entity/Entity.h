#pragma once
#include "../JMiles42/Maths/Vectors/Vector2i.h"
class Entity
{
public:
	//Entities Position
	Vector2i position;
	//The Entities Previous Pos
	Vector2i oldPosition;
	virtual ~Entity();
	//Move the position
	//NOT USED ANYMORE
	//USE Position += Direction INSTED OF this 
	virtual void MovePos(Vector2i newPos, bool RelitiveMove = false);
	//USE POSITION CLAMP INSTED OF THIS
	static void ClampVector(Vector2i &vecToClamp);
	//USE Position += Direction INSTED OF this 
	virtual void MoveInDirection(Direction dir);
	//Checks if I can move in direction
	bool CanMoveInDirection(Direction dir) const;
};
