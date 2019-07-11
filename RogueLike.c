#include "stdlib.h"
#include "ncurses.h"
#include "time.h"

typedef struct Position
{
	int y;
	int x;
	// TILE_TYLE tile
} Position;

typedef struct Room
{
	Position position;
	int height;
	int width;
	Position ** doors;
	//
	// Monster ** monsters;		// pointer to array of structs ! i think !!
	// Item ** items;
} Room;

typedef struct Player
{
	Position position;
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
	srand(time(NULL));		// What this MEAM ?!
	noecho();

	return 1;	// 1 == Succes & 0 == failure !!
}

Room ** MapSetUp() {		// Array of structs
	Room ** rooms;			// Create array of room! very simple xD
	rooms	= malloc(sizeof(Room) * 6);

	rooms[0] 	= createRoom(13, 13, 6, 21);
	drawRoom(rooms[0]);

	rooms[1] 	= createRoom(13, 50, 6, 21);
	drawRoom(rooms[1]);

	rooms[2] 	= createRoom(2, 25, 6, 21);
	drawRoom(rooms[2]);

	return rooms;
}

Room * createRoom(int y, int x, int height, int width ) {
	Room * newRoom;
	newRoom		= malloc(sizeof(Room));

	newRoom->position.y		= y;
	newRoom->position.x		= x;
	newRoom->height			= height;
	newRoom->width			= width;

	newRoom->doors			= malloc(sizeof(Position) * 4);

	// Doors ..

	/* Top door */
	newRoom->doors[0]			= malloc(sizeof(Position));
	newRoom->doors[0]->x 		= rand() % (width -2) + newRoom->position.x +1;
	newRoom->doors[0]->y 		= newRoom->position.y;

	/* Bottom door */
	newRoom->doors[1]			= malloc(sizeof(Position));
	newRoom->doors[1]->x 		= rand() % (width -2) + newRoom->position.x +1;
	newRoom->doors[1]->y 		= newRoom->position.y + newRoom->height;

	/* Left door */
	newRoom->doors[2]			= malloc(sizeof(Position));
	newRoom->doors[2]->x 		= newRoom->position.x;
	newRoom->doors[2]->y 		= rand() % (height -2) + newRoom->position.y +1;

	/* Right door */
	newRoom->doors[3]			= malloc(sizeof(Position));
	newRoom->doors[3]->x 		= newRoom->position.x + width -1;
	newRoom->doors[3]->y 		= rand() % (height -2) + newRoom->position.y +1;

	return newRoom;
}

Player * PlayerSetUp() {
	Player * newPlayer;
	newPlayer = malloc(sizeof(Player));

	newPlayer->position.x 	= 20;
	newPlayer->position.y 	= 15;
	newPlayer->health		= 20;
	playerMove(15, 20, newPlayer);

	return newPlayer;
}

int handleInput(int input, Player * user) {
	int newX;
	int newY;
	if (input == 'w' || input == 'W')	// Move Up
	{
		newY 	= user->position.y - 1;
		newX	= user->position.x;
	}
	if (input == 's' || input == 'S')	// Move Down
	{
		newY 	= user->position.y + 1;
		newX	= user->position.x;
	}
	if (input == 'a' || input == 'A')	// Move Left
	{
		newY 	= user->position.y;
		newX	= user->position.x - 1;
	}
	if (input == 'd' || input == 'D')	// Move Right
	{
		newY 	= user->position.y;
		newX	= user->position.x + 1;
	}
	CheckPosition(newY, newX, user);
}

int CheckPosition(int y, int x, Player * user) {
	if ( mvinch(y, x) == '.' )
	{
		playerMove(y, x, user);
	}
	else {
		playerMove(user->position.y, user->position.x, user);
	}
}

int playerMove(int y, int x,Player * user) {
	mvprintw(user->position.y, user->position.x, ".");	// Change Prev
	user->position.x 	= x;
	user->position.y 	= y;
	mvprintw(user->position.y, user->position.x, "@");	// Update knew
	move(user->position.y, user->position.x);
}

int drawRoom(Room * room) {

	int x;
	int y;
	/* Draw top & bottom */
	for (x = room->position.x; x < room->position.x + room->width; ++x )
	{
		mvprintw(room->position.y, x, "-");	// the top
		mvprintw(room->position.y + room->height, x, "-");	// the bottom
	}

	for (y = room->position.y + 1; y < room->position.y + room->height; ++y)
	{
		/* draw side walls */
		mvprintw(y, room->position.x, "|");	// Left side
		mvprintw(y, room->position.x + room->width -1, "|");	// Right side
		for ( x = room->position.x +1; x < room->position.x + room->width -1; ++x )
		{
			mvprintw(y, x, ".");
		}
	}
	/* Draw doors */
	mvprintw(room->doors[0]->y, room->doors[0]->x, "+");
	mvprintw(room->doors[1]->y, room->doors[1]->x, "+");
	mvprintw(room->doors[2]->y, room->doors[2]->x, "+");
	mvprintw(room->doors[3]->y, room->doors[3]->x, "+");
	return 1;	// 1 == Success
}
