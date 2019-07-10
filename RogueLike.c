#include "stdlib.h"
#include "ncurses.h"

typedef struct Player
{
	int xPosition;
	int yPosition;
	int health;
} Player;


int ScreenSetUp();
int MapSetUp();
Player * PlayerSetUp();

int main(void) {
	int ch;
	Player * user;

	ScreenSetUp();
	MapSetUp();
	user = PlayerSetUp();

	while( (ch = getch()) != 'q' ) {

	}


	refresh();
	endwin();
	return 0;
}

int ScreenSetUp() {
	initscr();
	noecho();

	return 0;
}

int MapSetUp() {
	mvprintw(13, 13, "-----------------------");
	mvprintw(14, 13, "|---------------------|");
	mvprintw(15, 13, "|---------------------|");
	mvprintw(16, 13, "|---------------------|");
	mvprintw(17, 13, "|---------------------|");
	mvprintw(18, 13, "-----------------------");

	mvprintw(13, 50, "-----------------------");
	mvprintw(14, 50, "|---------------------|");
	mvprintw(15, 50, "|---------------------|");
	mvprintw(16, 50, "|---------------------|");
	mvprintw(17, 50, "|---------------------|");
	mvprintw(18, 50, "-----------------------");

	mvprintw(2, 20, "-----------------------");
	mvprintw(3, 20, "|---------------------|");
	mvprintw(4, 20, "|---------------------|");
	mvprintw(5, 20, "|---------------------|");
	mvprintw(6, 20, "|---------------------|");
	mvprintw(7, 20, "-----------------------");
	return 0;
}

Player * PlayerSetUp() {
	Player * newPlayer;
	newPlayer = malloc(sizeof(Player));

	newPlayer->xPosition 	= 20;
	newPlayer->yPosition 	= 15;
	newPlayer->health		= 20;
	mvprintw(newPlayer->yPosition, newPlayer->xPosition, "@");
	move(newPlayer->yPosition, newPlayer->xPosition);	// Curser ;)

	return newPlayer;
}
