#include "Item.h"
#include "StackedItem.h"
#include "StaticItems.h"
namespace ItemSystem
{
	//Items shoul only ever be made at code time.
	Item::Item()
	{
		m_name = "Empty";
		m_desc = "";
		m_value = 0;
		m_sprite = ' ';
		m_rarity = Rarity::Common;
	}
	Item::Item(std::string _name, std::string _desc, int _cost, char _sprite, Rarity _rarity)
	{
		m_name = _name;
		m_desc = _desc;
		m_value = _cost;
		m_sprite = _sprite;
		m_rarity = _rarity;
	}
	Item::~Item() { }
	std::string Item::ToString() const
	{
		return "Item: " + m_name + " Its Value is: $" + std::to_string(m_value);
	}
	bool Item::operator ==(const Item &a) const
	{
		return (a.m_name == m_name);
	}
	char Item::GetSprite() const
	{
		return m_sprite;
	}
	int Item::GetValue() const
	{
		return m_value;
	}
	Rarity Item::GetRarity() const
	{
		return m_rarity;
	}
	std::string Item::GetName() const
	{
		return m_name;
	}
	std::string Item::GetDesc() const
	{
		return m_desc;
	}
	StackedItem Item::GetItemStack(int stackValue) const
	{
		return StackedItem(*this, stackValue);
	}
	Item::operator StackedItem() const
	{
		return GetItemStack();
	}
}
