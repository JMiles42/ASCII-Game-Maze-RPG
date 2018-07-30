#include "Skill.h"
Skill::Skill(std::string _name, int _level, int _maxLevel)
{
	name = _name;
	curLevel = _level;
	maxLevel = _maxLevel;
}
Skill::~Skill() {}
void Skill::operator=(Skill other)
{
	this->name = other.GetName();
	this->maxLevel = other.GetMaxLevel();
	this->curLevel = other.GetCurLevel();
}
int Skill::GetCurLevel() const
{
	return curLevel;
}
int Skill::GetMaxLevel() const
{
	return maxLevel;
}
std::string Skill::GetName() const
{
	return name;
}
bool Skill::UpgradeSkill(int amount)
{
	if ((curLevel + amount) < maxLevel)
	{
		curLevel += amount;
		return true;
	}
	curLevel = maxLevel;
	return false;
}
int Skill::operator++()
{
	curLevel++;
	return curLevel;
}
bool Skill::AtMaxLevel() const
{
	return curLevel >= maxLevel;
}
