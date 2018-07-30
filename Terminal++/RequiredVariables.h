//#ifndef ReqVars
//#define ReqVars
#pragma once
//#ifndef ReqVars
#include "SubWindowWithBorder.h"
#include "Maps/Map.h"
#include "People/Player.h"
//Changed from static to extern fixed AI Map issues
// Still keeping the AI desstroy walls.
extern SubWindowWithBorder GameWindow;
extern SubWindowWithBorder InventoryWindow;
extern SubWindowWithBorder InfoPanel;
extern SubWindowWithBorder PlayerInfoPanel;
extern SubWindowWithBorder LogWindow;
extern Map currentMap;
extern std::vector<std::vector<Map::Tile>> mapDisplay;
extern bool needNewMap;
extern bool playerDead;
extern Map nextMap;
extern People::Player player;
//
const static int WindowHeight = 40;
const static int WindowWidth = 100;
const static int LeftWindowWidth = 60;
const static int RightWindowWidth = (WindowWidth - LeftWindowWidth) + 1;
const static int InventoryHeight = 10;
const static int PlayerInfoHeight = 10;
const static int GameWindowHeight = 22;
const static int InventoryWindowLeftX = 60;
const static int InventoryWindowRightX = 98;
const static int InventoryWindowTopY = 1;
const static int InventoryWindowBottomY = 8;
const static int GameWindowLeftX = 1;
const static int GameWindowRightX = 58;
const static int GameWindowTopY = 1;
const static int GameWindowBottomY = 20;
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
//#endif
