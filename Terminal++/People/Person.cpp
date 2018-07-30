#include "Person.h"
namespace People
{
	Person::Person(int _health)
	{
		m_name = "";
		HealthCurrent = _health;
		HealthMax = HealthCurrent;
	}
	Person::Person(std::string _name, int _health)
	{
		m_name = _name;
		HealthCurrent = _health;
		HealthMax = HealthCurrent;
	}
	Person::Person(Skills _skills, int _health)
	{
		skills = _skills;
		HealthCurrent = _health;
		HealthMax = HealthCurrent;
	}
	Person::Person(std::string _name, Skills _skills, int _health)
	{
		m_name = _name;
		skills = _skills;
		HealthCurrent = _health;
		HealthMax = HealthCurrent;
	}
	Person::~Person() { }
	bool Person::TakeDamage(int amount)
	{
		HealthCurrent -= amount;
		if (HealthCurrent <= 0)
			return true;
		if (HealthCurrent >= GetHealthMax())
			HealthCurrent = GetHealthMax();
		return false;
	}
	int Person::GetHealthMax() const
	{
		return HealthMax + (skills.DefenseSkill.GetCurLevel() / 5);
	}
	int Person::GetHealthCurrent() const
	{
		return HealthCurrent;
	}
	bool Person::IsFullHealth() const
	{
		return HealthCurrent == GetHealthMax();
	}
}
