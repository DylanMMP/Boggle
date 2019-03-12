#include <stdio.h>
#include <stdlib.h>
//#include "GenBoard.c"
#include "WordFind.c"
#include "WordList.h"
#include "GenBoard.h"

int main(void){
  extern struct boardNode **Board;
  wordList();
  printf("\n");
  genBoard();
  printf("\n");
  wordFind();
  printf("\n");
  int height = 5;
  int width = 5;
  for(int j = 0; j < height; j++){
    for(int k = 0; k < width; k++){
      printf("%c",Board[0][0].boardChar);
    }
    printf("\n");
  }

 return 0;
}
