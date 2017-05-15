/*
CS 349 A1 Skeleton Code - Snake

- - - - - - - - - - - - - - - - - - - - - -

Commands to compile and run:

    g++ -o snake snake.cpp -L/usr/X11R6/lib -lX11 -lstdc++
    ./snake

Note: the -L option and -lstdc++ may not be needed on some machines.
*/

#include <iostream>
#include <list>
#include <cstdlib>
#include <sys/time.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <sstream>

/*
 * Header files for X functions
 */
#include <X11/Xlib.h>
#include <X11/Xutil.h>

using namespace std;
 
/*
 * Global game state variables
 */
const int Border = 1;
const int BufferSize = 10;
int FPS = 60;
int speed = 5;
int speed_saver = 5;
const int width = 800;
const int height = 600;


/*
 * up      0
 * down    1
 * left    2
 * right   3
 */


struct snakeLst {
    int x;
    int y;
    snakeLst * next;
    snakeLst * previous;
    
    snakeLst(int x, int y, snakeLst * next, snakeLst * previous) : x(x), y(y), next(next), previous(previous) {
        
    }
   
};

int score = 0;
int pause_indicator = 0;
int died = 0;
int dying = 0;
int start_screen = 1;
int just_turned = 0;
int quit_indicator = 0;
int snake_size = 1;

snakeLst * head = new snakeLst(100, 450, NULL, NULL);
snakeLst * tail = new snakeLst(100, 450, NULL, head);


/*
 * Information to draw on the window.
 */
struct XInfo {
	Display	 *display;
	int		 screen;
	Window	 window;
    Pixmap   pixmap;
	GC		 gc[3];
	int		width;		// size of window
	int		height;
};


/*
 * Function to put out a message on error exits.
 */
void error( string str ) {
  cerr << str << endl;
  exit(0);
}



/*
 * An abstract class representing displayable things.
 */
class Displayable {
	public:
		virtual void paint(XInfo &xinfo) = 0;
};

list<Displayable *> dList;           // list of Displayables

