#pragma once
#include"../UniversalHeader.h"
#include "../ItemSystem/Item.h"
namespace ItemSystem
{
	//Declare that there  is a class called Item
	//To allow the opperater overload to be declaied
	class Item;
	class StackedItem
	{
	public:
		//Item in stack adress in memory
		const Item *m_itemInStack;
		//Item stack amount
		unsigned int m_stackSize = 1;
		//Blank Cons
		StackedItem();
		//Item ref cons
		StackedItem(const Item &_item, int _stackSize = 1);
		//Item adress cons
		StackedItem(const Item *_item, int _stackSize = 1);
		~StackedItem();
		//Simple String of info in the item stack
		std::string ToString() const;
		//Overloaded Opperatoers to change the stack size
		bool operator ==(const StackedItem &a) const;
		//Overloaded Opperatoers to change the stack size
		StackedItem operator +(const StackedItem &a) const;
		//Overloaded Opperatoers to change the stack size
		StackedItem operator +(const int &a) const;
		//Overloaded Opperatoers to change the stack size
		StackedItem operator ++();
		//Overloaded Opperatoers to change the stack size
		StackedItem operator --();
		//Overloaded Opperatoers to change the stack size
		StackedItem operator -(const StackedItem &a) const;
		//Overloaded Opperatoers to change the stack size
		StackedItem operator -(const int &a) const;
		//Overloaded Opperatoers to change the stack size
		void operator +=(const StackedItem &a);
		//Overloaded Opperatoers to change the stack size
		void operator +=(const int &a);
		//Overloaded Opperatoers to change the stack size
		void operator -=(const StackedItem &a);
		//Overloaded Opperatoers to change the stack size
		void operator -=(const int &a);
		//Get stacksize operater
		operator int() const;
		//Get string operater
		operator std::string() const;
		// Get SDtackSize
		int GetStackSize() const;
		//Get Total value of stack
		int GetTotalValue() const;
		//Get Item Name
		std::string GetItemName() const;
		//Get Item Descrition
		std::string GetItemDesc() const;
		// Get Item Vlaue 
		int GetItemValue() const;
		// Get Item Rarity
		Rarity GetItemRarity() const;
		//Get Item Char Sprite
		char GetItemSprite() const;
		//Get Item adress
		const Item * GetItem() const;
	};
}
