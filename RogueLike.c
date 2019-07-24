// TODO : Separate code to files at the end of project
// TODO : comment & describe every function
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
/* Level/map functions */
Room ** MapSetUp();		// returns pointer to 2D array : master array
char ** saveLevelPositions();
/*  */
Player * PlayerSetUp();
Position * handleInput(int input, Player * user);
int CheckPosition(Position * newPosition, Player * user, char ** level);
int playerMove(Position * newPosition, Player * user, char ** level);
/* Room functions */
Room * createRoom(int y, int x, int height, int width );
int drawRoom(Room * room);
int connectDoors(Position * doorOne, Position * doorTwo);


// -----------------------------------------------------------------------------------
int main(void) {
	int ch;
	Player * user;
	char ** level;
	Position * newPosition;

	ScreenSetUp();
	MapSetUp();
	level = saveLevelPositions();
	user = PlayerSetUp();

	/* Main Game Loop */
	while( (ch = getch()) != 'q' ) {
		newPosition = handleInput(ch, user);
		CheckPosition(newPosition, user, level);
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

	// --
	rooms[0] 	= createRoom(13, 13, 6, 21);
	drawRoom(rooms[0]);

	rooms[1] 	= createRoom(13, 50, 6, 21);
	drawRoom(rooms[1]);

	rooms[2] 	= createRoom(2, 25, 6, 21);
	drawRoom(rooms[2]);

	// --
	connectDoors(rooms[1]->doors[1], rooms[0]->doors[3]);
	connectDoors(rooms[2]->doors[2], rooms[0]->doors[0]);
	connectDoors(rooms[2]->doors[3], rooms[1]->doors[0]);
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

	/* Left door */
	newRoom->doors[1]			= malloc(sizeof(Position));
	newRoom->doors[1]->x 		= newRoom->position.x;
	newRoom->doors[1]->y 		= rand() % (height -2) + newRoom->position.y +1;

	/* Bottom door */
	newRoom->doors[2]			= malloc(sizeof(Position));
	newRoom->doors[2]->x 		= rand() % (width -2) + newRoom->position.x +1;
	newRoom->doors[2]->y 		= newRoom->position.y + newRoom->height;

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
	newPlayer->health		= 20;		// = Useless till now!
	mvprintw(15, 20, "@");	// Update knew
	move(15, 20);

	return newPlayer;
}

Position * handleInput(int input, Player * user) {
	Position * newPosition;
	newPosition = malloc(sizeof(Position));
	
	if (input == 'w' || input == 'W')	// Move Up
	{
		newPosition->y 	= user->position.y - 1;
		newPosition->x	= user->position.x;
	}
	if (input == 's' || input == 'S')	// Move Down
	{
		newPosition->y 	= user->position.y + 1;
		newPosition->x	= user->position.x;
	}
	if (input == 'a' || input == 'A')	// Move Left
	{
		newPosition->y 	= user->position.y;
		newPosition->x	= user->position.x - 1;
	}
	if (input == 'd' || input == 'D')	// Move Right
	{
		newPosition->y 	= user->position.y;
		newPosition->x	= user->position.x + 1;
	}
	return newPosition;
}

int CheckPosition(Position * newPosition, Player * user, char ** level) {
	if ( mvinch(newPosition->y, newPosition->x) == '.' 	|| 
		mvinch(newPosition->y, newPosition->x) == '+' 	|| 
		mvinch(newPosition->y, newPosition->x) == '#' )
	{
		playerMove(newPosition, user, level);
	}
	else {
		move(user->position.y, user->position.x + 0);
	}
	return 1;
}

int playerMove(Position * newPosition,Player * user, char ** level) {
	char buffer[8];
	sprintf(buffer, "%c", level[user->position.y][user->position.x]);	// convert single char to string of char

	mvprintw(user->position.y, user->position.x, buffer);	// Change Prev
	user->position.y 	= newPosition->y;
	user->position.x 	= newPosition->x;
	mvprintw(user->position.y, user->position.x, "@");	// Update knew
	move(user->position.y, user->position.x);
	return 1;
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

int connectDoors(Position * doorOne, Position * doorTwo) {

	Position temp;
	Position prev;

	temp.x 		= doorOne->x;
	temp.y 		= doorOne->y;
	
	int count 	= 0;

	prev 		= temp;

	while(1) {
		// Move Left
		if (abs( (temp.x -1) - doorTwo->x) < abs( ( temp.x) - doorTwo->x) && mvinch(temp.y, temp.x -1) == ' ')
		{
			prev.x 	= temp.x;
			temp.x 	= temp.x -1;
		}
		// Move Right
		else if (abs( temp.x +1 - doorTwo->x) < abs( ( temp.x) - doorTwo->x) && mvinch(temp.y, temp.x +1) == ' ')
		{
			prev.x 	= temp.x;
			temp.x 	= temp.x +1;
		}
		// Move down
		else if (abs( (temp.y +1) - doorTwo->y) < abs( ( temp.y) - doorTwo->y) && mvinch(temp.y +1, temp.x) == ' ')
		{
			prev.x 	= temp.x;
			temp.y 	= temp.y +1;
		}
		// Move up
		else if (abs( (temp.y +1) - doorTwo->y) < abs( ( temp.y) - doorTwo->y) && mvinch(temp.y -1, temp.x) == ' ')
		{
			prev.x 	= temp.x;
			temp.y 	= temp.y +1;
		}
		else
		{
			if( count == 0) {
				temp = prev;
				count++;
				continue;
			} else {
				return 0;
			}
		}
		mvprintw(temp.y, temp.x, "#");
		// getch();			// REMOVE ME !!!!!!!!
	}

	return 1;	// 1 == Success
}

/**
Master Function!
This func saves every single locaiton in 2D array
*/
char ** saveLevelPositions() {
	int y, x;
	char ** positions;
	positions = malloc(sizeof(char *) * 25);

	for (int y = 0; y < 25; ++y)
	{
		positions[y] = malloc(sizeof(char)*100);
		for (x = 0; x < 100; ++x)
		{
			positions[y][x] = mvinch(y, x);
		}
	}
	return positions;
}