class StartScreen : public Displayable {
public:
    virtual void paint(XInfo &xinfo) {

        /****************   draw black  ***************/
        XColor xcolour_ss_black;
        char xcolor_ss_black[] = "#000000";
        Colormap cmap_ss_black = DefaultColormap(xinfo.display, DefaultScreen(xinfo.display));
        XParseColor(xinfo.display, cmap_ss_black, xcolor_ss_black, &xcolour_ss_black);
        XAllocColor(xinfo.display, cmap_ss_black, &xcolour_ss_black);
        XSetForeground(xinfo.display, xinfo.gc[0], xcolour_ss_black.pixel);
        
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 280, 180, 100, 20);//1
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 260, 200, 20, 40);//2
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 240, 240, 20, 60);//3
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 260, 300, 20, 20);//4
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 280, 240, 20, 40);//5
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 360, 240, 20, 40);//6
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 380, 200, 20, 20);//7
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 400, 220, 20, 40);//8
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 420, 260, 20, 40);//9
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 280, 320, 120, 20);//10
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 400, 300, 20, 80);//11
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 240, 340, 40, 20);//12
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 220, 360, 20, 20);//13
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 200, 380, 20, 60);//14
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 220, 440, 20, 20);//15
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 240, 460, 180, 20);//16
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 320, 340, 20, 20);//17
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 300, 360, 20, 20);//18
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 260, 380, 20, 20);//19
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 280, 400, 100, 20);//20
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 380, 380, 20, 20);//21
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 420, 340, 20, 20);//22
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 440, 360, 20, 20);//23
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 460, 380, 20, 20);//24
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 480, 400, 20, 60);//25
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 460, 460, 20, 20);//26
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 440, 400, 20, 60);//27
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 420, 440, 20, 20);//28
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 420, 200, 20, 20);//29
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 440, 180, 20, 20);//30
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 460, 200, 20, 20);//31
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 480, 180, 20, 20);//32
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 460, 160, 20, 20);//33
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 480, 80, 20, 60);//34
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 500, 140, 20, 20);//35
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 520, 160, 140, 20);//36
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 660, 140, 20, 20);//37
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 680, 80, 20, 60);//38
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 660, 60, 20, 20);//39
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 520, 40, 140, 20);//40
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 500, 60, 20, 20);//41
        
        XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[0], 560, 85, "I WANT", 6);
        XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[0], 515, 110, "PRESS w/a/s/d TO GUIDE ME", 25);
        XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[0], 540, 125, "PRESS p TO PAUSE", 16);
        XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[0], 535, 140, "PRESS r TO RESTART", 18);
        
        XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[0], 340, 555, "PRESS ANY KEY TO START", 22);
        
        XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[0], 673, 520, "WENXUE LI", 9);
        XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[0], 684, 540, "w254li", 6);
        XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[0], 677, 560, "20517629", 8);
        
        XFreeColormap(xinfo.display, cmap_ss_black);
        /****************   draw black  ***************/

        /****************   draw light green  ***************/
        XColor xcolour_ss_lgreen;
        char xcolor_ss_lgreen[] = "#32CD32";
        Colormap cmap_ss_lgreen = DefaultColormap(xinfo.display, DefaultScreen(xinfo.display));
        XParseColor(xinfo.display, cmap_ss_lgreen, xcolor_ss_lgreen, &xcolour_ss_lgreen);
        XAllocColor(xinfo.display, cmap_ss_lgreen, &xcolour_ss_lgreen);
        XSetForeground(xinfo.display, xinfo.gc[0], xcolour_ss_lgreen.pixel);
        
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 280, 200, 100, 40);//1
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 260, 240, 20, 40);//2
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 380, 220, 20, 60);//3
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 300, 240, 60, 60);//4
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 280, 280, 100, 20);//5
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 280, 340, 40, 20);//6
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 240, 360, 60, 20);//7
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 220, 380, 40, 20);//8
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 240, 400, 40, 40);//9
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 280, 420, 100, 20);//10
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 380, 400, 20, 40);//11
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 400, 380, 20, 60);//12
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 340, 340, 40, 20);//13
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 320, 360, 60, 20);//14
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 460, 400, 20, 60);//15
        
        XFreeColormap(xinfo.display, cmap_ss_lgreen);

        /****************   draw light green  ***************/
        
        /****************   draw dark green  ***************/
        XColor xcolour_ss_dgreen;
        char xcolor_ss_dgreen[] = "#228B22";
        Colormap cmap_ss_dgreen = DefaultColormap(xinfo.display, DefaultScreen(xinfo.display));
        XParseColor(xinfo.display, cmap_ss_dgreen, xcolor_ss_dgreen, &xcolour_ss_dgreen);
        XAllocColor(xinfo.display, cmap_ss_dgreen, &xcolour_ss_dgreen);
        XSetForeground(xinfo.display, xinfo.gc[0], xcolour_ss_dgreen.pixel);
        
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 400, 260, 20, 40);//1
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 280, 300, 120, 20);//2
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 380, 340, 20, 40);//3
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 280, 380, 100, 20);//4
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 220, 400, 20, 40);//5
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 240, 440, 180, 20);//6
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 420, 360, 20, 80);//7
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 440, 380, 20, 20);//8
        
        XFreeColormap(xinfo.display, cmap_ss_dgreen);

        /****************   draw dark green  ***************/
        
        /****************   draw pink  ***************/
        XColor xcolour_ss_pink;
        char xcolor_ss_pink[] = "#FF69B4";
        Colormap cmap_ss_pink = DefaultColormap(xinfo.display, DefaultScreen(xinfo.display));
        XParseColor(xinfo.display, cmap_ss_pink, xcolor_ss_pink, &xcolour_ss_pink);
        XAllocColor(xinfo.display, cmap_ss_pink, &xcolour_ss_pink);
        XSetForeground(xinfo.display, xinfo.gc[0], xcolour_ss_pink.pixel);
        
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 260, 280, 20, 20);//1
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 380, 280, 20, 20);//2
        
        XFreeColormap(xinfo.display, cmap_ss_pink);

        /****************   draw pink  ***************/
        
        
        /****************   draw apple   ****************/
        
        /*****   draw  brown  *****/
        XColor xbrown;
        char brown[] = "#FF0000";
        Colormap cmap_brown = DefaultColormap(xinfo.display, DefaultScreen(xinfo.display));
        XParseColor(xinfo.display, cmap_brown, brown, &xbrown);
        XAllocColor(xinfo.display, cmap_brown, &xbrown);
        XSetForeground(xinfo.display, xinfo.gc[0], xbrown.pixel);
        
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 608, 72, 2, 6);
        XFreeColormap(xinfo.display, cmap_brown);

        /*****   draw  brown  *****/
        
        /*****   draw  green  *****/
        XColor xgreen;
        char green[] = "#00FF00";
        Colormap cmap_green = DefaultColormap(xinfo.display, DefaultScreen(xinfo.display));
        XParseColor(xinfo.display, cmap_green, green, &xgreen);
        XAllocColor(xinfo.display, cmap_green, &xgreen);
        XSetForeground(xinfo.display, xinfo.gc[0], xgreen.pixel);
        
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 610, 74, 2, 2);
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 612, 72, 2, 2);
        XFreeColormap(xinfo.display, cmap_green);

        /*****   draw  green  *****/
        
        /*****   draw  white  *****/
        XColor xwhite;
        char white[] = "#FFFFFF";
        Colormap cmap_white = DefaultColormap(xinfo.display, DefaultScreen(xinfo.display));
        XParseColor(xinfo.display, cmap_white, white, &xwhite);
        XAllocColor(xinfo.display, cmap_white, &xwhite);
        XSetForeground(xinfo.display, xinfo.gc[0], xwhite.pixel);
        
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 604, 88, 4, 2);
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 604, 80, 2, 2);
        XFreeColormap(xinfo.display, cmap_white);

        /*****   draw  white  *****/
        
        /*****   draw  red  *****/
        XColor xred;
        char red[] = "#FF0000";
        Colormap cmap_red = DefaultColormap(xinfo.display, DefaultScreen(xinfo.display));
        XParseColor(xinfo.display, cmap_red, red, &xred);
        XAllocColor(xinfo.display, cmap_red, &xred);
        XSetForeground(xinfo.display, xinfo.gc[0], xred.pixel);
        
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 604, 76, 4, 2);//1
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 611, 76, 4, 2);//2
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 602, 78, 2, 8);//3
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 604, 82, 2, 6);//4
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 606, 80, 6, 10);//5
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 608, 78, 8, 2);//6
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 612, 80, 4, 6);//7
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 612, 86, 2, 2);//8
        
        XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[0], 680, 500, "MADE BY", 7);
        
        XFreeColormap(xinfo.display, cmap_red);

        /*****   draw  red  *****/
        
        /****************   draw apple   ****************/
        
    }
};

