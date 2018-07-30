#pragma once
#include "../UniversalHeader.h"
class Skill
{
public:
	//The only Skill Cons
	//Name, current Level, Max Level
	Skill(std::string _name, int _level, int _maxLevel);
	~Skill();
	//Comapres two skills
	void operator=(Skill other);
	//Gets current level
	int GetCurLevel() const;
	//Get max level
	int GetMaxLevel() const;
	//Gets name
	std::string GetName() const;
	//Upgrade the skill by amount
	bool UpgradeSkill(int amount);
	//Add one to skill
	int operator++();
	//Checks if skill is at max level
	bool AtMaxLevel() const;
private:
	//Skill name
	std::string name;
	//Skill Max Level
	int maxLevel;
	//Skill Current level
	int curLevel;
};
