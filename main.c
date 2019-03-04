#include <stdio.h>
#include <stdlib.h>
#include "GenBoard.c"
#include "WordFind.c"
#include "WordList.c"


int main(void){
  genBoard();
  printf("\n");
  wordFind();
  printf("\n");
  wordList();
  printf("\n");
  return 0;
}
