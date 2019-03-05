#include <stdio.h>
#include <stdlib.h>
#include "GenBoard.c"
#include "WordFind.c"
#include "WordList.c"


int main(void){
  wordList();
  printf("\n");
  genBoard();
  printf("\n");
  wordFind();
  printf("\n");
  return 0;
}