StartScreen startScreen;



/*
 * Function to repaint a display list
 */
void repaint( XInfo &xinfo) {
    list<Displayable *>::const_iterator begin = dList.begin();
    list<Displayable *>::const_iterator end = dList.end();

    
    // get height and width of window (might have changed since last repaint)
    
    XWindowAttributes windowInfo;
    XGetWindowAttributes(xinfo.display, xinfo.window, &windowInfo);
    unsigned int height = windowInfo.height;
    unsigned int width = windowInfo.width;
    
    // big black rectangle to clear background
    

    // draw display list
    
    XColor xcolour_bg;
    char xcolor_bg[] = "#F5F5F5";
    Colormap cmap_bg = DefaultColormap(xinfo.display, DefaultScreen(xinfo.display));
    XParseColor(xinfo.display, cmap_bg, xcolor_bg, &xcolour_bg);
    XAllocColor(xinfo.display, cmap_bg, &xcolour_bg);
    XSetForeground(xinfo.display, xinfo.gc[0], xcolour_bg.pixel);
    XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 0, 0, 800, 600);
    
    while( begin != end ) {
        Displayable *d = *begin;
        d->paint(xinfo);
        begin++;
    }
    XCopyArea(xinfo.display, xinfo.pixmap, xinfo.window, xinfo.gc[0], 0, 0, 800, 600, 0, 0);
    XFlush( xinfo.display );
}



class Obstacles : public Displayable {
public:
    virtual void paint(XInfo &xinfo) {

        /**************/

        XColor xcolour_o;
        char xcolor_o[] = "#000000";
        Colormap cmap_o = DefaultColormap(xinfo.display, DefaultScreen(xinfo.display));
        XParseColor(xinfo.display, cmap_o, xcolor_o, &xcolour_o);
        XAllocColor(xinfo.display, cmap_o, &xcolour_o);
        XSetForeground(xinfo.display, xinfo.gc[0], xcolour_o.pixel);
        
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 50, 50, 10, 450);
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 750, 50, 10, 450);
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 50, 500, 710, 10);
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 50, 50, 710, 10);

        XFreeColormap(xinfo.display, cmap_o);

    }
};

class Fruit : public Displayable {
public:
    virtual void paint(XInfo &xinfo) {

        /****************   draw apple   ****************/
        
        /*****   draw  brown  *****/
        XColor xbrown;
        char brown[] = "#FF0000";
        Colormap cmap_brown = DefaultColormap(xinfo.display, DefaultScreen(xinfo.display));
        XParseColor(xinfo.display, cmap_brown, brown, &xbrown);
        XAllocColor(xinfo.display, cmap_brown, &xbrown);
        XSetForeground(xinfo.display, xinfo.gc[0], xbrown.pixel);
        
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x+5, y+1, 1, 3);

        XFreeColormap(xinfo.display, cmap_brown);
        /*****   draw  brown  *****/
        
