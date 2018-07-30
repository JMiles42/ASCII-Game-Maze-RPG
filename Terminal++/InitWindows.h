//This file is for slightly less clutter in entrypoint
void InitGameWindows()
{
	//Creates all of the windows with the cords variables
	GameWindow = SubWindowWithBorder(
		GameWindowHeight,
		LeftWindowWidth,
		0,
		0,
		false);
	LogWindow = SubWindowWithBorder(
		(WindowHeight - GameWindowHeight) + 1,
		LeftWindowWidth,
		GameWindowHeight - 1,
		0,
		true);
	InventoryWindow = SubWindowWithBorder(
		InventoryHeight,
		RightWindowWidth,
		0,
		LeftWindowWidth - 1,
		false);
	PlayerInfoPanel = SubWindowWithBorder(
		PlayerInfoHeight,
		RightWindowWidth,
		InventoryHeight - 1,
		LeftWindowWidth - 1,
		false);
	InfoPanel = SubWindowWithBorder(
		(WindowHeight - InventoryHeight - PlayerInfoHeight) + 2,
		RightWindowWidth,
		(InventoryHeight + PlayerInfoHeight) - 2,
		LeftWindowWidth - 1,
		false);
	//Crate a colour vaiable to allow easier typing of border draw methods
	SubWindowWithBorder::Colour BorderCol = SubWindowWithBorder::Colour::Cyan;
	//Simple Border and refresh
	GameWindow.Init(BorderCol);
	//Simple Border and refresh
	PlayerInfoPanel.Init(BorderCol);
	//Print borders that overlap with the currect character to mak them all join
	InventoryWindow.DrawBorders(
		SubWindowWithBorder::BorderTileType::PointingDownT,
		SubWindowWithBorder::BorderTileType::UpperRightCorner,
		SubWindowWithBorder::BorderTileType::PointingRightT,
		SubWindowWithBorder::BorderTileType::PointingLeftT,
		BorderCol);
	//Print borders that overlap with the currect character to mak them all join
	InfoPanel.DrawBorders(
		SubWindowWithBorder::BorderTileType::PointingRightT,
		SubWindowWithBorder::BorderTileType::PointingLeftT,
		SubWindowWithBorder::BorderTileType::PointingUpT,
		SubWindowWithBorder::BorderTileType::LowerRightCorner,
		BorderCol);
	//Print borders that overlap with the currect character to mak them all join
	LogWindow.DrawBorders(
		SubWindowWithBorder::BorderTileType::PointingRightT,
		SubWindowWithBorder::BorderTileType::PointingLeftT,
		SubWindowWithBorder::BorderTileType::LowerLeftCorner,
		SubWindowWithBorder::BorderTileType::PointingUpT,
		BorderCol);
	//Draw borders does not refresh like Init so a refresh is needed
	InventoryWindow.Refresh();
	//Draw borders does not refresh like Init so a refresh is needed
	InfoPanel.Refresh();
	//Make sure anything typed into the log appears at the bottom of the window
	for (int i = 0; i < 20; ++i)
		LogWindow.Log("\n");
	//Draw borders does not refresh like Init so a refresh is needed
	LogWindow.Refresh();
}
void InitConsoleWindow()
{
	//This changes the whole programs window
	//Most of this stuff I am not fully aware of what it is doing, I found a bunch of this code while googling
	//And on MSDN
	//Get std window handle
	HWND console = GetConsoleWindow();
	//Create and get the windows rect
	RECT r;
	GetWindowRect(console, &r);
	//Create a style
	DWORD newStyle = WS_OVERLAPPEDWINDOW;
	//Used for setting window size
	SMALL_RECT rect;
	//Used for setting console buffer
	COORD coord;
	coord.X = WindowWidth; // Defining X and
	coord.Y = WindowHeight; // Y size for buffer.
	rect.Top = 0;
	rect.Left = 0;
	rect.Bottom = coord.Y - 1; // height for window
	rect.Right = coord.X - 1; // width for window
	HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE); // get handle
	SetConsoleWindowInfo(console, TRUE, &rect); // set window size
	SetConsoleScreenBufferSize(console, coord); // set buffer size
	resize_term(coord.Y, coord.X);
	//Sets windows title
	SetConsoleTitle(TEXT("A VIDEO GAME!"));
	//Sets the style to not contain minimize, maximize, or be resizable
	SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_SIZEBOX & ~WS_MINIMIZEBOX & ~WS_MAXIMIZEBOX);
	//Enables mouse input
	SetConsoleMode(console, GetConsoleMode(console, nullptr) | ENABLE_MOUSE_INPUT);
	//NO idea
	//Don't want to remove cos could brake user interation
	keypad(stdscr, TRUE);
}
