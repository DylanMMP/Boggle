//How to bring in things from other classes?
//How to store found words?

#include <stdio.h>
#include <stdlib.h>
#include "GenBoard.h"
//Definition to get size of an array
#define LEN(arr) ((int)(sizeof(arr) / sizeof(arr)[0]));


void wordFind(){
  //char board[4][4] = {{'A','A','H','U'},{'O','P','P','L'},{'E','J','E','F'},{'T','X','L','L'}};

  int width = LEN(Board);
  int height = LEN(Board[0]);

/*
  for(int j = 0; j < height; j++){
    for(int k = 0; k < width; k++){
      checkAdjacent(*Board[],*checked[],j,k);
    }
  }*/
  printf("Width = %d\n",width);
  printf("Height= %d\n",height);
}
