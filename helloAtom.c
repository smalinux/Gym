/**
* ===================================
* ===================================
*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/*
int board[25] = {
  :,:,:,:,:,
  :,O,-,X,:,
  :,X,-,-,:,
  :,-,-,-,:,
}
*/

// const EMPTY     = 0;
// const NOUGHTS   = 1;      // without int !!!
// const CHROSSES  = 2;
// const BORDER    = 3;
enum {EMPTY, NOUGHTS, CHROSSES, BORDER};
enum {HUMANWIN, COMPWIN, DRAW};

const int ConvertTo25[] = {   // Very Nice idea ; ) actual places in 25 square board ; )
  6,    7   ,8,
  11,   12  ,13,
  16,   17  ,18,
};


void InitBoard(int *board) {
  int i = 0;
  for (i = 0; i < 25; ++i) {
    board[i] = BORDER;
  }
  for (i = 0; i < 9; ++i) {
    board[ConvertTo25[i]] = EMPTY;      // nice nested array ; )
  }
}

void PrintBoard(const int *board) {
  printf("\nBorad:\n");
  int i = 0;
  for (i = 0; i < 25; ++i) {

    if (i%5==0 && i!=0) {             // no spaces ; )
      printf("\n\n");
    }
    if(board[i] == BORDER) {
      printf("%4s ", " ");
    } else if (board[i] == CHROSSES) {
      printf("%4s", "X");
    }  else if (board[i] == NOUGHTS) {
      printf("%4s", "O");
    }  else if (board[i] == EMPTY) {
      printf("%4s", "-");
    } else {
      printf("%4d", board[i]);
    }
  }
  printf("\n");
}

void MakeMove(int *board, const sq, const side) {
  board[sq] = side;           // Very Simple! ; )
}

int GetHumanMove(int *board) {

  char userInput[4];
  int moveOk  = 0;
  int move    = -1;

  while (moveOk == 0) {
    printf("Please enter a move from 1 to 9: ");
    fgets(userInput, 3, stdin);
    // Validations ....
    // https://www.youtube.com/watch?v=GP7H4M5jXLk&list=PLZ1QII7yudbc7_ZgXA-gIXmME41Rs2GP5&index=4
    move--;   // Zero Indexing
    moveOk = !moveOk;
  }
}

int HasEmpty(const int *board) {
  int i = 0;
  for (i = 0; i < 9; ++i) {
    if (board[ConvertTo25[0]] == EMPTY) {
      return 1;
    }
  }
  return 0;
}

void RunGame() {
  int GameOver = 0;
  int Side = NOUGHTS;         // human player
  int LastMoveMade = 0;
  int board[25];

  InitBoard(&board[0]);
  PrintBoard(&board[0]);
  while (!GameOver) {
    if (Side==NOUGHTS) {
      // get move from human, make move on board, Change side
      GetHumanMove(&board[0]);
    } else {
      // get move from Computer, make move on board, Change side
      PrintBoard(&board[0]);
    }

    // if Three in a row exists == Game is Over
    // if (/* condition */) {
    //   /* code */
    // }

    // if no more moves, Game is a draw
    // if(!HasEmpty(&board[0])) {
    //   // GameOver
    // }

    GameOver = !GameOver;   // REMOVE ME !!

  }
}

int main(int argc, char const *argv[]) {

  RunGame();

  return 0;
}
