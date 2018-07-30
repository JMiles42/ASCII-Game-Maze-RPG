#pragma once
#include "../UniversalHeader.h"
#include "../Entity/Entity.h"
#include "Skills.h"
namespace People
{
	class Person :
			public Entity
	{
	public:
		//Name of person
		//Never used
		std::string m_name;
		//The skills of the person
		//AI implimentation planed
		//NOT YET IMPLIMENTED
		Skills skills;
		//Health only constructer
		Person(int _health = 100);
		//Health And Name Cons
		Person(std::string _name, int _health = 100);
		//Skills and health Cons
		Person(Skills _skills, int _health = 100);
		//Full Const
		Person(std::string _name, Skills _skills, int _health = 100);
		~Person();
		//Method to handle taking damage
		virtual bool TakeDamage(int amount);
		//Get Max Health with skills Applied
		int GetHealthMax() const;
		//Getr Current health
		int GetHealthCurrent() const;
		//Compairs health vs max
		bool IsFullHealth() const;
	protected:
		int HealthMax;
		int HealthCurrent;
	};
}