        /*****   draw  green  *****/
        XColor xgreen;
        char green[] = "#00FF00";
        Colormap cmap_green = DefaultColormap(xinfo.display, DefaultScreen(xinfo.display));
        XParseColor(xinfo.display, cmap_green, green, &xgreen);
        XAllocColor(xinfo.display, cmap_green, &xgreen);
        XSetForeground(xinfo.display, xinfo.gc[0], xgreen.pixel);
        
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x+7, y+1, 1, 1);
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x+6, y+2, 1, 1);
        
        XFreeColormap(xinfo.display, cmap_green);
 
        /*****   draw  green  *****/
        
        /*****   draw  white  *****/
        XColor xwhite;
        char white[] = "#FFFFFF";
        Colormap cmap_white = DefaultColormap(xinfo.display, DefaultScreen(xinfo.display));
        XParseColor(xinfo.display, cmap_white, white, &xwhite);
        XAllocColor(xinfo.display, cmap_white, &xwhite);
        XSetForeground(xinfo.display, xinfo.gc[0], xwhite.pixel);
        
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x+3, y+4, 2, 1);
        XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x+3, y+5, 1, 1);

        XFreeColormap(xinfo.display, cmap_white);
        /*****   draw  white  *****/
        
        if (golden == 1) {
            /*****   draw  yellow  *****/
            XColor xyellow;
            char yellow[] = "#FFA500";
            Colormap cmap_yellow = DefaultColormap(xinfo.display, DefaultScreen(xinfo.display));
            XParseColor(xinfo.display, cmap_yellow, yellow, &xyellow);
            XAllocColor(xinfo.display, cmap_yellow, &xyellow);
            XSetForeground(xinfo.display, xinfo.gc[0], xyellow.pixel);
            
            XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x+3, y+3, 2, 1);
            XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x+6, y+3, 2, 1);
            XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x+2, y+4, 1, 4);
            XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x+3, y+6, 1, 3);
            XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x+4, y+5, 1, 5);
            XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x+5, y+4, 1, 6);
            XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x+6, y+4, 1, 6);
            XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x+7, y+4, 1, 5);
            XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x+8, y+4, 1, 4);

            XFreeColormap(xinfo.display, cmap_yellow);
            /*****   draw  yellow  *****/
            
        } else if (slow_down == 1) {
            /*****   draw  purple  *****/
            
            XColor xpurple;
            char purple[] = "#A020F0";
            Colormap cmap_purple = DefaultColormap(xinfo.display, DefaultScreen(xinfo.display));
            XParseColor(xinfo.display, cmap_purple, purple, &xpurple);
            XAllocColor(xinfo.display, cmap_purple, &xpurple);
            XSetForeground(xinfo.display, xinfo.gc[0], xpurple.pixel);
            
            XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x+3, y+3, 2, 1);
            XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x+6, y+3, 2, 1);
            XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x+2, y+4, 1, 4);
            XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x+3, y+6, 1, 3);
            XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x+4, y+5, 1, 5);
            XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x+5, y+4, 1, 6);
            XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x+6, y+4, 1, 6);
            XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x+7, y+4, 1, 5);
            XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x+8, y+4, 1, 4);
            
            XFreeColormap(xinfo.display, cmap_purple);
            
            /*****   draw  purple  *****/
        } else {
            /*****   draw  red  *****/
            XColor xred;
            char red[] = "#FF0000";
            Colormap cmap_red = DefaultColormap(xinfo.display, DefaultScreen(xinfo.display));
            XParseColor(xinfo.display, cmap_red, red, &xred);
            XAllocColor(xinfo.display, cmap_red, &xred);
            XSetForeground(xinfo.display, xinfo.gc[0], xred.pixel);
            
            XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x+3, y+3, 2, 1);
            XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x+6, y+3, 2, 1);
            XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x+2, y+4, 1, 4);
            XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x+3, y+6, 1, 3);
            XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x+4, y+5, 1, 5);
            XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x+5, y+4, 1, 6);
            XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x+6, y+4, 1, 6);
            XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x+7, y+4, 1, 5);
            XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x+8, y+4, 1, 4);

            XFreeColormap(xinfo.display, cmap_red);
            /*****   draw  red  *****/
        }
        
        /****************   draw apple   ****************/
        
        
        /****************    print score   *************/
        XColor xcolour_s;
        char xcolor_s[] = "#000000";
        Colormap cmap_s = DefaultColormap(xinfo.display, DefaultScreen(xinfo.display));
        XParseColor(xinfo.display, cmap_s, xcolor_s, &xcolour_s);
        XAllocColor(xinfo.display, cmap_s, &xcolour_s);
        XSetForeground(xinfo.display, xinfo.gc[0], xcolour_s.pixel);
        
        XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[0], 20, 550, "SCORE", 5);

        stringstream ss;
        ss << score;
        ss.str();         // Gets you a C++ std::string
        ss.str().c_str();
        
        XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[0], 70, 550, ss.str().c_str(), ss.str().length());
        
        XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[0], 20, 570, "LIFE", 4);

        int life = 1 - died;
        stringstream ss2;
        ss2 << life;
        ss2.str();         // Gets you a C++ std::string
        ss2.str().c_str();
        
        XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[0], 70, 570, ss2.str().c_str(), ss2.str().length());

        XFreeColormap(xinfo.display, cmap_s);
    }
    
    Fruit() {
        // generate the x and y value for the fruit
        srand(time(NULL));
        int golden_indicator = rand() % 10;
        if (golden_indicator == 0) {
            golden = 1;
        } else {
            golden = 0;
            int slow_indicator = rand() % 15;
            if (slow_indicator == 0) {
                slow_down = 1;
            } else {
                slow_down = 0;
            }
        }
        x = (rand() % 64 + 6) * 10;
        y = (rand() % 40 + 6) * 10;
        if (x == 100 && y == 450) {
            x = 250;
            y = 300;
        }
    }
    
    int getX() {
        return x;
    }
    
    int getY() {
        return y;
    }
    
    int getGolden() {
        return golden;
    }
    
    int getSlow_down() {
        return slow_down;
    }
    
    void refresh(int preX, int preY) {
        srand(time(NULL));
        int golden_indicator = rand() % 10;
        if (golden_indicator == 0) {
            golden = 1;
        } else {
            golden = 0;
            int slow_indicator = rand() % 20;
            if (slow_indicator == 0) {
                slow_down = 1;
            } else {
                slow_down = 0;
            }
        }
        
        do {
            x = (rand() % 64 + 6) * 10;
        } while (x == preX);
        
        do {
            y = (rand() % 40 + 6) * 10;
        } while (y == preY);
        
        snakeLst * ptr = head;
        
        do {
            if (x == ptr->x && y == ptr->y) {
                refresh(x, y);
            } else {
                if (ptr->next != NULL) {
                    ptr = ptr->next;
                } else {
                    break;
                }
            }
        } while (ptr != NULL);
        
    }

    
private:
    int x;
    int y;
    int golden;
    int slow_down;
};


Fruit fruit;
Obstacles obstacles;


