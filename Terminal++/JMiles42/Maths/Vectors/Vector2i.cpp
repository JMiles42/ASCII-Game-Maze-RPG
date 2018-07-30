#include "Vector2i.h"
Vector2i::Vector2i()
{
	yPos = 0;
	xPos = 0;
}
Vector2i::Vector2i(int _y, int _x)
{
	yPos = _y;
	xPos = _x;
}
Vector2i::Vector2i(int _values)
{
	yPos = _values;
	xPos = _values;
}
Vector2i::~Vector2i() {}
Vector2i Vector2i::operator=(const int &amount) const
{
	return Vector2i(amount);
}
Vector2i Vector2i::operator+(const int &amount) const
{
	return Vector2i(yPos + amount, xPos + amount);
}
Vector2i Vector2i::operator+(const Direction &dir) const
{
	Vector2i returnValue = Vector2i(*this);
	returnValue += dir;
	return returnValue;
}
Vector2i Vector2i::operator+(const Vector2i &other) const
{
	return Vector2i(yPos + other.yPos, xPos + other.xPos);
}
Vector2i Vector2i::operator*(const int &amount) const
{
	return Vector2i(yPos * amount, xPos * amount);
}
Vector2i Vector2i::operator*(const Vector2i &other) const
{
	return Vector2i(yPos * other.yPos, xPos * other.xPos);
}
Vector2i Vector2i::operator+=(const int &amount)
{
	yPos += amount;
	xPos += amount;
	return Vector2i(yPos, xPos);
}
Vector2i Vector2i::operator+=(const Direction &dir)
{
	switch (dir)
	{
	case Direction::Up:
		yPos--;
		break;
	case Direction::Left:
		xPos--;
		break;
	case Direction::Down:
		yPos++;
		break;
	case Direction::Right:
		xPos++;
		break;
	default:
		break;
	}
	return Vector2i(yPos, xPos);
}
Vector2i Vector2i::operator+=(const Vector2i &other)
{
	yPos += other.yPos;
	yPos += other.xPos;
	return Vector2i(yPos, xPos);
}
Vector2i Vector2i::operator-(const int &amount) const
{
	return Vector2i(yPos - amount, xPos - amount);
}
Vector2i Vector2i::operator-(const Direction &dir) const
{
	Vector2i returnValue = Vector2i(*this);
	returnValue -= dir;
	return returnValue;
}
Vector2i Vector2i::operator-(const Vector2i &other) const
{
	return Vector2i(yPos - other.yPos, xPos - other.xPos);
}
Vector2i Vector2i::operator-=(const int &amount)
{
	yPos -= amount;
	yPos -= amount;
	return Vector2i(yPos, xPos);
}
Vector2i Vector2i::operator-=(const Direction &dir)
{
	switch (dir)
	{
	case Direction::Up:
		yPos++;
		break;
	case Direction::Left:
		xPos++;
		break;
	case Direction::Down:
		yPos--;
		break;
	case Direction::Right:
		xPos--;
		break;
	default:
		break;
	}
	return Vector2i(yPos, xPos);
}
Vector2i Vector2i::operator-=(const Vector2i &other)
{
	yPos -= other.yPos;
	yPos -= other.xPos;
	return Vector2i(yPos, xPos);
}
bool Vector2i::operator==(const int &amount) const
{
	return yPos == amount && xPos == amount;
}
bool Vector2i::operator==(const Vector2i &other) const
{
	return yPos == other.yPos && xPos == other.xPos;
}
void Vector2i::ClampVector(Vector2i &vecToClamp)
{
	if (vecToClamp.xPos > MovementLimitsRightX)
		vecToClamp.xPos = MovementLimitsLeftX;
	else if (vecToClamp.xPos < MovementLimitsLeftX)
		vecToClamp.xPos = MovementLimitsRightX;
	if (vecToClamp.yPos > MovementLimitsBottomY)
		vecToClamp.yPos = MovementLimitsTopY;
	else if (vecToClamp.yPos < MovementLimitsTopY)
		vecToClamp.yPos = MovementLimitsBottomY;
}
void Vector2i::ClampVector()
{
	if (xPos > MovementLimitsRightX)
		xPos = MovementLimitsLeftX;
	else if (xPos < MovementLimitsLeftX)
		xPos = MovementLimitsRightX;
	if (yPos > MovementLimitsBottomY)
		yPos = MovementLimitsTopY;
	else if (yPos < MovementLimitsTopY)
		yPos = MovementLimitsBottomY;
}
int Vector2i::GetMagnitudeSquared() const
{
	return (xPos * xPos) + (yPos * yPos);
}
int Vector2i::DistanceBetween2Points(Vector2i a, Vector2i b)
{
	return std::sqrt((a - b).GetMagnitudeSquared());
}
int Vector2i::GetMagnitude() const
{
	return std::sqrt(GetMagnitudeSquared());
}
void Vector2i::Normalise()
{
	float mag = GetMagnitude();
	(xPos == 0) ? false : xPos = (xPos / mag);
	(yPos == 0) ? false : yPos = (yPos / mag);
}
