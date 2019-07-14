#include "stdio.h"
#include "ncurses.h"

int main() {
	initscr();
	mvprintw(10,10, "Hi, Snake !");
	refresh();
	getch();
	endwin();
	return 0;
}