void deleteLastNode() {
    if (head == NULL) {
        return;
    }
    
    if (head->next == NULL) {
        delete head;
        head = NULL;
        return;
    }
    
    snakeLst * currNode = head;
    while (currNode->next != NULL && currNode->next->next != NULL) {
        currNode = currNode->next;
    }
    tail = currNode;
    delete currNode->next;
    currNode->next = NULL;
}


class Snake : public Displayable {
	public:
		virtual void paint(XInfo &xinfo) {

            /*******************/
         
            XColor xcolour_sn;
            char xcolor_sn[] = "#6B8E23";
            Colormap cmap_sn = DefaultColormap(xinfo.display, DefaultScreen(xinfo.display));
            XParseColor(xinfo.display, cmap_sn, xcolor_sn, &xcolour_sn);
            XAllocColor(xinfo.display, cmap_sn, &xcolour_sn);
            XSetForeground(xinfo.display, xinfo.gc[0], xcolour_sn.pixel);
            
            snakeLst * ptr = head;
            while (true) {
                XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], ptr->x, ptr->y, blockSize, blockSize);

                if (ptr->next != NULL) {
                    ptr = ptr->next;
                } else {
                    break;
                }
            }
            
            XFreeColormap(xinfo.display, cmap_sn);
            
            if (dying == 1) {
                XColor xcolour_ho;
                char xcolor_ho[] = "#000000";
                Colormap cmap_ho = DefaultColormap(xinfo.display, DefaultScreen(xinfo.display));
                XParseColor(xinfo.display, cmap_ho, xcolor_ho, &xcolour_ho);
                XAllocColor(xinfo.display, cmap_ho, &xcolour_ho);
                XSetForeground(xinfo.display, xinfo.gc[0], xcolour_ho.pixel);
                
                XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[0], 365, 200, "HIT OBSTACLE", 12);

                if (died == 1) {
                    XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[0], 350, 240, "PRESS r TO RESTART", 18);

                } else {
                    XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[0], 350, 240, "PRESS r TO RESTART", 18);
                    XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[0], 398, 260, "OR", 2);
                    XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[0], 330, 280, "PRESS w/a/s/d TO CONTINUE", 25);

                }
                XFreeColormap(xinfo.display, cmap_ho);
            }
            
            if (pause_indicator == 1) {
                XColor xcolour_ho;
                char xcolor_ho[] = "#000000";
                Colormap cmap_ho = DefaultColormap(xinfo.display, DefaultScreen(xinfo.display));
                XParseColor(xinfo.display, cmap_ho, xcolor_ho, &xcolour_ho);
                XAllocColor(xinfo.display, cmap_ho, &xcolour_ho);
                XSetForeground(xinfo.display, xinfo.gc[0], xcolour_ho.pixel);
                
                XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[0], 390, 200, "PAUSE", 5);
                XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[0], 350, 240, "PRESS r TO RESTART", 18);
                XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[0], 398, 260, "OR", 2);
                XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[0], 330, 280, "PRESS p/w/a/s/d TO CONTINUE", 27);

                XFreeColormap(xinfo.display, cmap_ho);
            }
		}

		
		void move(XInfo &xinfo) {
            
            int preX = head->x;
            int preY = head->y;
            
            if (direction == 0) {
                snakeLst * newHead = new snakeLst(preX, preY - 10, head, NULL);
                head = newHead;
                
                deleteLastNode();
                
            } else if (direction == 1) {
                snakeLst * newHead = new snakeLst(preX, preY + 10, head, NULL);
                head = newHead;
                
                deleteLastNode();
                
            } else if (direction == 2) {
                snakeLst * newHead = new snakeLst(preX - 10, preY, head, NULL);
                head = newHead;
                
                deleteLastNode();
                
            } else if (direction == 3) {
                snakeLst * newHead = new snakeLst(preX + 10, preY, head, NULL);
                head = newHead;
                
                deleteLastNode();
                
            }
            
            int newX = head->x;
            int newY = head->y;
            
            int fX = fruit.getX();
            int fY = fruit.getY();
        
            if (((fX - newX > -10 && fX - newX <= 0) || (fX - newX < 10 && fX - newX >= 0))
                && ((fY - newY > -10 && fY - newY <= 0) || (fY - newY < 10 && fY - newY >= 0))) {
                didEatFruit(head);
            }
            
            newX = head->x;
            newY = head->y;
            
            if (direction == 0 && newY - 10 < 60) {
                didHitObstacle(head, xinfo);
            } else if (direction == 1 && newY + 10 > 490) {
                didHitObstacle(head, xinfo);
            } else if (direction == 2 && newX - 10 < 60) {
                didHitObstacle(head, xinfo);
            } else if (direction == 3 && newX + 10 > 740) {
                didHitObstacle(head, xinfo);
            }
            
            
            snakeLst * hh = head;
            if (hh->next != NULL) {
                hh = hh->next;
            }
        
            while (hh->next != NULL) {
                hh = hh->next;
                if (direction == 0 && newY - 10 == hh->y && newX == hh->x) {
                    didHitObstacle(head, xinfo);
                    break;
                } else if (direction == 1 && newY + 10 == hh->y && newX == hh->x) {
                    didHitObstacle(head, xinfo);
                    break;
                } else if (direction == 2 && newX - 10 == hh->x && newY == hh->y) {
                    didHitObstacle(head, xinfo);
                    break;
                } else if (direction == 3 && newX + 10 == hh->x && newY == hh->y) {
                    didHitObstacle(head, xinfo);
                    break;
                }
            }
        
		}
		
		int getX() {
			return x;
		}
		
		int getY() {
			return y;
		}
    
        int getDirection() {
            return direction;
        }
    
        void setDirection(int d) {
            direction = d;
        }

 
        void didEatFruit(snakeLst * h) {
            int x = fruit.getX();
            int y = fruit.getY();
            
            snakeLst * newHead = new snakeLst(x, y, h, NULL);
            head = newHead;
            score += 100;
            snake_size += 1;
            
            if (fruit.getGolden() == 1) {
                died -= 1;
            }
            
            if (fruit.getSlow_down() == 1 && speed > 1) {
                speed -= 1;
            }
             
            fruit.refresh(x, y);
        }

        void didHitObstacle(snakeLst * h, XInfo &xinfo) {
            died += 1;
            dying = 1;
        }

        void turnLeft(snakeLst * h, snakeLst * t, XInfo &xinfo) {
            // d = 1 increase x
            // d = 0 decrease x
            // d = 3 decrease y
            // d = 2 increase y
            
            int preX = h->x;
            int preY = h->y;
            
            if (direction == 0) {
                snakeLst * newHead = new snakeLst(preX - 10, preY, head, NULL);
                head = newHead;
                direction = 2;
            } else if (direction == 1) {
                snakeLst * newHead = new snakeLst(preX + 10, preY, head, NULL);
                head = newHead;
                direction = 3;
            } else if (direction == 2) {
                snakeLst * newHead = new snakeLst(preX, preY + 10, head, NULL);
                head = newHead;
                direction = 1;
            } else if (direction == 3) {
                snakeLst * newHead = new snakeLst(preX, preY - 10, head, NULL);
                head = newHead;
                direction = 0;
            }
            
            deleteLastNode();
            
            int newX = head->x;
            int newY = head->y;
            
            int fX = fruit.getX();
            int fY = fruit.getY();
            
            if (((fX - newX > -10 && fX - newX <= 0) || (fX - newX < 10 && fX - newX >= 0))
                && ((fY - newY > -10 && fY - newY <= 0) || (fY - newY < 10 && fY - newY >= 0))) {
                didEatFruit(head);
            }
            
            newX = head->x;
            newY = head->y;
            
            if (direction == 0 && newY - 10 < 60) {
                didHitObstacle(head, xinfo);
            } else if (direction == 1 && newY + 10 > 490) {
                didHitObstacle(head, xinfo);
            } else if (direction == 2 && newX - 10 < 60) {
                didHitObstacle(head, xinfo);
            } else if (direction == 3 && newX + 10 > 740) {
                didHitObstacle(head, xinfo);
            }
            
            
            snakeLst * hh = head;
            if (hh->next != NULL) {
                hh = hh->next;
            }
            
            while (hh->next != NULL) {
                hh = hh->next;
                if (direction == 0 && newY - 10 == hh->y && newX == hh->x) {
                    didHitObstacle(head, xinfo);
                    break;
                } else if (direction == 1 && newY + 10 == hh->y && newX == hh->x) {
                    didHitObstacle(head, xinfo);
                    break;
                } else if (direction == 2 && newX - 10 == hh->x && newY == hh->y) {
                    didHitObstacle(head, xinfo);
                    break;
                } else if (direction == 3 && newX + 10 == hh->x && newY == hh->y) {
                    didHitObstacle(head, xinfo);
                    break;
                }
            }
            
        }

        void turnRight(snakeLst * h, snakeLst * t, XInfo &xinfo) {
            // d = 1 decrease x
            // d = 0 increase x
            // d = 3 increase y
            // d = 2 decrease y
            
            int preX = h->x;
            int preY = h->y;
            
            if (direction == 0) {
                snakeLst * newHead = new snakeLst(preX + 10, preY, head, NULL);
                head = newHead;
                direction = 3;
            } else if (direction == 1) {
                snakeLst * newHead = new snakeLst(preX - 10, preY, head, NULL);
                head = newHead;
                direction = 2;
            } else if (direction == 2) {
                snakeLst * newHead = new snakeLst(preX, preY - 10, head, NULL);
                head = newHead;
                direction = 0;
            } else if (direction == 3) {
                snakeLst * newHead = new snakeLst(preX, preY + 10, head, NULL);
                head = newHead;
                direction = 1;
            }
            
            deleteLastNode();
            
            int newX = head->x;
            int newY = head->y;
            
            int fX = fruit.getX();
            int fY = fruit.getY();
            
            if (((fX - newX > -10 && fX - newX <= 0) || (fX - newX < 10 && fX - newX >= 0))
                && ((fY - newY > -10 && fY - newY <= 0) || (fY - newY < 10 && fY - newY >= 0))) {
                didEatFruit(head);
            }
            
            newX = head->x;
            newY = head->y;
            
            if (direction == 0 && newY - 10 < 60) {
                didHitObstacle(head, xinfo);
            } else if (direction == 1 && newY + 10 > 490) {
                didHitObstacle(head, xinfo);
            } else if (direction == 2 && newX - 10 < 60) {
                didHitObstacle(head, xinfo);
            } else if (direction == 3 && newX + 10 > 740) {
                didHitObstacle(head, xinfo);
            }
            
            snakeLst * hh = head;
            if (hh->next != NULL) {
                hh = hh->next;
            }
            
            while (hh->next != NULL) {
                hh = hh->next;
                if (direction == 0 && newY - 10 == hh->y && newX == hh->x) {
                    didHitObstacle(head, xinfo);
                    break;
                } else if (direction == 1 && newY + 10 == hh->y && newX == hh->x) {
                    didHitObstacle(head, xinfo);
                    break;
                } else if (direction == 2 && newX - 10 == hh->x && newY == hh->y) {
                    didHitObstacle(head, xinfo);
                    break;
                } else if (direction == 3 && newX + 10 == hh->x && newY == hh->y) {
                    didHitObstacle(head, xinfo);
                    break;
                }
            }
        }
		
		Snake(int x, int y): x(x), y(y) {
			direction = 3;
            blockSize = 10;
		}
	
	private:
		int x;
		int y;
		int blockSize;
		int direction;
};



