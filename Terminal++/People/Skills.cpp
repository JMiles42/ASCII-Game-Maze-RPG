#include "Skills.h"
Skills::Skills() { }
Skills::~Skills() {}
void Skills::operator=(Skills other)
{
	this->OffenseSkill = other.OffenseSkill;
	this->DefenseSkill = other.DefenseSkill;
	this->ShoppingSkill = other.ShoppingSkill;
}
