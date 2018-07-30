#include "SubWindowWithBorder.h"
#include <vector>
SubWindowWithBorder::SubWindowWithBorder()
{
	//border = newwin(0, 0, 4, 4);
	//content = newwin(0, 0, 2, 2);
	width = 0;
	height = 0;
	area = height * width;
	isLog = false;
}
SubWindowWithBorder::SubWindowWithBorder(bool _log)
{
	//border = newwin(0, 0, 4, 4);
	//content = newwin(0, 0, 2, 2);
	content->_scroll = _log;
	width = 0;
	height = 0;
	area = height * width;
	isLog = _log;
}
SubWindowWithBorder::SubWindowWithBorder(int nlines, int ncols, int begy, int begx)
{
	border = newwin(nlines, ncols, begy, begx);
	content = newwin(nlines - 2, ncols - 2, begy + 1, begx + 1);
	width = ncols - 2;
	height = nlines - 2;
	area = height * width;
	isLog = false;
}
SubWindowWithBorder::SubWindowWithBorder(int nlines, int ncols, int begy, int begx, bool _log)
{
	border = newwin(nlines, ncols, begy, begx);
	content = newwin(nlines - 2, ncols - 2, begy + 1, begx + 1);
	content->_scroll = _log;
	isLog = _log;
	width = ncols - 2;
	height = nlines - 2;
	area = height * width;
}
void SubWindowWithBorder::DrawBorders() const
{
	WriteBorders(static_cast<unsigned long>(BorderTileType::UpperLeftCorner), static_cast<unsigned long>(BorderTileType::UpperRightCorner), static_cast<unsigned long>(BorderTileType::LowerLeftCorner), static_cast<unsigned long>(BorderTileType::LowerRightCorner), static_cast<unsigned long>(BorderTileType::HLine), static_cast<unsigned long>(BorderTileType::VLine));
	BorderRefresh();
}
void SubWindowWithBorder::DrawBorders(int col) const
{
	StartBorderColour(static_cast<int>(col));
	WriteBorders(static_cast<unsigned long>(BorderTileType::UpperLeftCorner), static_cast<unsigned long>(BorderTileType::UpperRightCorner), static_cast<unsigned long>(BorderTileType::LowerLeftCorner), static_cast<unsigned long>(BorderTileType::LowerRightCorner), static_cast<unsigned long>(BorderTileType::HLine), static_cast<unsigned long>(BorderTileType::VLine));
	EndBorderColour(static_cast<int>(col));
	BorderRefresh();
}
void SubWindowWithBorder::DrawBorders(Colour col) const
{
	StartBorderColour(static_cast<int>(col));
	WriteBorders(static_cast<unsigned long>(BorderTileType::UpperLeftCorner), static_cast<unsigned long>(BorderTileType::UpperRightCorner), static_cast<unsigned long>(BorderTileType::LowerLeftCorner), static_cast<unsigned long>(BorderTileType::LowerRightCorner), static_cast<unsigned long>(BorderTileType::HLine), static_cast<unsigned long>(BorderTileType::VLine));
	EndBorderColour(static_cast<int>(col));
	BorderRefresh();
}
void SubWindowWithBorder::DrawBorders(BorderTileType topLeft, BorderTileType topRight, BorderTileType lowerLeft, BorderTileType lowerRight) const
{
	WriteBorders(static_cast<unsigned long>(topLeft), static_cast<unsigned long>(topRight), static_cast<unsigned long>(lowerLeft), static_cast<unsigned long>(lowerRight), static_cast<unsigned long>(BorderTileType::HLine), static_cast<unsigned long>(BorderTileType::VLine));
	BorderRefresh();
}
void SubWindowWithBorder::DrawBorders(BorderTileType topLeft, BorderTileType topRight, BorderTileType lowerLeft, BorderTileType lowerRight, int col) const
{
	StartBorderColour(static_cast<int>(col));
	WriteBorders(static_cast<unsigned long>(topLeft), static_cast<unsigned long>(topRight), static_cast<unsigned long>(lowerLeft), static_cast<unsigned long>(lowerRight), static_cast<unsigned long>(BorderTileType::HLine), static_cast<unsigned long>(BorderTileType::VLine));
	EndBorderColour(static_cast<int>(col));
	BorderRefresh();
}
void SubWindowWithBorder::DrawBorders(BorderTileType topLeft, BorderTileType topRight, BorderTileType lowerLeft, BorderTileType lowerRight, Colour col) const
{
	StartBorderColour(static_cast<int>(col));
	WriteBorders(static_cast<unsigned long>(topLeft), static_cast<unsigned long>(topRight), static_cast<unsigned long>(lowerLeft), static_cast<unsigned long>(lowerRight), static_cast<unsigned long>(BorderTileType::HLine), static_cast<unsigned long>(BorderTileType::VLine));
	EndBorderColour(static_cast<int>(col));
	BorderRefresh();
}
void SubWindowWithBorder::DrawBorders(BorderTileType topLeft, BorderTileType topRight, BorderTileType lowerLeft, BorderTileType lowerRight, BorderTileType hor, BorderTileType vert) const
{
	WriteBorders(static_cast<unsigned long>(topLeft), static_cast<unsigned long>(topRight), static_cast<unsigned long>(lowerLeft), static_cast<unsigned long>(lowerRight), static_cast<unsigned long>(hor), static_cast<unsigned long>(vert));
	BorderRefresh();
}
void SubWindowWithBorder::DrawBorders(BorderTileType topLeft, BorderTileType topRight, BorderTileType lowerLeft, BorderTileType lowerRight, BorderTileType hor, BorderTileType vert, int col) const
{
	StartBorderColour(static_cast<int>(col));
	WriteBorders(static_cast<unsigned long>(topLeft), static_cast<unsigned long>(topRight), static_cast<unsigned long>(lowerLeft), static_cast<unsigned long>(lowerRight), static_cast<unsigned long>(hor), static_cast<unsigned long>(vert));
	EndBorderColour(static_cast<int>(col));
	BorderRefresh();
}
void SubWindowWithBorder::DrawBorders(BorderTileType topLeft, BorderTileType topRight, BorderTileType lowerLeft, BorderTileType lowerRight, BorderTileType hor, BorderTileType vert, Colour col) const
{
	StartBorderColour(static_cast<int>(col));
	WriteBorders(static_cast<unsigned long>(topLeft), static_cast<unsigned long>(topRight), static_cast<unsigned long>(lowerLeft), static_cast<unsigned long>(lowerRight), static_cast<unsigned long>(hor), static_cast<unsigned long>(vert));
	EndBorderColour(static_cast<int>(col));
	BorderRefresh();
}
void SubWindowWithBorder::DrawBorders(unsigned long topLeft, unsigned long topRight, unsigned long lowerLeft, unsigned long lowerRight, int col) const
{
	StartBorderColour(static_cast<int>(col));
	WriteBorders(topLeft, topRight, lowerLeft, lowerRight, static_cast<unsigned long>(BorderTileType::HLine), static_cast<unsigned long>(BorderTileType::VLine));
	EndBorderColour(static_cast<int>(col));
	BorderRefresh();
}
void SubWindowWithBorder::DrawBorders(unsigned long topLeft, unsigned long topRight, unsigned long lowerLeft, unsigned long lowerRight, Colour col) const
{
	StartBorderColour(static_cast<int>(col));
	WriteBorders(topLeft, topRight, lowerLeft, lowerRight, static_cast<unsigned long>(BorderTileType::HLine), static_cast<unsigned long>(BorderTileType::VLine));
	EndBorderColour(static_cast<int>(col));
	BorderRefresh();
}
void SubWindowWithBorder::DrawBorders(unsigned long topLeft, unsigned long topRight, unsigned long lowerLeft, unsigned long lowerRight, unsigned long hor, unsigned long vert) const
{
	WriteBorders(topLeft, topRight, lowerLeft, lowerRight, hor, vert);
	BorderRefresh();
}
void SubWindowWithBorder::DrawBorders(unsigned long topLeft, unsigned long topRight, unsigned long lowerLeft, unsigned long lowerRight, unsigned long hor, unsigned long vert, int col) const
{
	StartBorderColour(static_cast<int>(col));
	WriteBorders(topLeft, topRight, lowerLeft, lowerRight, hor, vert);
	EndBorderColour(static_cast<int>(col));
	BorderRefresh();
}
void SubWindowWithBorder::DrawBorders(unsigned long topLeft, unsigned long topRight, unsigned long lowerLeft, unsigned long lowerRight, unsigned long hor, unsigned long vert, Colour col) const
{
	StartBorderColour(static_cast<int>(col));
	WriteBorders(topLeft, topRight, lowerLeft, lowerRight, hor, vert);
	EndBorderColour(static_cast<int>(col));
	BorderRefresh();
}
void SubWindowWithBorder::Log(char data, Colour col, bool renderOnWrite) const
{
	if (isLog)
		wprintw(content, "\n");
	StartContentColour(static_cast<int>(col));
	wprintw(content, "%s", data);
	EndContentColour(static_cast<int>(col));
	if (renderOnWrite)
		Refresh();
}
void SubWindowWithBorder::Log(char *data, bool renderOnWrite) const
{
	if (isLog)
		wprintw(content, "\n");
	wprintw(content, "%s", data);
	if (renderOnWrite)
		Refresh();
}
void SubWindowWithBorder::Log(char *data, int col, bool renderOnWrite) const
{
	if (isLog)
		wprintw(content, "\n");
	StartContentColour(static_cast<int>(col));
	wprintw(content, "%s", data);
	EndContentColour(static_cast<int>(col));
	if (renderOnWrite)
		Refresh();
}
void SubWindowWithBorder::Log(char *data, Colour col, bool renderOnWrite) const
{
	if (isLog)
		wprintw(content, "\n");
	StartContentColour(static_cast<int>(col));
	wprintw(content, "%s", data);
	EndContentColour(static_cast<int>(col));
	if (renderOnWrite)
		Refresh();
}
void SubWindowWithBorder::Log(std::string &data, bool renderOnWrite) const
{
	if (isLog)
		wprintw(content, "\n");
	wprintw(content, "%s", data);
	if (renderOnWrite)
		Refresh();
}
void SubWindowWithBorder::Log(std::string &data, int col, bool renderOnWrite) const
{
	if (isLog)
		wprintw(content, "\n");
	StartContentColour(static_cast<int>(col));
	wprintw(content, "%s", data.data());
	EndContentColour(static_cast<int>(col));
	if (renderOnWrite)
		Refresh();
}
void SubWindowWithBorder::Log(std::string &data, Colour col, bool renderOnWrite) const
{
	if (isLog)
		wprintw(content, "\n");
	StartContentColour(static_cast<int>(col));
	wprintw(content, "%s", data.data());
	EndContentColour(static_cast<int>(col));
	if (renderOnWrite)
		Refresh();
}
void SubWindowWithBorder::Log(std::string *data, bool renderOnWrite) const
{
	if (isLog)
		wprintw(content, "\n");
	wprintw(content, "%s", data->data());
	if (renderOnWrite)
		Refresh();
}
void SubWindowWithBorder::Log(std::string *data, int col, bool renderOnWrite) const
{
	if (isLog)
		wprintw(content, "\n");
	StartContentColour(static_cast<int>(col));
	wprintw(content, "%s", data->data());
	EndContentColour(static_cast<int>(col));
	if (renderOnWrite)
		Refresh();
}
void SubWindowWithBorder::Log(std::string *data, Colour col, bool renderOnWrite) const
{
	StartContentColour(static_cast<int>(col));
	wprintw(content, "%s", data->data());
	EndContentColour(static_cast<int>(col));
	if (renderOnWrite)
		Refresh();
}
void SubWindowWithBorder::Log(const std::string &data, bool renderOnWrite) const
{
	if (isLog)
		wprintw(content, "\n");
	wprintw(content, "%s", data.data());
	if (renderOnWrite)
		Refresh();
}
void SubWindowWithBorder::Log(const std::string &data, int col, bool renderOnWrite) const
{
	if (isLog)
		wprintw(content, "\n");
	StartContentColour(static_cast<int>(col));
	wprintw(content, "%s", data.data());
	EndContentColour(static_cast<int>(col));
	if (renderOnWrite)
		Refresh();
}
void SubWindowWithBorder::Log(const std::string &data, Colour col, bool renderOnWrite) const
{
	if (isLog)
		wprintw(content, "\n");
	StartContentColour(static_cast<int>(col));
	wprintw(content, "%s", data.data());
	EndContentColour(static_cast<int>(col));
	if (renderOnWrite)
		Refresh();
}
void SubWindowWithBorder::Log(char data, bool renderOnWrite) const
{
	if (isLog)
		wprintw(content, "\n");
	wprintw(content, "%c", data);
	if (renderOnWrite)
		Refresh();
}
void SubWindowWithBorder::Log(char data, int col, bool renderOnWrite) const
{
	if (isLog)
		wprintw(content, "\n");
	StartContentColour(static_cast<int>(col));
	wprintw(content, "%c", data);
	EndContentColour(static_cast<int>(col));
	if (renderOnWrite)
		Refresh();
}
void SubWindowWithBorder::Print(int x, int y, char data, bool renderOnWrite) const
{
	if (isLog)
		wprintw(content, "\n");
	mvwprintw(content, x, y, "%c", data);
	if (renderOnWrite)
		Refresh();
}
void SubWindowWithBorder::Print(int x, int y, char data, int col, bool renderOnWrite) const
{
	StartContentColour(static_cast<int>(col));
	mvwprintw(content, x, y, "%c", data);
	EndContentColour(static_cast<int>(col));
	if (renderOnWrite)
		Refresh();
}
void SubWindowWithBorder::Print(int x, int y, char data, Colour col, bool renderOnWrite) const
{
	StartContentColour(static_cast<int>(col));
	mvwprintw(content, x, y, "%c", data);
	EndContentColour(static_cast<int>(col));
	if (renderOnWrite)
		Refresh();
}
void SubWindowWithBorder::Print(int x, int y, char *data, bool renderOnWrite) const
{
	mvwprintw(content, x, y, "%s", data);
	if (renderOnWrite)
		Refresh();
}
void SubWindowWithBorder::Print(int x, int y, char *data, int col, bool renderOnWrite) const
{
	StartContentColour(static_cast<int>(col));
	mvwprintw(content, x, y, "%s", data);
	EndContentColour(static_cast<int>(col));
	if (renderOnWrite)
		Refresh();
}
void SubWindowWithBorder::Print(int x, int y, char *data, Colour col, bool renderOnWrite) const
{
	StartContentColour(static_cast<int>(col));
	mvwprintw(content, x, y, "%s", data);
	EndContentColour(static_cast<int>(col));
	if (renderOnWrite)
		Refresh();
}
void SubWindowWithBorder::Print(int x, int y, std::string &data, bool renderOnWrite) const
{
	mvwprintw(content, x, y, "%s", data.data());
	if (renderOnWrite)
		Refresh();
}
void SubWindowWithBorder::Print(int x, int y, std::string &data, int col, bool renderOnWrite) const
{
	StartContentColour(static_cast<int>(col));
	mvwprintw(content, x, y, "%s", data.data());
	EndContentColour(static_cast<int>(col));
	if (renderOnWrite)
		Refresh();
}
void SubWindowWithBorder::Print(int x, int y, std::string &data, Colour col, bool renderOnWrite) const
{
	StartContentColour(static_cast<int>(col));
	mvwprintw(content, x, y, "%s", data.data());
	EndContentColour(static_cast<int>(col));
	if (renderOnWrite)
		Refresh();
}
void SubWindowWithBorder::Refresh() const
{
	wrefresh(content);
}
void SubWindowWithBorder::Clear() const
{
	wclear(content);
}
void SubWindowWithBorder::Init() const
{
	DrawBorders();
	BorderRefresh();
	Refresh();
}
void SubWindowWithBorder::Init(int col) const
{
	StartBorderColour(static_cast<int>(col));
	WriteBorders(static_cast<unsigned long>(BorderTileType::UpperLeftCorner), static_cast<unsigned long>(BorderTileType::UpperRightCorner), static_cast<unsigned long>(BorderTileType::LowerLeftCorner), static_cast<unsigned long>(BorderTileType::LowerRightCorner), static_cast<unsigned long>(BorderTileType::HLine), static_cast<unsigned long>(BorderTileType::VLine));
	EndBorderColour(static_cast<int>(col));
	BorderRefresh();
	Refresh();
}
void SubWindowWithBorder::Init(Colour col) const
{
	StartBorderColour(static_cast<int>(col));
	WriteBorders(static_cast<unsigned long>(BorderTileType::UpperLeftCorner), static_cast<unsigned long>(BorderTileType::UpperRightCorner), static_cast<unsigned long>(BorderTileType::LowerLeftCorner), static_cast<unsigned long>(BorderTileType::LowerRightCorner), static_cast<unsigned long>(BorderTileType::HLine), static_cast<unsigned long>(BorderTileType::VLine));
	EndBorderColour(static_cast<int>(col));
	BorderRefresh();
	Refresh();
}
int SubWindowWithBorder::GetHeight() const
{
	return height;
}
int SubWindowWithBorder::GetWidth() const
{
	return width;
}
int SubWindowWithBorder::GetArea() const
{
	return area;
}
void SubWindowWithBorder::WriteBorders(unsigned long topLeft, unsigned long topRight, unsigned long lowerLeft, unsigned long lowerRight, unsigned long hor, unsigned long vert) const
{
	wborder(border,
		vert,
		vert,
		hor,
		hor,
		topLeft,
		topRight,
		lowerLeft,
		lowerRight);
}
void SubWindowWithBorder::StartBorderColour(int col) const
{
	wattron(border, COLOR_PAIR(col));
}
void SubWindowWithBorder::EndBorderColour(int col) const
{
	wattroff(border, COLOR_PAIR(col));
}
void SubWindowWithBorder::StartContentColour(int col) const
{
	wattron(content, COLOR_PAIR(col));
}
void SubWindowWithBorder::EndContentColour(int col) const
{
	wattroff(content, COLOR_PAIR(col));
}
void SubWindowWithBorder::BorderRefresh() const
{
	wrefresh(border);
}
void SubWindowWithBorder::PrintDataToScreen(int y, int x, std::vector<ColouredString> data) const
{
	for (auto &dat : data)
	{
		Print(y, x, dat.data, dat.colour);
		x += dat.data.size();
	}
}
