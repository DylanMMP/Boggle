//How to bring in things from other classes?
//How to store found words?

#include <stdio.h>
#include <stdlib.h>
//Definition to get size of an array
#define LEN(arr) ((int)(sizeof(arr) / sizeof(arr)[0]));

/*int* checkAdjacent(char* board[], int* checked[], int posX, int posY){

}*/

void wordFind(void){
  char board[4][4] = {{'A','A','H','U'},{'O','P','P','L'},{'E','J','E','F'},{'T','X','L','L'}};

  int width = LEN(board);
  int height = LEN(board[0]);

/*
  for(int j = 0; j < height; j++){
    for(int k = 0; k < width; k++){
      checkAdjacent(*Board[],*checked[],j,k);
    }
  }*/
  printf("Width = %d\n",width);
  printf("Height= %d\n",height);
}
