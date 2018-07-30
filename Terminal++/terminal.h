// File [terminal.h]
#ifndef TERMINAL_PLUS_PLUS_H
#define TERMINAL_PLUS_PLUS_H

#include <ostream>

namespace curses
{
	// ENUMERATIONS:
	enum Color
	{
		// Default colors for DOS:
		cBlack, cBlue, cGreen, cCyan,
		cRed, cPurple, cBrown, cGrey,

		cDIM = cGrey,

		cDGrey, cLBlue, cLGreen, cLCyan,
		cLRed, cLPurple, cYellow, cWhite
	};

    // POINT2D and related types:
    template <typename T>
    class Point2dTemplate
    {
    public:
        T x, y;

        Point2dTemplate( T tX = 0, T tY = 0 ):x(tX),y(tY) {}

        Point2dTemplate<T>& operator +=( const Point2dTemplate<T>& rP2d ) 
            { x += rP2d.x; y += rP2d.y; return *this; }
        Point2dTemplate<T>& operator -=( const Point2dTemplate<T>& rP2d )
            { x -= rP2d.x; y -= rP2d.y; return *this; }
    };

    template <typename T>
    inline Point2dTemplate<T> operator +(
        const Point2dTemplate<T>& lhs,
        const Point2dTemplate<T>& rhs )
    {
        return Point2dTemplate<T>(lhs)+=rhs;
    }
    template <typename T>
    inline Point2dTemplate<T> operator -(
        const Point2dTemplate<T>& lhs,
        const Point2dTemplate<T>& rhs )
    {
        return Point2dTemplate<T>(lhs)-=rhs;
    }

    typedef Point2dTemplate<int> Point2d;

    //--- CURSES SCREEN MANIPULATION
    // POINT2D proxy class for screen IO: class Cursor
    class Cursor
    {
    public:
        Cursor( bool = true );
        ~Cursor( );

        class IntProxy
        {
        public:
            IntProxy( Cursor& );

            operator int( ) const;

            IntProxy& operator ++( );
            const int operator ++( int );
            IntProxy& operator --( );
            const int operator --( int );
            IntProxy& operator=( int );
            IntProxy& operator+=( const int );
            IntProxy& operator-=( const int );
        private:
            Cursor& mCursor;
        };

        IntProxy x, y;            

        operator Point2d( ) const;

	Cursor& operator=(const Cursor& );
	Cursor& operator=( const Point2d& );
        Cursor& operator+=( const Point2d& );
        Cursor& operator-=( const Point2d& );
    private:
        mutable Point2d mCurrentPoint;
                Point2d mStartPoint;
        const bool mSavePos;

        void update( const IntProxy&, int );
        int  reveal( const IntProxy& ) const;
        void getScreenPoint( Point2d& rPoint2d ) const;
        void setScreenPoint( );
        friend class IntProxy;
    };

    // SCREEN OUTPUT CLASS: class TerminalBuffer
    class TerminalBuffer
    : public  std::streambuf
    {
    public:
        TerminalBuffer( );
        virtual int overflow( int c = std::char_traits<char>::eof() );
    };

    // PRIMARY IO CLASS: class Terminal
    class Terminal
    : private TerminalBuffer,
      public std::ostream
    {
    public:
        Terminal( );
        ~Terminal( );
        
        Cursor	cursor;
		Color	foreground;
		Color	background;

        void cls( );		// Clear the screen
        void update( );		// Update curses - do this in each loop to refresh the screen
		bool kbhit( );		// Returns true if a key has been hit (or is hit within a really small time window)

		void setcolors( );	// Apply current foreground/background

    private:
        Terminal& streamOut( std::ostream& );

    friend Terminal& operator <<( Terminal&, std::ostream& );
        
	};
	
	// The global terminal object:
	extern Terminal terminal;

    Terminal& operator <<( Terminal&, std::ostream& );

	// Global helper:
	extern const char endl;

    // IO MANIPULATORS: class color
    class color
    {
    public:
        color( int c ) { mColor = c; }
    private:
		int mColor;
    friend std::ostream& operator <<( std::ostream&, const color& );
    };

   std::ostream& operator <<( std::ostream&, const color& );

   class bgcolor
   {
   public:
	   bgcolor(int c) { mColor = c; }
	   static void set(int);
   private:
	   int mColor;
	   friend std::ostream& operator <<(std::ostream&, const bgcolor&);
   };

   std::ostream& operator <<(std::ostream&, const color&);
   std::ostream& operator <<( std::ostream&, const Color& );


}

#endif // TERMINAL_PLUS_PLUS_H
// End of file.
