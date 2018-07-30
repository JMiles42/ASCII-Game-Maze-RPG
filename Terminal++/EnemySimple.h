#pragma once
#include "People/Person.h"
#include "RequiredVariables.h"
class EnemySimple :
		public People::Person
{
public:
	//States, NOT IMPLIMENTED
	enum class EnemyState
	{
		Idle,
		Walking,
		Attacking
	};
	//Current state, can only wonder.
	EnemyState state;
	EnemySimple();
	//Spawns Enemy at pos, with seed, for pathing
	EnemySimple(Vector2i pos, int seed = time(nullptr));
	~EnemySimple();
	bool TakeDamage(int amount) override;
	//Calculate weather to move, stay or NOT IMPLIMENTED chase player
	bool Update();
	//Get Next Dir, This replaced a randomly generated dir as it would get stuck in loops.
	Direction GetNewDir() const;
private:
	//Walk length before next action
	int walkLength = 5;
	//Previous direction
	Direction prevDir;
	//Queue of future paths
	//These loop around back on to its self, as it should get first, remove first, and ad it to last
	std::queue<std::pair<Direction, int>> path;
	//How far have i currently walked
	int currentWalkLength = 0;
	//Init queue path
	void EnQueuePath();
	//MY PRNGs
	std::mt19937 rd;
	std::uniform_int_distribution<> dist = std::uniform_int_distribution<>(0, 3);
};
