#pragma once
int GetItemPosInVector(int y, int x)
{
	return ((y - InventoryWindowTopY) * InventoryWindow.GetWidth() + (x - InventoryWindowLeftX));
}
void PlayerStatsClicked(int y, int x);
void ScreenClicked(int y, int x)
{
	/*
	x=width : y=height
	|-----------------------------------------------|-------------------------------------------------------	|
	|1x:1y			58x:1y	|	60x:1y			98x:1y	|
	|						|			Inv				|
	|						|	60x:8y			98x:8y	|
	|						|-------------------------------------------------------|
	|		Game			|	60x:10y			98x:10y	|
	|						|			Player Info			|
	|						|	60x:17y			98x:17y	|
	|						|-------------------------------------------------------|
	|	1x20y		58x:20y	|	60x:19y			98x:19y	|
	|-----------------------------------------------	|							|
	|	1x:22y		58x:22y	|							|
	|			Log			|			Item Stats			|
	|	1x:38y		58x:38y	|	60x:38y			98x:38y	|
	|-----------------------------------------------|-------------------------------------------------------	|
	*/
	/*
	const static int GameWindowLeftX = 1;
	const static int GameWindowRightX = 58;
	const static int GameWindowTopY = 1;
	const static int GameWindowBottomY = 20;

	const static int InventoryWindowLeftX = 60;
	const static int InventoryWindowRightX = 98;
	const static int InventoryWindowTopY = 1;
	const static int InventoryWindowBottomY = 8;

	const static int LogWindowLeftX = 1;
	const static int LogWindowRightX = 58;
	const static int LogWindowTopY = 22;
	const static int LogWindowBottomY = 38;

	const static int PlayerInfoWindowLeftX = 60;
	const static int PlayerInfoWindowRightX = 98;
	const static int PlayerInfoWindowTopY = 10;
	const static int PlayerInfoWindowBottomY = 17;

	const static int ItemInfoWindowLeftX = 60;
	const static int ItemInfoWindowRightX = 98;
	const static int ItemInfoWindowTopY = 19;
	const static int ItemInfoWindowBottomY = 38;
	*/
#ifdef DebugClick
	mvaddch(y, x, '%');
#endif
#pragma region GameWindow
	if
	(
		x >= GameWindowLeftX &&
		x <= GameWindowRightX &&
		y >= GameWindowTopY &&
		y <= GameWindowBottomY
	)
	{
#ifdef DebugClickLog
		LogWindow.Log("You Clicked In The Game Window.");
#endif
		//Allow the user to click the screen and move the player if cheats are enabled
		if (Cheating)
		{
			player.oldPosition = player.position;
			player.position = Vector2i(y - 1, x - 1);
			DrawPlayer();
		}
	}
#pragma endregion
#pragma region InventoryWindow
	else if
	(
		x >= InventoryWindowLeftX &&
		x <= InventoryWindowRightX &&
		y >= InventoryWindowTopY &&
		y <= InventoryWindowBottomY
	)
	{
#ifdef DebugClickLog
		LogWindow.Log("You Clicked In The Inventory.");
#endif
		//Display Item at y/x cords
		DisplayItem(y, x);
	}
#pragma endregion
#pragma region LogWindow
	else if
	(
		x >= LogWindowLeftX &&
		x <= LogWindowRightX &&
		y >= LogWindowTopY &&
		y <= LogWindowBottomY
	)
	{
#ifdef DebugClickLog
		LogWindow.Log("You Clicked In The Log Window.");
#endif
	}
#pragma endregion
#pragma region PlayerInfoWindow
	else if
	(
		x >= PlayerInfoWindowLeftX &&
		x <= PlayerInfoWindowRightX &&
		y >= PlayerInfoWindowTopY &&
		y <= PlayerInfoWindowBottomY
	)
	{
		//Check if the user click on any of ther interactable parts
		PlayerStatsClicked(y, x);
#ifdef DebugClickLog
		LogWindow.Log("You Clicked In The Player Info Window.");
#endif
	}
#pragma endregion
#pragma region ItemInfoWindow
	else if
	(
		x >= ItemInfoWindowLeftX &&
		x <= ItemInfoWindowRightX &&
		y >= ItemInfoWindowTopY &&
		y <= ItemInfoWindowBottomY
	)
	{
#ifdef DebugClickLog
		LogWindow.Log("You Clicked In The Item Info window.");
#endif
		//Check if the sell button was clicked
		if (y == ItemInfoWindowBottomY && x > (ItemInfoWindowLeftX + 9) && x < (ItemInfoWindowLeftX + 9 + 9 + 6))
		{
			//If the pointer is not null else BAIL
			if (selectedItem)
			{
				//If the user has no shpping skill, don't allow the sellin of there money
				//As there SHOULD be no gain
				if (selectedItem == &player.inventory.Items[0] && player.skills.ShoppingSkill.GetCurLevel() == 0)
				{
					LogWindow.Log("Why are you trying to sell your " + player.inventory.Items[0].GetItemName() + ".");
					return;
				}
				//Get total value Item stack will be sold for
				int itemSellValue = static_cast<int>(selectedItem->GetTotalValue() * (player.skills.ShoppingSkill.GetCurLevel() / 100 + 1));
				//Add amount to money
				player.inventory.Items[0].m_stackSize += itemSellValue;
				LogWindow.Log(selectedItem->GetItemName() + " Has Been Sold.");
				LogWindow.Log(std::to_string(itemSellValue) + " Funds Added to your account.");
				//Remove item if it snot money
				if (selectedItem != &player.inventory.Items[0])
				{
					LogWindow.Log("Sold");
					if (*selectedItemIndex != 9999)
						player.inventory.Items.erase(player.inventory.Items.begin() + (*selectedItemIndex));
					selectedItem = nullptr;
					*selectedItemIndex = 9999;
				}
				//Tell refresh thread to redraw window
				ReWriteInv = true;
				//Print Item info to screen
				PrintItemInfoToScreen(selectedItem);
				DisplayPlayerStats();
			}
		}
	}
#pragma endregion
}
void DisplayItem(int y, int x)
{
	//Get locolized cords
	x -= InventoryWindowLeftX;
	y -= InventoryWindowTopY;
	//Calculate item pos
	int invPos = (y * InventoryWindow.GetWidth() + x);
	//Check if there is a item at this position
	if (player.inventory.Items.size() > (invPos))
	{
		//Store the item pos
		(*selectedItemIndex) = invPos;
		//Change selected item to item
		selectedItem = &player.inventory.Items[invPos];
		//Print items info to screen
		PrintItemInfoToScreen(selectedItem);
	}
	else
	{
		//Make selected item null
		selectedItem = nullptr;
		//Set index to my hardcoded nullRef
		*selectedItemIndex = 9999;
		//Print no item info
		PrintNullItemInfo();
	}
}
void PrintNullItemInfo()
{
	InfoPanel.Clear();
	InfoPanel.Print(0, 0, "Item Info:");
	InfoPanel.Print(1, 0, "Please select an Item in your inventory");
	InfoPanel.Print(2, 0, "to Display its stats.");
}
void PrintItemInfoToScreen(ItemSystem::StackedItem *item)
{
	if (!item)
	{
		PrintNullItemInfo();
		return;
	}
	InfoPanel.Clear();
	//This exists to make adding more lines easier
	int yPos = 0;
	InfoPanel.Print(yPos, 0, "Item Info:", false);
	yPos++;
	InfoPanel.Print(yPos, 0, item->GetItemName(), static_cast<SubWindowWithBorder::Colour>(item->GetItemRarity()), false);
	yPos++;
	InfoPanel.Print(yPos, 0, "StackSize: " + std::to_string(item->GetStackSize()), false);
	yPos++;
	yPos++;
	InfoPanel.Print(yPos, 0, "Description: ", false);
	yPos++;
	InfoPanel.Print(yPos, 0, item->GetItemDesc(), false);
	InfoPanel.Print(InfoPanel.GetHeight() - 3, 0, MakeStringLength(15, "Per Item Value: ") + std::to_string(item->GetItemValue()), false);
	InfoPanel.Print(InfoPanel.GetHeight() - 2, 0, MakeStringLength(15, "Total Value: ") + std::to_string(item->GetTotalValue()), false);
	//39
	InfoPanel.Print(InfoPanel.GetHeight() - 1, 0, ("Actions: SELL Item Stack"), SubWindowWithBorder::Colour::Yellow, false);
	InfoPanel.Refresh();
}
void PlayerStatsClicked(int y, int x)
{
	//12 healing 91-94
	//88-94
	//14 defense
	//15 offense
	//16 shopping
	if (x >= 88 && x <= 94)
	{
		//If user can't afford show message and bail
		if (player.inventory.Items[0].m_stackSize < 100)
		{
			LogWindow.Log("I can't afford my upgrades");
			return;
		}
		if (y == 14)
		{
			player.skills.DefenseSkill.UpgradeSkill(9);
			player.inventory.Items[0].m_stackSize -= 100;
		}
		else if (y == 15)
		{
			player.skills.OffenseSkill.UpgradeSkill(5);
			player.inventory.Items[0].m_stackSize -= 100;
		}
		else if (y == 16)
		{
			player.skills.ShoppingSkill.UpgradeSkill(1);
			player.inventory.Items[0].m_stackSize -= 100;
		}
		if (x >= 91 && y == 12)
		{
			//Heal player
			player.TakeDamage(-10);
			player.inventory.Items[0].m_stackSize -= 100;
		}
		DisplayPlayerStats();
	}
}
