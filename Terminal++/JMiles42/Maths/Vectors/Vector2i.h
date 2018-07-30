#pragma once
#include "Direction.h"
#include <cmath>
class Vector2i
{
public:
	int yPos,xPos;
	//Game map bounds
	const static int MovementLimitsLeftX = 0;
	const static int MovementLimitsRightX = 57;
	const static int MovementLimitsTopY = 0;
	const static int MovementLimitsBottomY = 19;
	Vector2i();
	Vector2i(int _y, int _x);
	Vector2i(int _values);
	~Vector2i();
	Vector2i operator=(const int &amount) const;
	Vector2i operator+(const int &amount) const;
	Vector2i operator+(const Direction &dir) const;
	Vector2i operator+(const Vector2i &other) const;
	Vector2i operator*(const int &amount) const;
	Vector2i operator*(const Vector2i &other) const;
	Vector2i operator+=(const int &amount);
	Vector2i operator+=(const Direction &dir);
	Vector2i operator+=(const Vector2i &other);
	Vector2i operator-(const int &amount) const;
	Vector2i operator-(const Direction &dir) const;
	Vector2i operator-(const Vector2i &other) const;
	Vector2i operator-=(const int &amount);
	Vector2i operator-=(const Direction &amount);
	Vector2i operator-=(const Vector2i &other);
	bool operator==(const int &amount) const;
	bool operator==(const Vector2i &other) const;
	static void ClampVector(Vector2i &vecToClamp);
	void ClampVector();
	int GetMagnitudeSquared() const;
	static int DistanceBetween2Points(Vector2i a, Vector2i b);
	int GetMagnitude() const;
	void Normalise();
};