Snake snake(100, 450);

/*
 * Initialize X and create a window
 */
void initX(int argc, char *argv[], XInfo &xInfo) {
    if (argc == 3) {
        stringstream ss;
        ss << argv[1];
        ss >> FPS;
        stringstream ss2;
        ss2 << argv[2];
        ss2 >> speed;
        speed_saver = speed;
    }
    
	XSizeHints hints;
	unsigned long white, black;

   /*
	* Display opening uses the DISPLAY	environment variable.
	* It can go wrong if DISPLAY isn't set, or you don't have permission.
	*/	
	xInfo.display = XOpenDisplay( "" );
	if ( !xInfo.display )	{
		error( "Can't open display." );
	}
	
   /*
	* Find out some things about the display you're using.
	*/
	xInfo.screen = DefaultScreen( xInfo.display );

	white = XWhitePixel( xInfo.display, xInfo.screen );
	black = XBlackPixel( xInfo.display, xInfo.screen );
    
    XColor xcolour_bg;
    char xcolor_bg[] = "#F5F5F5";
    Colormap cmap_bg = DefaultColormap(xInfo.display, DefaultScreen(xInfo.display));
    XParseColor(xInfo.display, cmap_bg, xcolor_bg, &xcolour_bg);
    XAllocColor(xInfo.display, cmap_bg, &xcolour_bg);

	hints.x = 100;
	hints.y = 100;
	hints.width = 800;
	hints.height = 600;
	hints.flags = PPosition | PSize;

	xInfo.window = XCreateSimpleWindow( 
		xInfo.display,				// display where window appears
		DefaultRootWindow( xInfo.display ), // window's parent in window tree
		hints.x, hints.y,			// upper left corner location
		hints.width, hints.height,	// size of the window
		Border,						// width of window's border
		black,						// window border colour
		xcolour_bg.pixel );					// window background colour
		
	XSetStandardProperties(
		xInfo.display,		// display containing the window
		xInfo.window,		// window whose properties are set
		"animation",		// window's title
		"Animate",			// icon's title
		None,				// pixmap for the icon
		argv, argc,			// applications command line args
		&hints );			// size hints for the window
    
	/* 
	 * Create Graphics Contexts
	 */
	int i = 0;
	xInfo.gc[i] = XCreateGC(xInfo.display, xInfo.window, 0, 0);
    XSetForeground(xInfo.display, xInfo.gc[i], BlackPixel(xInfo.display, xInfo.screen));
	XSetBackground(xInfo.display, xInfo.gc[i], WhitePixel(xInfo.display, xInfo.screen));
	XSetFillStyle(xInfo.display, xInfo.gc[i], FillSolid);
	XSetLineAttributes(xInfo.display, xInfo.gc[i],
	                     1, LineSolid, CapButt, JoinRound);

	XSelectInput(xInfo.display, xInfo.window, 
		ButtonPressMask | KeyPressMask | 
		PointerMotionMask | 
		EnterWindowMask | LeaveWindowMask |
		StructureNotifyMask);  // for resize events
    
    XSetGraphicsExposures(xInfo.display, xInfo.gc[i],0);

    xInfo.pixmap = XCreatePixmap(xInfo.display, xInfo.window, 800, 600, XDefaultDepth(xInfo.display, xInfo.screen));
    
	/*
	 * Put the window on the screen.
	 */
	XMapRaised( xInfo.display, xInfo.window );
	XFlush(xInfo.display);
}


