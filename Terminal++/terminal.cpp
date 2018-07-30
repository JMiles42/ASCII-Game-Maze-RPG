#include <ostream>
#include <sstream>
#include <string>
#include <assert.h>
#include "terminal.h"
#include <curses.h>

namespace curses {

// The global terminal object:
Terminal terminal;

// Global helpers:
static const char endl = '\n';

//--- CURSOR
Cursor::Cursor( bool savePos )
: x(*this), y(*this), mSavePos(savePos)
{
    getScreenPoint( mStartPoint );
    getScreenPoint( mCurrentPoint );
}

Cursor::~Cursor( )
{
    mCurrentPoint = mStartPoint;
    setScreenPoint( );
}

Cursor::operator Point2d( ) const
{
    if (!mSavePos) getScreenPoint( mCurrentPoint );
    return mCurrentPoint;
}

Cursor & Cursor::operator=(const Cursor & rhs)
{
	mCurrentPoint = rhs;
	setScreenPoint();
	return *this;
}

Cursor& Cursor::operator=( const Point2d& rhs )
{
    mCurrentPoint = rhs;
    setScreenPoint( );
    return *this;
}

Cursor& Cursor::operator+=( const Point2d& rhs )
{
    if (!mSavePos) getScreenPoint( mCurrentPoint );
    mCurrentPoint += rhs;
    setScreenPoint( );

    return *this;
}

Cursor& Cursor::operator-=( const Point2d& rhs )
{
    if (!mSavePos) getScreenPoint( mCurrentPoint );
    mCurrentPoint -= rhs;
    setScreenPoint( );
    return *this;
}

void Cursor::getScreenPoint( Point2d& rPoint2d ) const
{
    int x, y;
    getyx(stdscr, y, x);
    rPoint2d = Point2d(x,y);
}

void Cursor::setScreenPoint( )
{
    move( mCurrentPoint.y, mCurrentPoint.x );
}

void Cursor::update( const IntProxy& rIntProxy, int i )
{
    if (!mSavePos) getScreenPoint( mCurrentPoint );

    if ( &rIntProxy == &x )
        mCurrentPoint.x = i;
    else
    {
        assert( &rIntProxy == &y );
        mCurrentPoint.y = i;
    }

    setScreenPoint( );
}

int  Cursor::reveal( const IntProxy& rIntProxy ) const
{
    if (!mSavePos) getScreenPoint( mCurrentPoint );

    if ( &rIntProxy == &x )
        return mCurrentPoint.x;

    assert( &rIntProxy == &y );

    return mCurrentPoint.y;
}

// Cursor::IntProxy

Cursor::IntProxy::IntProxy( Cursor& rCursor )
: mCursor(rCursor)
{
}

Cursor::IntProxy::operator int( ) const
{
    return mCursor.reveal(*this);
}

Cursor::IntProxy& 
 Cursor::IntProxy::operator ++( )
{
    int i = mCursor.reveal(*this);
    mCursor.update(*this,i+1);
    return *this;
}

const int Cursor::IntProxy::operator ++( int )
{
    int i = mCursor.reveal(*this);
    mCursor.update(*this,i+1);
    return i;
}

Cursor::IntProxy&
 Cursor::IntProxy::operator --( )
{
    int i = mCursor.reveal(*this);
    mCursor.update(*this,i-1);
    return *this;
}

const int Cursor::IntProxy::operator --( int )
{
    int i = mCursor.reveal(*this);
    mCursor.update(*this,i-1);
    return i;
}

Cursor::IntProxy&
 Cursor::IntProxy::operator=( int i )
{
    mCursor.update(*this,i);
    return *this;
}

Cursor::IntProxy&
 Cursor::IntProxy::operator+=( const int add )
{
    int i = mCursor.reveal(*this);
    mCursor.update(*this,i+add);
    return *this;
}

Cursor::IntProxy&
 Cursor::IntProxy::operator-=( const int add )
{
    int i = mCursor.reveal(*this);
    mCursor.update(*this,i-add);
    return *this;
}

//---TERMINAL BUFFER
TerminalBuffer::TerminalBuffer( )
{
    setbuf(0,0);
}

int TerminalBuffer::overflow( int c )
{
    // This could be a lot more efficient by
    // buffering, but for the moment this works
    // well:
    printw("%c",c);
    return 1;
}

//---TERMINAL
Terminal::Terminal( )
: TerminalBuffer( ),
  std::ostream( (TerminalBuffer*) this ),
  std::ios(0),
  cursor( false )
{
    // INIT SCREEN:
    initscr( );
    raw( );

    if (has_colors())
    {

        start_color();

        // Initialise all colour pairs for windows console:

#define INIT_PAIRS_FOR_BG(bgVal, bg)																				\
        init_pair( (short) cBlack   +1	+ bgVal * 16, (short)		(COLOR_BLACK | A_DIM),		(bg));		\
        init_pair( (short) cBlue    +1	+ bgVal * 16, (short)		(COLOR_BLUE | A_DIM),		(bg));		\
        init_pair( (short) cGreen   +1	+ bgVal * 16, (short)		(COLOR_GREEN | A_DIM),		(bg));		\
        init_pair( (short) cCyan    +1	+ bgVal * 16, (short)		(COLOR_CYAN | A_DIM),		(bg));		\
        init_pair( (short) cRed     +1	+ bgVal * 16, (short)		(COLOR_RED | A_DIM),		(bg));		\
        init_pair( (short) cPurple  +1	+ bgVal * 16, (short)		(COLOR_MAGENTA | A_DIM),	(bg));		\
		init_pair( (short) cBrown   +1	+ bgVal * 16, (short)		(COLOR_YELLOW | A_DIM),		(bg));		\
        init_pair( (short) cGrey    +1	+ bgVal * 16, (short)		(COLOR_WHITE | A_DIM),		(bg));		\
        init_pair( (short) cDGrey   +1	+ bgVal * 16, (short)		(COLOR_BLACK | A_BOLD),		(bg));		\
        init_pair( (short) cLBlue   +1	+ bgVal * 16, (short)		(COLOR_BLUE | A_BOLD),		(bg));		\
        init_pair( (short) cLGreen  +1	+ bgVal * 16, (short)		(COLOR_GREEN | A_BOLD),		(bg));		\
        init_pair( (short) cLCyan   +1	+ bgVal * 16, (short)		(COLOR_CYAN | A_BOLD),		(bg));		\
        init_pair( (short) cLRed    +1	+ bgVal * 16, (short)		(COLOR_RED | A_BOLD),		(bg));		\
        init_pair( (short) cLPurple +1	+ bgVal * 16, (short)		(COLOR_MAGENTA | A_BOLD),	(bg));		\
        init_pair( (short) cYellow  +1	+ bgVal * 16, (short)		(COLOR_YELLOW | A_BOLD),	(bg));		\
        init_pair( (short) cWhite   +1	+ bgVal * 16, (short)		(COLOR_WHITE | A_BOLD),		(bg));		\
		//

		INIT_PAIRS_FOR_BG( 0, COLOR_BLACK );
		INIT_PAIRS_FOR_BG( 1, COLOR_BLUE );
		INIT_PAIRS_FOR_BG( 2, COLOR_GREEN );
		INIT_PAIRS_FOR_BG( 3, COLOR_CYAN );
		INIT_PAIRS_FOR_BG( 4, COLOR_RED );
		INIT_PAIRS_FOR_BG( 5, COLOR_MAGENTA );
		INIT_PAIRS_FOR_BG( 6, COLOR_YELLOW );
		INIT_PAIRS_FOR_BG( 7, COLOR_WHITE );

    }

    clear( );
    refresh( );
    // INIT KEYBOARD:
    keypad(stdscr,TRUE);
    noecho( );
}

Terminal::~Terminal( )
{
    //SHUTDOWN SCREEN:
    endwin( );
    // sync ostream
    sync( );
}


void Terminal::cls( )
{
    erase( );
}

void Terminal::update( )
{
    refresh( );
}

bool Terminal::kbhit()
{
	// Set the timeout to a really small value then ask for a key hit:
	timeout(0);
	int ch = getch();
	timeout(-1);

	// Did we get a key? If so, return true but return the key to the buffer:
	if (ch != ERR) 
	{
		ungetch(ch);
		return true;
	}
	// No key was hit within the timeout -- return false:
	else 
	{
		return false;
	}
}

void Terminal::setcolors()
{
	// Apply current foreground/background
#define \
    TO_CURSES_STYLE(c) \
             COLOR_PAIR(c+1)|(c<=cDIM?A_DIM:A_BOLD)

	attrset( TO_CURSES_STYLE(foreground + 16 * background) );
}

//---COLOR

std::ostream& operator <<(std::ostream& rOutStream, const color& rColor)
{
	terminal.foreground = (curses::Color) rColor.mColor;
	terminal.setcolors();
	return rOutStream;
}

std::ostream& operator <<(std::ostream& rOutStream, const bgcolor& rColor)
{
	terminal.background = (curses::Color) rColor.mColor;
	terminal.setcolors();
	return rOutStream;
}

std::ostream& operator <<( std::ostream& rOutStream, const Color& eColor )
{
	terminal.foreground = eColor;
	terminal.setcolors();
	return rOutStream;
}


} // end namespace curses;

// End of file.
