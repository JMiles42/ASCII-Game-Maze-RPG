#include "Player.h"
namespace People
{
	Player::Player()
	{
		m_name = "Player";
		inventory = ItemSystem::Inventory();
	}
	Player::~Player() { }
	bool Player::TakeDamage(int amount)
	{
		return Person::TakeDamage(amount);
	}
	int Player::GetDPS() const
	{
		return damage + (skills.OffenseSkill.GetCurLevel() / 2);
	}
}