void handleKeyPress(XInfo &xinfo, XEvent &event) {
    KeySym key;
    char text[BufferSize];
    
    /*
     * Exit when 'q' is typed.
     * This is a simplified approach that does NOT use localization.
     */
    int i = XLookupString(
                          (XKeyEvent *)&event, 	// the keyboard event
                          text, 					// buffer when text will be written
                          BufferSize, 			// size of the text buffer
                          &key, 					// workstation-independent key symbol
                          NULL );					// pointer to a composeStatus structure (unused)
    if ( i == 1) {
        printf("Got key press -- %c\n", text[0]);
        if (start_screen == 1) {
            
            start_screen = 0;
            dList.pop_front();
            dList.push_front(&snake);
            dList.push_front(&fruit);
            dList.push_front(&obstacles);
            
        } else if (text[0] == 'q' || text[0] == 'Q') {
            while (snake_size > 0) {
                deleteLastNode();
                snake_size -= 1;
            }
            quit_indicator = 1;
            
        } else if ((text[0] == 'p' || text[0] == 'P') && pause_indicator == 0) {
            
            pause_indicator = 1;
            
        } else if ((text[0] == 'p' || text[0] == 'P') && pause_indicator == 1) {
            
            pause_indicator = 0;
            
        } else if ((text[0] == 'w' || text[0] == 'W') && died < 1) {
            
            if (pause_indicator == 1) {
                pause_indicator = 0;
            }
            
            if (dying == 1) {
                dying = 0;
            }
            
            int d = snake.getDirection();
            
            if (d == 2) {
                just_turned = 1;
                snake.turnRight(head, tail, xinfo);
            } else if (d == 3) {
                just_turned = 1;
                snake.turnLeft(head, tail, xinfo);
            }
        } else if ((text[0] == 'a' || text[0] == 'A') && died < 1) {
            
            if (pause_indicator == 1) {
                pause_indicator = 0;
            }
            
            if (dying == 1) {
                dying = 0;
            }
            
            int d = snake.getDirection();
            
            if (d == 0) {
                just_turned = 1;
                snake.turnLeft(head, tail, xinfo);
            } else if (d == 1) {
                just_turned = 1;
                snake.turnRight(head, tail, xinfo);
            }
            
        } else if ((text[0] == 's' || text[0] == 'S') && died < 1) {
            
            if (pause_indicator == 1) {
                pause_indicator = 0;
            }
            
            if (dying == 1) {
                dying = 0;
            }
            
            int d = snake.getDirection();
            
            if (d == 2) {
                just_turned = 1;
                snake.turnLeft(head, tail, xinfo);
            } else if (d == 3) {
                just_turned = 1;
                snake.turnRight(head, tail, xinfo);
            }
            
        } else if ((text[0] == 'd' || text[0] == 'D') && died < 1) {
            
            if (pause_indicator == 1) {
                pause_indicator = 0;
            }
            
            if (dying == 1) {
                dying = 0;
            }
            
            int d = snake.getDirection();
            
            if (d == 0) {
                just_turned = 1;
                snake.turnRight(head, tail, xinfo);
            } else if (d == 1) {
                just_turned = 1;
                snake.turnLeft(head, tail, xinfo);
            }
            
        } else if (text[0] == 'r' || text[0] == 'R') {
            if (pause_indicator == 1) {
                pause_indicator = 0;
            }
            
            if (dying == 1) {
                dying = 0;
            }
            
            died = 0;
            snake.setDirection(3);
            while (snake_size > 0) {
                deleteLastNode();
                snake_size -= 1;
            }
            head = new snakeLst(100, 450, NULL, NULL);
            tail = new snakeLst(100, 450, NULL, head);
            fruit.refresh(fruit.getX(), fruit.getY());
            score = 0;
            snake_size = 1;
            speed = speed_saver;
            repaint(xinfo);
            
        }
    }
}


