#pragma once
#include "terminal.h"
#include <curses.h>
#include <Windows.h>
#include <vector>
class SubWindowWithBorder
{
public:
	//My user friendly enum for pdcurses border chars
	enum class BorderTileType
	{
		UpperLeftCorner = ACS_ULCORNER,
		LowerLeftCorner = ACS_LLCORNER,
		UpperRightCorner = ACS_URCORNER,
		LowerRightCorner = ACS_LRCORNER,
		PointingLeftT = ACS_RTEE,
		PointingRightT = ACS_LTEE,
		PointingUpT = ACS_BTEE,
		PointingDownT = ACS_TTEE,
		HLine = ACS_HLINE,
		VLine = ACS_VLINE,
		LeftArrow = ACS_LARROW,
		RightArrow = ACS_RARROW,
		DownArrow = ACS_DARROW,
		UpArrow = ACS_UARROW,
		Board = ACS_BOARD,
		Lantern = ACS_LANTERN,
		Block = ACS_BLOCK,
		S1 = ACS_S1,
		S9 = ACS_S9,
		Diamond = ACS_DIAMOND,
		Checkerboard = ACS_CKBOARD,
		Degree = ACS_DEGREE,
		PlusMinus = ACS_PLMINUS,
		Bullet = ACS_BULLET,
		Plus = ACS_PLUS,
	};
	enum class Colour
	{
		White = 0,
		Black = 1,
		Blue = 2,
		Green = 3,
		Cyan = 4,
		Red = 5,
		Purple = 6,
		Yellow = 7
	};
	//Simple data struct
	//For a coloured string
	struct ColouredString
	{
		std::string data;
		Colour colour;
		ColouredString(std::string _data, Colour _colour = Colour::White)
		{
			data = _data;
			colour = _colour;
		}
		operator std::string() const
		{
			return data;
		}
		operator Colour() const
		{
			return colour;
		}
	};
	//Border window only used for the outline/border
	WINDOW *border;
	//The content this is where all the displayed text is held.
	WINDOW *content;
	//Determins if the subwindow Content should be a text scrollable window
	bool isLog;
	//Empty Constructer
	SubWindowWithBorder();
	//Log only constructer
	SubWindowWithBorder(bool _log);
	//Position and dimention only constructer
	SubWindowWithBorder(int nlines, int ncols, int begy, int begx);
	//Full constructer
	SubWindowWithBorder(int nlines, int ncols, int begy, int begx, bool _log);
	//Display the border with current drawing colour
	void DrawBorders() const;
	void DrawBorders(int col) const;
	void DrawBorders(Colour col) const;
	void DrawBorders(BorderTileType topLeft, BorderTileType topRight, BorderTileType lowerLeft, BorderTileType lowerRight) const;
	void DrawBorders(BorderTileType topLeft, BorderTileType topRight, BorderTileType lowerLeft, BorderTileType lowerRight, int col) const;
	void DrawBorders(BorderTileType topLeft, BorderTileType topRight, BorderTileType lowerLeft, BorderTileType lowerRight, Colour col) const;
	void DrawBorders(BorderTileType topLeft, BorderTileType topRight, BorderTileType lowerLeft, BorderTileType lowerRight, BorderTileType hor, BorderTileType vert) const;
	void DrawBorders(BorderTileType topLeft, BorderTileType topRight, BorderTileType lowerLeft, BorderTileType lowerRight, BorderTileType hor, BorderTileType vert, int col) const;
	void DrawBorders(BorderTileType topLeft, BorderTileType topRight, BorderTileType lowerLeft, BorderTileType lowerRight, BorderTileType hor, BorderTileType vert, Colour col) const;
	void DrawBorders(unsigned long topLeft, unsigned long topRight, unsigned long lowerLeft, unsigned long lowerRight, int col) const;
	void DrawBorders(unsigned long topLeft, unsigned long topRight, unsigned long lowerLeft, unsigned long lowerRight, Colour col) const;
	void DrawBorders(unsigned long topLeft, unsigned long topRight, unsigned long lowerLeft, unsigned long lowerRight, unsigned long hor, unsigned long vert) const;
	void DrawBorders(unsigned long topLeft, unsigned long topRight, unsigned long lowerLeft, unsigned long lowerRight, unsigned long hor, unsigned long vert, int col) const;
	void DrawBorders(unsigned long topLeft, unsigned long topRight, unsigned long lowerLeft, unsigned long lowerRight, unsigned long hor, unsigned long vert, Colour col) const;
	//Prints data to the screen where the curser is
	void Log(char data, bool renderOnWrite = true) const;
	void Log(char data, int col, bool renderOnWrite = true) const;
	void Log(char data, Colour col, bool renderOnWrite = true) const;
	void Log(char *data, bool renderOnWrite = true) const;
	void Log(char *data, int col, bool renderOnWrite = true) const;
	void Log(char *data, Colour col, bool renderOnWrite = true) const;
	void Log(std::string &data, bool renderOnWrite = true) const;
	void Log(std::string &data, int col, bool renderOnWrite = true) const;
	void Log(std::string &data, Colour col, bool renderOnWrite = true) const;
	void Log(std::string *data, bool renderOnWrite = true) const;
	void Log(std::string *data, int col, bool renderOnWrite = true) const;
	void Log(std::string *data, Colour col, bool renderOnWrite = true) const;
	void Log(const std::string &data, bool renderOnWrite = true) const;
	void Log(const std::string &data, int col, bool renderOnWrite = true) const;
	void Log(const std::string &data, Colour col, bool renderOnWrite = true) const;
	//Prints the data to the screen at cords
	void Print(int x, int y, char *data, bool renderOnWrite = true) const;
	void Print(int x, int y, std::string &data, bool renderOnWrite = true) const;
	void Print(int x, int y, char data, bool renderOnWrite = true) const;
	void Print(int x, int y, char data, int col, bool renderOnWrite = true) const;
	void Print(int x, int y, char data, Colour col, bool renderOnWrite = true) const;
	void Print(int x, int y, char *data, int col, bool renderOnWrite = true) const;
	void Print(int x, int y, char *data, Colour col, bool renderOnWrite = true) const;
	void Print(int x, int y, std::string &data, int col, bool renderOnWrite = true) const;
	void Print(int x, int y, std::string &data, Colour col, bool renderOnWrite = true) const;
	//Refresh the subwindows contents ready for display
	void Refresh() const;
	//Clears the window
	void Clear() const;
	//Called to draw borders and do first refresh
	void Init() const;
	//Called to draw borders and do first refresh
	void Init(int col) const;
	//Called to draw borders and do first refresh
	void Init(Colour col) const;
	int GetHeight() const;
	int GetWidth() const;
	int GetArea() const;
	//Prints coloured data, from top down one entry per line
	void PrintDataToScreen(int y, int x, std::vector<ColouredString> data) const;
private:
	int width,height,area;
	void WriteBorders(unsigned long topLeft, unsigned long topRight, unsigned long lowerLeft, unsigned long lowerRight, unsigned long hor, unsigned long vert) const;
	void StartBorderColour(int col) const;
	void EndBorderColour(int col) const;
	void StartContentColour(int col) const;
	void EndContentColour(int col) const;
	void BorderRefresh() const;
};
