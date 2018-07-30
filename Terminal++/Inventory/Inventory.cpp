#include "Inventory.h"
namespace ItemSystem
{
	Inventory::Inventory() { }
	Inventory::~Inventory() { }
	void Inventory::Clear()
	{
		Items.clear();
	}
	bool Inventory::HasSpaceForNewItem() const
	{
		return (Items.size() < 314);
	}
	void Inventory::AddNewItem(StackedItem item)
	{
		//Checks if item is in invetory if it is add stack amount to it
		for (auto &itm : Items)
		{
			if (itm.GetItem() == item.GetItem())
			{
				itm.m_stackSize += item.m_stackSize;
				return;
			}
		}
		//else add stack it inv
		Items.push_back(item);
	}
	void Inventory::AddNewItemStack(StackedItem item)
	{
		//Add item to inventory
		Items.push_back(item);
	}
	std::string Inventory::ToString()
	{
		//For every items in inventory get is string
		//Unless its empty, the add to the empty count
		std::string s = "";
		int emptySlots = 314 - Items.size();
		for (auto &i : Items)
		{
			if (i.GetItem() == &StaticItems::Empty)
				emptySlots++;
			else
			{
				s += i.ToString();
				s += "\n";
			}
		}
		if (emptySlots > 0)
		{
			s += "There are: ";
			s += std::to_string(emptySlots);
			s += " empty slots available.\n";
		}
		return s;
	}
}
