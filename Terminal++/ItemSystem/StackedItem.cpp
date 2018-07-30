#include "StackedItem.h"
#include "StaticItems.h"
#include "Item.h"
namespace ItemSystem
{
	StackedItem::StackedItem()
	{
		m_itemInStack = &StaticItems::Empty;
		m_stackSize = 1;
	}
	StackedItem::StackedItem(const Item &_item, int _stackSize)
	{
		m_itemInStack = &_item;
		m_stackSize = _stackSize;
	}
	StackedItem::StackedItem(const Item *_item, int _stackSize)
	{
		m_itemInStack = _item;
		m_stackSize = _stackSize;
	}
	StackedItem::~StackedItem() { }
	std::string StackedItem::ToString() const
	{
		//If stack is "empty" return a differantly buit string
		if (m_itemInStack == &StaticItems::Empty)
			return "This item stack is empty.";
		return m_stackSize > 1 ?
				std::to_string(m_stackSize) + " " + m_itemInStack->GetName() + " Total Value: $" + std::to_string((m_itemInStack->GetValue() * m_stackSize)) :
				m_itemInStack->GetName() + " Total Value: $" + std::to_string((m_itemInStack->GetValue() * m_stackSize));
	}
	bool StackedItem::operator==(const StackedItem &otherItemStack) const
	{
		return (otherItemStack.m_itemInStack == m_itemInStack);
	}
	StackedItem StackedItem::operator +(const StackedItem &otherItemStack) const
	{
		StackedItem sI = *this;
		sI.m_stackSize += otherItemStack.m_stackSize;
		return sI;
	}
	StackedItem StackedItem::operator +(const int &valueToChangeBy) const
	{
		StackedItem sI = *this;
		sI.m_stackSize += valueToChangeBy;
		return sI;
	}
	StackedItem StackedItem::operator++()
	{
		m_stackSize++;
		return (*this);
	}
	StackedItem StackedItem::operator--()
	{
		m_stackSize--;
		return (*this);
	}
	StackedItem StackedItem::operator -(const StackedItem &otherItemStack) const
	{
		StackedItem sI = *this;
		sI.m_stackSize -= otherItemStack.m_stackSize;
		return sI;
	}
	StackedItem StackedItem::operator -(const int &valueToChangeBy) const
	{
		StackedItem sI = *this;
		sI.m_stackSize -= valueToChangeBy;
		return sI;
	}
	void StackedItem::operator +=(const StackedItem &otherItemStack)
	{
		m_stackSize += m_stackSize;
	}
	void StackedItem::operator +=(const int &valueToChangeBy)
	{
		m_stackSize += valueToChangeBy;
	}
	void StackedItem::operator -=(const StackedItem &otherItemStack)
	{
		m_stackSize -= otherItemStack.m_stackSize;
	}
	void StackedItem::operator -=(const int &valueToChangeBy)
	{
		m_stackSize -= valueToChangeBy;
	}
	StackedItem::operator int() const
	{
		return GetTotalValue();
	}
	StackedItem::operator std::string() const
	{
		return m_itemInStack->GetName();
	}
	int StackedItem::GetStackSize() const
	{
		return m_stackSize;
	}
	int StackedItem::GetTotalValue() const
	{
		return static_cast<int>(m_stackSize * static_cast<int>(m_itemInStack->GetValue()));
	}
	std::string StackedItem::GetItemName() const
	{
		return m_itemInStack->GetName();
	}
	std::string StackedItem::GetItemDesc() const
	{
		return m_itemInStack->GetDesc();
	}
	int StackedItem::GetItemValue() const
	{
		return m_itemInStack->GetValue();
	}
	Rarity StackedItem::GetItemRarity() const
	{
		return m_itemInStack->GetRarity();
	}
	char StackedItem::GetItemSprite() const
	{
		return m_itemInStack->GetSprite();
	}
	const Item * StackedItem::GetItem() const
	{
		return m_itemInStack;
	}
}
