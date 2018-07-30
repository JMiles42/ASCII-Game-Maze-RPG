#pragma once
#include "../UniversalHeader.h"
#include "Rarity.h"
namespace ItemSystem
{
	//Declare that there  is a class called StackedItem
	//To allow the opperater overload to be declaied
	class StackedItem;
	//Used only at compile time
	class Item
	{
	protected:
		//Items Name
		std::string m_name;
		//Items Description
		std::string m_desc;
		//The Sprite of the Item
		char m_sprite;
		//The value of the item
		int m_value;
		//The rarity, used mostly for colour id
		Rarity m_rarity;
	public:
		//Null Cons
		Item();
		//Full Cons
		Item(std::string _name, std::string _desc, int _cost, char _sprite, Rarity _rarity);
		~Item();
		//Returns a build string of the items info
		std::string ToString() const;
		//Gets The Items Name
		std::string GetName() const;
		//Gets The Item Description
		std::string GetDesc() const;
		//Gets The Item Char Sprite
		char GetSprite() const;
		//Gets The Item Value
		int GetValue() const;
		//Gets The Item Rarity
		Rarity GetRarity() const;
		//Compair Item Opperater
		bool operator==(const Item &a) const;
		//Get Item in an item stack with Optional size
		StackedItem GetItemStack(int stackValue = 1) const;
		//Easly create an item stack of this item
		operator StackedItem() const;
	};
}
