#pragma once
#include "../UniversalHeader.h"
#include "../ItemSystem/Item.h"
#include "../ItemSystem/StackedItem.h"
#include "../ItemSystem/StaticItems.h"
namespace ItemSystem
{
	class Inventory
	{
	public:
		//Max size for the players inv, the total area of the inventory window
		const static int PlayerInvMax = 312;
		//The Items in the inventory
		std::vector<StackedItem> Items;
		Inventory();
		~Inventory();
		//Clears the inventory vector
		void Clear();
		//Checks if there is space in inv
		bool HasSpaceForNewItem() const;
		//Adds Items to stack count if exists elss adds to new stack
		void AddNewItem(StackedItem item);
		//Adds as new stack requardless of if a stack already exitss
		void AddNewItemStack(StackedItem item);
		//Invetory to string
		std::string ToString();
	};
}
