#pragma once
enum class Direction
{
	Up = 0,
	Left,
	Down,
	Right
};
namespace DirectionHelper
{
	static void InvertDirection(Direction &dir)
	{
		switch (dir)
		{
		case Direction::Up:
			dir = Direction::Down;
			break;
		case Direction::Left:
			dir = Direction::Right;
			break;
		case Direction::Down:
			dir = Direction::Up;
			break;
		case Direction::Right:
			dir = Direction::Left;
			break;
		default: break;
		}
	}
};
