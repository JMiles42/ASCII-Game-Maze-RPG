#pragma once
#include "../UniversalHeader.h"
#include "../ItemSystem/Item.h"
namespace ItemSystem { namespace StaticItems
{
	//Blank Item
	//SHOULD NEVER BE USED
	//EXISTS FOR THE POTENTIAL TO COMPARE TO THIS
	const static Item Empty = Item();
	//The following are all the items in the game
	//As Items should be only created in source code, this is where that is.
	const static Item Gold = Item("Gold", "Its shiny!", 100, '#', Rarity::Rare);
	const static Item Money = Item("CashMunie", "You Buy Things With It!\n \"Not For Resale...\"", 1, '$', Rarity::Common);
	const static Item Lewt = Item("Lewt", "LEWT, SWEET PRESCIUS LUTE", 1, 'l', Rarity::Common);
	const static Item RareLewt = Item("Lewt", "LEWT, SWEET! PRESCIUS LUTE", 2, 'l', Rarity::Rare);
	const static Item LedgLute = Item("Lute", "LUTE, SWEET! PRESCIUS! GLORIOUSLY! LUTE, THATS MINE, ALL MYNE!", 4, 'L', Rarity::Ledgendary);
#pragma region Loot
	const static Item SwordOfAmmo = Item("Sword of Endless Ammo", "Never runs out of ammo, Requires at least one to use.\n *Ammo sold seperatly.", 100, 'S', Rarity::Ledgendary);
	const static Item GunOfMelee = Item("Gun Of Hitting", "Can only be used as a melee weapon.\n Does not contain space for a clip or a trigger.", 200, 'G', Rarity::Ledgendary);
	const static Item UnrealisticGoals = Item("Unrealistic Goals", "This item has infinite uses, never runs out and one hits everything. \nCan only be uses if you are level 42.\nHowever there are no levels so you can't use it XD.", 10000, '&', Rarity::Ledgendary);
#pragma endregion
#pragma region Stat Increses
	//REMOVED DO TO NOT HAVING ENOUGH TIME TO IMPLIMENT
	//Was ment to upgrade it skill, just not implimented
	//const static Item HealthPotionC = Item("Health ++", "Use this to increse your Health. x1", 100, 'H', Rarity::Common);
	//const static Item HealthPotionR = Item("Health ++", "Use this to increse your Health. x2", 1000, 'H', Rarity::Rare);
	//const static Item HealthPotionL = Item("Health ++", "Use this to increse your Health. x4", 10000, 'H', Rarity::Ledgendary);
	//const static Item OffenseBoostC = Item("Offense ++", "Use this to increse your Offense. x1", 100, 'O', Rarity::Common);
	//const static Item OffenseBoostR = Item("Offense ++", "Use this to increse your Offense. x2", 1000, 'O', Rarity::Rare);
	//const static Item OffenseBoostL = Item("Offense ++", "Use this to increse your Offense. x4", 10000, 'O', Rarity::Ledgendary);
	//const static Item DefenseBoostC = Item("Defense ++", "Use this to increse your Defense. x1", 100, 'D', Rarity::Common);
	//const static Item DefenseBoostR = Item("Defense ++", "Use this to increse your Defense. x2", 1000, 'D', Rarity::Rare);
	//const static Item DefenseBoostL = Item("Defense ++", "Use this to increse your Defense. x4", 10000, 'D', Rarity::Ledgendary);
	//const static Item ShoppingBoostC = Item("Shopping ++", "Use this to increse your Shopping. x1", 100, 'S', Rarity::Common);
	//const static Item ShoppingBoostR = Item("Shopping ++", "Use this to increse your Shopping. x2", 1000, 'S', Rarity::Rare);
	//const static Item ShoppingBoostL = Item("Shopping ++", "Use this to increse your Shopping. x4", 10000, 'S', Rarity::Ledgendary);
	//const static Item StatsBoostC = Item("Stats ++", "Use this to increse all your Stats. x1", 500, 'Z', Rarity::Common);
	//const static Item StatsBoostR = Item("Stats ++", "Use this to increse all your Stats. x2", 5000, 'Z', Rarity::Rare);
	//const static Item StatsBoostL = Item("Stats ++", "Use this to increse all your Stats. x4", 50000, 'Z', Rarity::Ledgendary);
#pragma endregion
}}
