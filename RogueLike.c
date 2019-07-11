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
int handleInput(int, Player *);
int playerMove(int, int, Player *);

int main(void) {
	int ch;
	Player * user;

	ScreenSetUp();
	MapSetUp();
	user = PlayerSetUp();

	/* Main Game Loop */
	while( (ch = getch()) != 'q' ) {
		handleInput(ch, user);
	}


	refresh();
	endwin();
	return 0;
}

int ScreenSetUp() {
	initscr();
	noecho();

	return 1;	// 1 == Succes & 0 == failure !!
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

int handleInput(int input, Player * user) {
	if (input == 'w' || input == 'W')	// Move Up
	{
		playerMove(user->yPosition - 1, user->xPosition, user);
	}
	if (input == 's' || input == 'S')	// Move Down
	{
		playerMove(user->yPosition + 1, user->xPosition, user);
	}
	if (input == 'a' || input == 'A')	// Move Left
	{
		playerMove(user->yPosition, user->xPosition - 1, user);
	}
	if (input == 'd' || input == 'D')	// Move Right
	{
		playerMove(user->yPosition, user->xPosition + 1, user);
	}
}

int playerMove(int y, int x,Player * user) {
	mvprintw(user->yPosition, user->xPosition, ".");	// Change Prev
	user->xPosition 	= x;
	user->yPosition 	= y;
	mvprintw(user->yPosition, user->xPosition, "@");	// Update knew
	move(user->yPosition, user->xPosition);
}
