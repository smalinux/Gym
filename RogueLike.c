#include "stdlib.h"
#include "ncurses.h"

typedef struct Room
{
	int xPosition;
	int yPosition;
	int height;
	int width;
	//
	// Monster ** monsters;		// pointer to array of structs ! i think !!
	// Item ** items;
} Room;

typedef struct Player
{
	int xPosition;
	int yPosition;
	int health;
	// Room * room;
} Player;


int ScreenSetUp();
Room ** MapSetUp();		// returns array of struct ; )
Player * PlayerSetUp();
int handleInput(int, Player *);
int CheckPosition(int, int, Player *);
int playerMove(int, int, Player *);
/* Room functions */
Room * createRoom(int y, int x, int height, int width );
int drawRoom(Room * room);


// -----------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------

int ScreenSetUp() {
	initscr();
	noecho();

	return 1;	// 1 == Succes & 0 == failure !!
}

Room ** MapSetUp() {		// Array of structs
	Room ** rooms;			// Create array of room! very simple xD
	rooms	= malloc(sizeof(Room) * 6);
	// mvprintw(13, 13, "-----------------------");
	// mvprintw(14, 13, "|.....................|");
	// mvprintw(15, 13, "|.....................|");
	// mvprintw(16, 13, "|.....................|");
	// mvprintw(17, 13, "|.....................|");
	// mvprintw(18, 13, "-----------------------");

	rooms[0] 	= createRoom(13, 13, 6, 21);
	drawRoom(rooms[0]);

	rooms[1] 	= createRoom(13, 50, 6, 21);
	drawRoom(rooms[1]);

	rooms[2] 	= createRoom(2, 13, 6, 21);
	drawRoom(rooms[2]);

	// mvprintw(13, 50, "-----------------------");
	// mvprintw(14, 50, "|.....................|");
	// mvprintw(15, 50, "|.....................|");
	// mvprintw(16, 50, "|.....................|");
	// mvprintw(17, 50, "|.....................|");
	// mvprintw(18, 50, "-----------------------");

	// mvprintw(2, 20, "-----------------------");
	// mvprintw(3, 20, "|.....................|");
	// mvprintw(4, 20, "|.....................|");
	// mvprintw(5, 20, "|.....................|");
	// mvprintw(6, 20, "|.....................|");
	// mvprintw(7, 20, "-----------------------");
	return rooms;
}

Room * createRoom(int y, int x, int height, int width ) {
	Room * newRoom;
	newRoom		= malloc(sizeof(Room));

	newRoom->yPosition		= y;
	newRoom->xPosition		= x;
	newRoom->height			= height;
	newRoom->width			= width;
	return newRoom;
}

Player * PlayerSetUp() {
	Player * newPlayer;
	newPlayer = malloc(sizeof(Player));

	newPlayer->xPosition 	= 20;
	newPlayer->yPosition 	= 15;
	newPlayer->health		= 20;
	playerMove(15, 20, newPlayer);

	return newPlayer;
}

int handleInput(int input, Player * user) {
	int newX;
	int newY;
	if (input == 'w' || input == 'W')	// Move Up
	{
		newY 	= user->yPosition - 1;
		newX	= user->xPosition;
	}
	if (input == 's' || input == 'S')	// Move Down
	{
		newY 	= user->yPosition + 1;
		newX	= user->xPosition;
	}
	if (input == 'a' || input == 'A')	// Move Left
	{
		newY 	= user->yPosition;
		newX	= user->xPosition - 1;
	}
	if (input == 'd' || input == 'D')	// Move Right
	{
		newY 	= user->yPosition;
		newX	= user->xPosition + 1;
	}
	CheckPosition(newY, newX, user);
}

int CheckPosition(int y, int x, Player * user) {
	if ( mvinch(y, x) == '.' )
	{
		playerMove(y, x, user);
	}
	else {
		playerMove(user->yPosition, user->xPosition, user);
	}
}

int playerMove(int y, int x,Player * user) {
	mvprintw(user->yPosition, user->xPosition, ".");	// Change Prev
	user->xPosition 	= x;
	user->yPosition 	= y;
	mvprintw(user->yPosition, user->xPosition, "@");	// Update knew
	move(user->yPosition, user->xPosition);
}

int drawRoom(Room * room) {

	int x;
	int y;
	/* Draw top & bottom */
	for (x = room->xPosition; x < room->xPosition + room->width; ++x )
	{
		mvprintw(room->yPosition, x, "-");	// the top
		mvprintw(room->yPosition + room->height, x, "-");	// the bottom
	}

	for (y = room->yPosition + 1; y < room->yPosition + room->height; ++y)
	{
		/* draw side walls */
		mvprintw(y, room->xPosition, "|");	// Left side
		mvprintw(y, room->xPosition + room->width -1, "|");	// Right side
		for ( x = room->xPosition +1; x < room->xPosition + room->width -1; ++x )
		{
			mvprintw(y, x, ".");
		}
	}
	return 1;	// 1 == Success
}
