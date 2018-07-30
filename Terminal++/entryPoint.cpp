#include "entryPoint.h"
//Declare the extern vars from required vars
SubWindowWithBorder GameWindow;
SubWindowWithBorder InventoryWindow;
SubWindowWithBorder InfoPanel;
SubWindowWithBorder PlayerInfoPanel;
SubWindowWithBorder LogWindow;
Map currentMap;
//This is the double buffer so that the player and enemies can be rendered with the map, not on top of the map
std::vector<std::vector<Map::Tile>> mapDisplay = Map(CSVReader::LoadCSVFile("GameData/Maps/start_scrn.csv")).LevelData;
bool needNewMap = false;
bool playerDead = false;
Map nextMap = Map(static_cast<int>(time(nullptr) + 42));
People::Player player;
bool gameRunning = false;
int main()
{
	srand(time(nullptr));
	InitConsoleWindow();
	MEVENT mouseinput;
	//Not sure what all of these do, but I saw them in a mouse click demo and well they make it work so... I keeped them
	{
		initscr();
		raw();
		nodelay(stdscr, 1);
		//Disable Curser
		curs_set(0);
		nonl();
		keypad(stdscr, 1);
	}
	ThreadStart();
	mousemask(ALL_MOUSE_EVENTS, nullptr);
	InitGameWindows();
	selectedItemIndex = new int;
	*selectedItemIndex = 9999;
	bool restartGame = false;
	bool firing = false;
	while (!restartGame)
	{
		long input = 0;
		const SubWindowWithBorder::Colour gunCol = SubWindowWithBorder::Colour::Yellow;
		LogWindow.Log("Hello, and welcome to this cave, I am your ShootyMcGun41+4-2+5-6", gunCol);
		LogWindow.Log("Please, use the \"D\" door to leave.", gunCol);
		LogWindow.Log("\"L\" & \"C\" are loot, and loot chests and your Invetory, and stats are to the right of you at all times, not sure how you see them then...", gunCol);
		LogWindow.Log("Along with the buttons to upgrade them.\nWow I realy didn't think this through. I don't know how you use them?", gunCol);
		LogWindow.Log("If you happen across an \"@\" they aren't GOOD NEWS EVERYONE, nvm They are bad. Shoot them by using \"space\" whatever that is. Then point in a direction.", gunCol);
		LogWindow.Log("\nPress the anykey to start.", gunCol);
		LogWindow.Log("Please note if the anykey is not accesable\nI'm sorry.\nYou should probly just leave.", gunCol);
		GameWindow.Refresh();
		PrintNullItemInfo();
		StartScrn();
		player.inventory.Clear();
		player.inventory.AddNewItem((&ItemSystem::StaticItems::Money));
		DisplayInventory();
		DisplayPlayerStats();
		//A realy bad wait for user input loop YAAY
		while ((input = wgetch(stdscr)) == -1) { }
		StartRoom();
		DrawPlayer();
		gameRunning = true;
		while (gameRunning && !playerDead)
		{
			input = wgetch(stdscr);
			switch (input)
			{
			case KEY_MOUSE:
				nc_getmouse(&mouseinput);
				if (mouseinput.bstate == BUTTON1_PRESSED)
				{
					//LogWindow.Log("MouseClick");
					//LogWindow.Log(std::to_string(mouseinput.x) + "x  : " + std::to_string(mouseinput.y) + "y");
					ScreenClicked(mouseinput.y, mouseinput.x);
					refresh();
				}
				break;
			case 'w':
			case 'W':
				//Up Arrow
			case 259:
#ifdef WalkingDirMessages
				LogWindow.Log("Up");
#endif // WalkingDirMessages
				if (firing)
					FireWeapon(Direction::Up, &firing);
				else
					MovePlayer(Direction::Up);
#ifdef InventoryCheats
				if (player.inventory.HasSpaceForNewItem())
					player.inventory.AddNewItem(&ItemSystem::StaticItems::GunOfMelee);
#endif
				break;
			case 'a':
			case 'A':
				//Left Arrow
			case 260:
#ifdef WalkingDirMessages
				LogWindow.Log("Left");
#endif // WalkingDirMessages
				if (firing)
					FireWeapon(Direction::Left, &firing);
				else
					MovePlayer(Direction::Left);
#ifdef InventoryCheats
				if (player.inventory.HasSpaceForNewItem())
					player.inventory.AddNewItem(ItemSystem::StaticItems::SwordOfAmmo.GetItemStack(5));
#endif
				break;
			case 's':
			case 'S':
				//Down Arrow
			case 258:
#ifdef WalkingDirMessages
				LogWindow.Log("Down");
#endif // WalkingDirMessages
				if (firing)
					FireWeapon(Direction::Down, &firing);
				else
					MovePlayer(Direction::Down);
#ifdef InventoryCheats
				if (player.inventory.HasSpaceForNewItem())
					player.inventory.AddNewItem(&ItemSystem::StaticItems::Gold);
#endif
				break;
			case 'd':
			case 'D':
				//Right Arrow
			case 261:
#ifdef WalkingDirMessages
				LogWindow.Log("Right");
#endif // WalkingDirMessages
				if (firing)
					FireWeapon(Direction::Right, &firing);
				else
					MovePlayer(Direction::Right);
#ifdef InventoryCheats
				if (player.inventory.HasSpaceForNewItem())
					player.inventory.AddNewItemStack(&ItemSystem::StaticItems::Gold);
#endif
				break;
			case ' ':
#ifdef WalkingDirMessages
				LogWindow.Log("Attack");
#endif // WalkingDirMessages
				firing = true;
				LogWindow.Log("Hmmmmm. In what Direction should I shoot", SubWindowWithBorder::Colour::Green);
				//{
				//	LogWindow.Log("BANG BANG, I shoot my gun. BANG BANG, It hits the ground.", SubWindowWithBorder::Colour::Green);
				//	LogWindow.Log("Bloody hell, I drop it everytime.", SubWindowWithBorder::Colour::Purple);
				//}
				break;
			case 'q':
			case 'Q':
				//Escape
			case 27:
				gameRunning = MessageBoxYesNo("Warning!\nWould you like to Quit the game?", "Quitting Game???");
				break;
			case 'k':
			case 'K':
				gameRunning = !player.TakeDamage(99);
				break;
			case 'r':
			case 'R':
				restartGame = MessageBoxYesNo("Warning!\nWould you like to Restart the game?", "Restart the Game???");
				break;
			case 'e':
			case 'E':
#ifdef InventoryCheats
				if (player.inventory.HasSpaceForNewItem())
					player.inventory.AddNewItemStack(&ItemSystem::StaticItems::DefenseBoostC);
				if (player.inventory.HasSpaceForNewItem())
					player.inventory.AddNewItemStack(&ItemSystem::StaticItems::DefenseBoostR);
				if (player.inventory.HasSpaceForNewItem())
					player.inventory.AddNewItemStack(&ItemSystem::StaticItems::DefenseBoostL);
#endif
				break;
			case 'P':
			case 'p':
				Cheating = !Cheating;
				LogWindow.Log((Cheating ? "Cheats On" : "Cheats Off"), SubWindowWithBorder::Colour::Red);
				break;
			default:
				//LogWindow.Log(std::to_string(input));
				break;
			}
			DisplayInventory();
		}
		EndScrn();
		restartGame = !MessageBoxYesNo("You are dead... Restart?", "YOU ARE DEAD!!!");
	}
	endwin();
	delete selectedItemIndex;
}
#include "InitWindows.h"
void ThreadStart()
{
	//Auto Refresh the console
	std::thread refreshThread(TerminalUpdate);
	refreshThread.detach();
	std::thread mapGenThread(GenerateNewMap, (&nextMap));
	mapGenThread.detach();
}
void StartScrn()
{
	//Load start screen
	mapDisplay = Map(CSVReader::LoadCSVFile("GameData/Maps/start_scrn.csv")).LevelData;
	DisplayMap(mapDisplay);
}
void EndScrn()
{
	//Load end screen
	mapDisplay = Map(CSVReader::LoadCSVFile("GameData/Maps/end_scrn.csv")).LevelData;
	DisplayMap(mapDisplay);
}
void TerminalUpdate()
{
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
		renderLock.lock();
		{
			curses::terminal.update();
			InventoryWindow.Refresh();
			GameWindow.Refresh();
			InfoPanel.Refresh();
			PlayerInfoPanel.Refresh();
		}
		renderLock.unlock();
	}
}
bool MessageBoxYesNo(std::string text, std::string title)
{
	int msgBox = MessageBox(nullptr, TEXT((text.c_str())), TEXT(title.c_str()), MB_YESNO);
	if (msgBox == IDYES)
		return true;
	return false;
}
void DisplayInventory()
{
	if (!ReWriteInv)
		return;
	ReWriteInv = false;
	InventoryWindow.Clear();
	if (player.inventory.Items.size() == 0)
		return;
	const int width = InventoryWindow.GetWidth();
	int row = 0;
	int offset = 0;
	//For every item in inventory add it to the screen
	for (int i = 0; i < player.inventory.Items.size(); i++)
	{
		InventoryWindow.Print(row, offset,
			player.inventory.Items[i].GetItemSprite(),
			static_cast<int>(player.inventory.Items[i].GetItemRarity()));
		offset++;
		//Calculate the position of the next char
		if (i > (width * (1 + row)))
		{
			row++;
			offset = 0;
		}
	}
	InventoryWindow.Refresh();
}
void DrawPlayer()
{
	//Shouldn't be needed before every movement, however some visual glitches were fixed this way.
	currentMap.CalculateColour();
	//Make the displayed map the current map
	mapDisplay = currentMap.LevelData;
	//Draw enemies on the mapDisplay
	EnemyDraw();
	//Set player pos
	mapDisplay[player.position.yPos][player.position.xPos] = Map::Tile(Map::TileType::Player, SubWindowWithBorder::Colour::Green);
	//Render map
	DisplayMap(mapDisplay);
}
//Start game room
void StartRoom()
{
	player.position = currentMap.GetSpawnPoint();
	player.position.ClampVector();
	EnemySpawn();
	DrawPlayer();
}
void EnemySpawn()
{
	enemies.clear();
	for (auto &point : currentMap.enemySpawns)
		enemies.push_back(EnemySimple(point, time(nullptr) + enemies.size()));
}
void EnemyCalc()
{
	for (auto &enemy : enemies)
		enemy.Update();
}
void EnemyDraw()
{
	for (auto &enemy : enemies)
		mapDisplay[enemy.position.yPos][enemy.position.xPos] = Map::Tile(Map::TileType::Enemy, SubWindowWithBorder::Colour::Red);
}
void DisplayMap(std::vector<std::vector<Map::Tile>> &map)
{
	for (int y = 0; y < map.size(); y++)
		for (int x = 0; x < map[y].size(); x++)
			GameWindow.Print(y, x, static_cast<char>(map[y][x].tile), map[y][x].colour, false);
	GameWindow.Refresh();
}
bool MovePlayer(Direction dir)
{
	Vector2i newPos = player.position + dir;
	player.ClampVector(newPos);
	Map::TileType tile = static_cast<Map::TileType>(*currentMap[newPos]);
	switch (tile)
	{
	case Map::TileType::Air:
		break;
	case Map::TileType::Wall:
		//If cheating dont care about walls XD
		if (Cheating)
			break;
		LogWindow.Log("That is a wall, Why would I walk into that.", SubWindowWithBorder::Colour::Yellow);
		return false;
	case Map::TileType::Chest:
		PlayerLootChestGet();
		LogWindow.Log("Sweet a chest.", SubWindowWithBorder::Colour::Green);
		*currentMap[newPos] = Map::TileType::LootedChest;
		break;
	case Map::TileType::LootedChest:
		LogWindow.Log("Sweet a chest.", SubWindowWithBorder::Colour::Green);
		LogWindow.Log("Wait, this looks familier. Damn it I've been here before.", SubWindowWithBorder::Colour::Yellow);
		break;
	case Map::TileType::Loot:
		PlayerLootGet();
		LogWindow.Log("Wow free stuff just laying on the ground. \nYoink!", SubWindowWithBorder::Colour::Green);
		*currentMap[newPos] = Map::TileType::Air;
		break;
	case Map::TileType::LoadedAir:
		LogWindow.Log("I don't know what this is...\nI should go back.", SubWindowWithBorder::Colour::Yellow);
		LogWindow.Log("Letter from the DEV", SubWindowWithBorder::Colour::Red);
		LogWindow.Log("How did this tile get here, this is a dev only tile, if you are reading this.\nCongrats You have found a bug... I mean a feature.", SubWindowWithBorder::Colour::Red);
		break;
	case Map::TileType::EnemySpawn:
		LogWindow.Log("I don't know what this is...\nI should go back.", SubWindowWithBorder::Colour::Yellow);
		LogWindow.Log("Letter from the DEV", SubWindowWithBorder::Colour::Red);
		LogWindow.Log("If you see this you should be fighting an enemy, but for some reason it didn't spawn.\nCongrats! You have found a bug... I mean a feature.", SubWindowWithBorder::Colour::Red);
		break;
	case Map::TileType::Door:
		LogWindow.Log("Guess I'll go through this door.", SubWindowWithBorder::Colour::Green);
		LoadInNextMap();
		return true;
	case Map::TileType::Teleporter:
		player.position = currentMap.GetTeleporterPoint();
		LogWindow.Log("Wait... Where am I?", SubWindowWithBorder::Colour::Green);
		player.position.ClampVector();
		EnemyCalc();
		DrawPlayer();
		return true;
	default:
		LogWindow.Log("I don't know what this is...\nI should go back.", SubWindowWithBorder::Colour::Yellow);
		LogWindow.Log("Letter from the DEV", SubWindowWithBorder::Colour::Red);
		LogWindow.Log("You have walked into somthing that is not a tile. I don't even... You have found a bug... I mean a feature.", SubWindowWithBorder::Colour::Red);
		return false;
	}
	player.position += dir;
	player.position.ClampVector();
	DrawPlayer();
	EnemyCalc();
	DisplayPlayerStats();
	return true;
}
void GenerateNewMap(Map *newMap)
{
	while (true)
	{
		if (needNewMap)
		{
			if (gameRunning)
				LogWindow.Log("Generating Next Level", SubWindowWithBorder::Colour::Red);
			needNewMap = false;
			MapGenerator mapGen(time(nullptr));
			(*newMap) = mapGen.GenerateMap();
			newMap->CalculateColour();
			if (gameRunning)
				LogWindow.Log("Next Level finished Generating", SubWindowWithBorder::Colour::Red);
		}
	}
}
void FireWeapon(Direction dir, bool *firing)
{
	(*firing) = false;
	Map::Tile *tile;
	Vector2i bulletPos = player.position + dir;
	bulletPos.ClampVector();
	if ((tile = currentMap[bulletPos])->tile == Map::TileType::Wall)
		tile->tile = Map::Tile(Map::TileType::Air);
	else
	{
		for (auto it = enemies.begin(); it != enemies.end(); ++it)
		{
			if (it->position == bulletPos)
			{
				if (it->TakeDamage(player.GetDPS()))
				{
					enemies.erase(it);
					LogWindow.Log("Yus it did dun died!", SubWindowWithBorder::Colour::Green);
					break;
				}
				LogWindow.Log("Yea! I hit it!", SubWindowWithBorder::Colour::Green);
			}
		}
	}
	Direction backDir = dir;
	DirectionHelper::InvertDirection(backDir);
	if (player.CanMoveInDirection(backDir))
		player.position += backDir;
	DrawPlayer();
	LogWindow.Log("BANG BANG, I shoot my gun. BANG BANG, It hits the ground.", SubWindowWithBorder::Colour::Green);
	LogWindow.Log("Man, still not used to this recoil.", SubWindowWithBorder::Colour::Purple);
}
void LoadInNextMap()
{
	LogWindow.Log("Loading Next Map...", SubWindowWithBorder::Colour::Red);
	currentMap = nextMap;
	needNewMap = true;
	player.oldPosition = player.position;
	player.position = currentMap.GetSpawnPoint();
	EnemySpawn();
	GameWindow.Clear();
	DrawPlayer();
}
void DisplayPlayerStats()
{
	//This is used to make adding lines or changing order easier
	int yPos = 0;
	PlayerInfoPanel.Print(yPos, 0, "Player Info");
	++yPos;
	PlayerInfoPanel.Print(yPos, 0, "Stats: Displayed as CURRENT / MAX");
	++yPos;
	//For each data I need to display with differant colors on one line
	{
		std::vector<SubWindowWithBorder::ColouredString> displayData;
		displayData.push_back(SubWindowWithBorder::ColouredString(MakeStringLength(10, "Health") + ": ", SubWindowWithBorder::Colour::Red));
		displayData.push_back(MakeStringLength(6, std::to_string(player.GetHealthCurrent()), false));
		displayData.push_back(std::string("/"));
		displayData.push_back(MakeStringLength(6, std::to_string(player.GetHealthMax())));
		displayData.push_back(player.IsFullHealth() ?
						MakeStringLength(10, "FULL", false) :
						MakeStringLength(10, "Heal", false));
		PlayerInfoPanel.PrintDataToScreen(yPos, 0, displayData);
	}
	++yPos;
	{
		std::vector<SubWindowWithBorder::ColouredString> displayData;
		displayData.push_back(SubWindowWithBorder::ColouredString(MakeStringLength(10, "Damage") + ": ", SubWindowWithBorder::Colour::Red));
		displayData.push_back(MakeStringLength(6, std::to_string(player.GetDPS()), false));
		PlayerInfoPanel.PrintDataToScreen(yPos, 0, displayData);
	}
	++yPos;
	{
		std::vector<SubWindowWithBorder::ColouredString> displayData;
		displayData.push_back(SubWindowWithBorder::ColouredString(MakeStringLength(10, player.skills.DefenseSkill.GetName()) + ": ", SubWindowWithBorder::Colour::Cyan));
		displayData.push_back(MakeStringLength(6, std::to_string(player.skills.DefenseSkill.GetCurLevel()), false));
		displayData.push_back(std::string("/"));
		displayData.push_back(MakeStringLength(6, std::to_string(player.skills.DefenseSkill.GetMaxLevel())));
		displayData.push_back(player.skills.DefenseSkill.AtMaxLevel() ?
						MakeStringLength(10, "MAXED", false) :
						MakeStringLength(10, "LevelUp", false));
		PlayerInfoPanel.PrintDataToScreen(yPos, 0, displayData);
	}
	++yPos;
	{
		std::vector<SubWindowWithBorder::ColouredString> displayData;
		displayData.push_back(SubWindowWithBorder::ColouredString(MakeStringLength(10, player.skills.OffenseSkill.GetName()) + ": ", SubWindowWithBorder::Colour::Green));
		displayData.push_back(MakeStringLength(6, std::to_string(player.skills.OffenseSkill.GetCurLevel()), false));
		displayData.push_back(std::string("/"));
		displayData.push_back(MakeStringLength(6, std::to_string(player.skills.OffenseSkill.GetMaxLevel())));
		displayData.push_back(player.skills.OffenseSkill.AtMaxLevel() ?
						MakeStringLength(10, "MAXED", false) :
						MakeStringLength(10, "LevelUp", false));
		PlayerInfoPanel.PrintDataToScreen(yPos, 0, displayData);
	}
	++yPos;
	{
		std::vector<SubWindowWithBorder::ColouredString> displayData;
		displayData.push_back(SubWindowWithBorder::ColouredString(MakeStringLength(10, player.skills.ShoppingSkill.GetName()) + ": ", SubWindowWithBorder::Colour::Yellow));
		displayData.push_back(MakeStringLength(6, std::to_string(player.skills.ShoppingSkill.GetCurLevel()), false));
		displayData.push_back(std::string("/"));
		displayData.push_back(MakeStringLength(6, std::to_string(player.skills.ShoppingSkill.GetMaxLevel())));
		displayData.push_back(player.skills.ShoppingSkill.AtMaxLevel() ?
						MakeStringLength(10, "MAXED", false) :
						MakeStringLength(10, "LevelUp", false));
		PlayerInfoPanel.PrintDataToScreen(yPos, 0, displayData);
	}
	++yPos;
	{
		std::vector<SubWindowWithBorder::ColouredString> displayData;
		displayData.push_back(SubWindowWithBorder::ColouredString(MakeStringLength(10, player.inventory.Items[0].GetItemName()) + ": ", SubWindowWithBorder::Colour::Yellow));
		displayData.push_back(MakeStringLength(13, std::to_string(player.inventory.Items[0].GetTotalValue()), false));
		PlayerInfoPanel.PrintDataToScreen(yPos, 0, displayData);
	}
}
//Makes a string given length with spaces as filler
std::string MakeStringLength(int length, std::string data, bool after)
{
	//Normal add spaces after the word
	if (after)
	{
		for (int i = data.size(); i < length; i++)
			data += " ";
		return data;
	}
	//Other
	//Addspaces to new string, then add other data to the end
	std::string returnVal = "";
	for (int i = 0; i < length - data.length(); i++)
		returnVal += " ";
	returnVal += data;
	return returnVal;
}
//Generate the loot for the player from the "L" on the map
void PlayerLootGet()
{
	std::mt19937 mt = std::mt19937(time(nullptr));
	std::uniform_int_distribution<int> prng(1, 100);
	int num = prng(mt);
	if (player.inventory.HasSpaceForNewItem())
	{
		if (num > 90)
			player.inventory.AddNewItemStack(ItemSystem::StackedItem(&ItemSystem::StaticItems::LedgLute));
		else if (num > 50)
			player.inventory.AddNewItemStack(ItemSystem::StackedItem(&ItemSystem::StaticItems::RareLewt));
		else
			player.inventory.AddNewItemStack(ItemSystem::StackedItem(&ItemSystem::StaticItems::Lewt));
	}
	else
		LogWindow.Log("Hmmmmm. My inventory is full, I Guess I can't pick this up.\nI should sell somthing.");
	ReWriteInv = true;
}
//Generate the loot chest for the player from the "C" on the map
void PlayerLootChestGet()
{
	std::mt19937 mt = std::mt19937(time(nullptr));
	std::uniform_int_distribution<int> prngPercent(1, 100);
	std::uniform_int_distribution<int> prngSmall(0, 3);
	int itemDropCount = (prngSmall(mt) + 1) * 4;
	for (int i = 0; i < itemDropCount; i++)
	{
		int chance = prngPercent(mt);
		if (player.inventory.HasSpaceForNewItem())
		{
			if (chance > 90)
				player.inventory.AddNewItemStack(ItemSystem::StackedItem(&ItemSystem::StaticItems::UnrealisticGoals, prngSmall(mt) + 2));
			else if (chance > 80)
				player.inventory.AddNewItemStack(ItemSystem::StackedItem(&ItemSystem::StaticItems::GunOfMelee, prngSmall(mt) * 3 + 1));
			else if (chance > 60)
				player.inventory.AddNewItemStack(ItemSystem::StackedItem(&ItemSystem::StaticItems::SwordOfAmmo, prngSmall(mt) * 3 + 1));
			else if (chance > 40)
				player.inventory.AddNewItemStack(ItemSystem::StackedItem(&ItemSystem::StaticItems::LedgLute, prngSmall(mt) * 4 + 1));
			else if (chance > 20)
				player.inventory.AddNewItemStack(ItemSystem::StackedItem(&ItemSystem::StaticItems::RareLewt, prngSmall(mt) * 3 + 1));
			else
				player.inventory.AddNewItemStack(ItemSystem::StackedItem(&ItemSystem::StaticItems::Lewt, prngSmall(mt) * 5 + 1));
		}
		else
			LogWindow.Log("Hmmmmm. My inventory is full, I Guess I can't pick this up.\nI should sell somthing.");
	}
	ReWriteInv = true;
}
#include "MouseClicks.h"
