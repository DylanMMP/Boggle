#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "WordFind.h"
#include "WordList.h"
#include "GenBoard.h"

int main(void){

  wordList();
  printf("wordlist complete\n");
  printf("\n");
  genBoard();
  printf("genboard complete\n");
  printf("\n");
  wordFind();
  printf("wordfind complete\n");
  printf("\n");

 return 0;
}
