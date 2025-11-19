#include "../Yahtc/Yahtc.h"
#include <ncurses.h>

int main(void) {
    
    // Setup the display

    // Setup the game
    
    // Game loop
    // Exit

	initscr();			/* Start curses mode 		  */
	printw("Hello World !!!");	/* Print Hello World		  */
	refresh();			/* Print it on to the real screen */
	getch();			/* Wait for user input */
	endwin();
}
