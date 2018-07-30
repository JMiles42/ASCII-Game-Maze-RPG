#pragma once
#include "UniversalHeader.h"
#include "terminal.h"
#include "RequiredVariables.h"
#include "People/Player.h"
#include "ItemSystem/StaticItems.h"
#include "Maps/Map.h"
#include "JMiles42/Maths/Vectors/Direction.h"
#include "MapGenerator.h"
#include "EnemySimple.h"
/*
//#define DebugClick
//#define DebugClickLog
//#define InventoryCheats
//#define WalkingDirMessages
*/
void InitConsoleWindow();
// Refresh the subwindows
void TerminalUpdate();
void InitGameWindows();
//Gets a y/n from user with mesages
bool MessageBoxYesNo(std::string text, std::string title);
void DisplayItem(int x, int y);
void PrintItemInfoToScreen(ItemSystem::StackedItem *item);
void PrintNullItemInfo();
int GetItemPosInVector(int y, int x);
void DrawPlayer();
void DisplayInventory();
void ScreenClicked(int x, int y);
void ThreadStart();
void StartScrn();
void EndScrn();
void StartRoom();
void EnemySpawn();
void EnemyCalc();
void EnemyDraw();
void DisplayMap(std::vector<std::vector<Map::Tile>> &map);
bool MovePlayer(Direction dir);
void GenerateNewMap(Map *newMap);
void FireWeapon(Direction dir, bool *firing);
void LoadInNextMap();
void DisplayPlayerStats();
void PlayerLootGet();
void PlayerLootChestGet();
//Render lock, not realy used the way it should be.
std::mutex renderLock;
//Are cheats enabled???
bool Cheating = false;
//
static ItemSystem::StackedItem *selectedItem = nullptr;
//
static int *selectedItemIndex = nullptr;
//
static bool ReWriteInv = true;
//
static std::vector<EnemySimple> enemies;
//
std::string MakeStringLength(int length, std::string data, bool after = true);