void handleAnimation(XInfo &xinfo, int inside) {
    /*
     * ADD YOUR OWN LOGIC
     * This method handles animation for different objects on the screen and readies the next frame before the screen is re-painted.
     */ 
	snake.move(xinfo);
}

// get microseconds
unsigned long now() {
	timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000 + tv.tv_usec;
}

void eventLoop(XInfo &xinfo) {
    if (start_screen == 1) {
        dList.push_front(&startScreen);
    } else {
        // Add stuff to paint to the display list
        dList.push_front(&snake);
        dList.push_front(&fruit);
        dList.push_front(&obstacles);
    }
	
    XEvent event;
    unsigned long lastRepaint = 0;
    int inside = 0;

    while( true ) {
		
        if (XPending(xinfo.display) > 0) {
            XNextEvent( xinfo.display, &event );
            cout << "event.type=" << event.type << "\n";
            switch( event.type ) {
                case KeyPress:
                    handleKeyPress(xinfo, event);
                    if (quit_indicator == 1) {
                        return;
                    }
                    break;
                case EnterNotify:
                    inside = 1;
                    break;
                case LeaveNotify:
                    inside = 0;
                    break;
                default:
                    continue;
            }
        }
        
        usleep(1000000/FPS);
        if (pause_indicator == 0 && dying == 0 && died < 1 && start_screen == 0 && just_turned == 0) {
            int diff = (200000 /  speed) - (1000000 / FPS);
            if (diff > 0 && start_screen == 0) usleep(diff);
            handleAnimation(xinfo, inside);
        }
        just_turned = 0;
        repaint(xinfo);
    }
}



/*
 * Start executing here.
 *	 First initialize window.
 *	 Next loop responding to events.
 *	 Exit forcing window manager to clean up - cheesy, but easy.
 */

int main ( int argc, char *argv[] ) {
    XInfo xInfo;
    
    initX(argc, argv, xInfo);
    eventLoop(xInfo);
    XCloseDisplay(xInfo.display);
}
