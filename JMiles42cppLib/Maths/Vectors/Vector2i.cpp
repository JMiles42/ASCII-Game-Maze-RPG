#include "Vector2i.h"

Vector2i::Vector2i()
{
	yPos = 0;
	xPos = 0;
}

Vector2i::Vector2i(int _y, int _x)
{
	yPos = _y;
	xPos = _y;
}

Vector2i::Vector2i(int _values)
{
	yPos = _values;
	xPos = _values;
}

Vector2i::~Vector2i()
{
}

Vector2i& Vector2i::operator=(const Vector2i& other)
{
	yPos = other.yPos;
	xPos = other.xPos;
	return *this;
}

Vector2i Vector2i::operator+(const Vector2i& other) const
{
	return Vector2i(other.yPos + yPos, other.xPos + xPos);
}

void Vector2i::operator+=(const Vector2i& other)
{
	yPos += other.yPos;
	xPos += other.xPos;
}

void Vector2i::operator/=(const int& other)
{
	(yPos == 0) ? false : yPos /= other;
	(xPos == 0) ? false : xPos /= other;
}

Vector2i Vector2i::operator*(const Vector2i& other) const
{
	return Vector2i(other.yPos * yPos, other.xPos * xPos);
}

Vector2i Vector2i::operator*(const float& other) const
{
	return Vector2i(yPos * other, xPos * other);
}

Vector2i Vector2i::operator*(const int& other) const
{
	return Vector2i(yPos * other, xPos * other);
}

Vector2i Vector2i::operator-(const Vector2i& other) const
{
	return Vector2i(other.yPos - yPos, other.xPos - xPos);
}

bool Vector2i::operator==(const Vector2i& other) const
{
	return (yPos == other.yPos && xPos == other.xPos);
}

void Vector2i::MoveInDirection(Direction dir, int amount)
{
	switch (dir)
	{
	case Direction::Up:
		yPos -= amount;
		break;
	case Direction::Left:
		xPos -= amount;
		break;
	case Direction::Down:
		yPos += amount;
		break;
	case Direction::Right:
		xPos += amount;
		break;
	default:
		break;
	}
}

Vector2i Vector2i::GetCordsInDirection(Direction dir, int amount)const
{
	Vector2i returnValue = Vector2i(this->yPos, this->xPos);
	switch (dir)
	{
	case Direction::Up:
		returnValue.yPos -= amount;
		break;
	case Direction::Left:
		returnValue.xPos -= amount;
		break;
	case Direction::Down:
		returnValue.yPos += amount;
		break;
	case Direction::Right:
		returnValue.xPos += amount;
		break;
	default:
		break;
	}
	return returnValue;
}
