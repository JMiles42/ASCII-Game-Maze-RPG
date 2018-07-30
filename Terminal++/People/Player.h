#pragma once
#include "Person.h"
#include "../UniversalHeader.h"
#include "../Inventory/Inventory.h"
namespace People
{
	class Player :
			public Person
	{
	public:
		//The players inventory for storing items
		ItemSystem::Inventory inventory;
		Player();
		~Player();
		bool TakeDamage(int amount) override;
		//Gets player Damage Per Shot
		int GetDPS() const;
	private:
		int damage = 1;
	};
}
