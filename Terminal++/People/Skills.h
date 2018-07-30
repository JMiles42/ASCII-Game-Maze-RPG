#pragma once
#include "Skill.h"
//Simple container class for easier orginisation in Person
class Skills
{
public:
	Skills();
	~Skills();
	void operator=(Skills other);
	Skill OffenseSkill = Skill("Offense", 0, 90000);
	Skill DefenseSkill = Skill("Defense", 0, 999999);
	Skill ShoppingSkill = Skill("Shopping", 0, 1000);
};
