// TODO : Validation
// Define el hardcodes

#include "stdlib.h"
#include "ncurses.h"

typedef struct Position { int y; int x; } Position;

typedef struct Snake
{
	Position position;
	// char c;	// snake chars
} Snake;

// ----------------------------------------------------------------------

int initGame();
Snake * initSnake();
// int DeInitGame();	// Unused till now
int mainLoop();
int drawSnake(Position position, Snake * snake);

// ----------------------------------------------------------------------

int main()
{
	initGame();
	refresh();

	endwin();
	
	return 0;
}

int initGame()
{
	Snake * s;
	s = malloc(sizeof(Snake));

	initscr();
	noecho();
	s = initSnake();
	mainLoop(s);

	return 0;
}

// ----------------------------------------------------------------------

int mainLoop(Snake * snake) {
	int ch;
	Position position;
	position.y = snake->position.y;
	position.x = snake->position.x;

	while( (ch = getch()) != 'q' ) {
		// TODO: Arrows Handling
		switch(ch)
		{
			case 'w':
				position.y -= 1;
				break;
			case 's':
				position.y += 1;
				break;
			case 'a':
				position.x -= 1;
				break;
			case 'd':
				position.x += 1;
				break;
			default:
				mvprintw(0,60,"F*ck");
				break;
		}
		drawSnake(position, snake);

		// if (ch == 'w') {
		// 	position.y 						= snake->position.y 		- 1;
		// 	mvprintw(0,0,"%i \t %i", position.y, position.x);
		// 	drawSnake(position, snake);
		// } else if (ch == 's') {
		// 	position.y 						= snake->position.y 		+ 1;
		// 	mvprintw(0,0,"%i \t %i", position.y, position.x);
		// 	drawSnake(position, snake);
		// } else if (ch == 'a') {
		// 	position.x 						= snake->position.x 		- 1;
		// 	mvprintw(0,0,"%i \t %i", position.y, position.x);
		// 	drawSnake(position, snake);
		// } else if (ch == 'd') {
		// 	position.x 						= snake->position.x 		+ 1;
		// 	mvprintw(0,0,"%i \t %i", position.y, position.x);
		// 	drawSnake(position, snake);
		// }
		//
		// mvprintw(0,0,"%i \t %i", position.y, position.x);
	}

	return 1;
}

Snake * initSnake() {
	Snake * snake;
	snake = malloc(sizeof(Snake));
	snake->position.x = 10;		// hardcode
	snake->position.y = 10;		// hardcode
	mvprintw(snake->position.y, snake->position.x, "&");
	// move(snake->position.y, snake->position.x);
	return snake;
}

int drawSnake(Position position, Snake * snake) {
	mvprintw(position.y, position.x, "-");
	return 1;
}