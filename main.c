#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "WordList.h"
#include "WordFind.h"
#include "GenBoard.h"
#include "playerAcc.c"

int main(void){
  int score = 0;
  char choice[3];
  struct foundWord *check = NULL;
  wordList();
  while(1){
    check = foundRoot;
    genBoard();
    wordFind();
    score = playerAcc();
    printf("You scored %d points!\n",score);
    printf("Would you like to see the possible words?");
    scanf("%s",choice);
    for(int i = 0;i < 3;i++){
      choice[i] = tolower(choice[i]);
    }
    if(strcmp(choice,"yes") == 0 || strcmp(choice,"y") == 0){
      while(check != NULL){
        printf("%s\n",check->storedWord);
        check = check->next;
      }
    }
    printf("Would you like to play again? ");
    scanf("%s",choice);
    for(int i = 0;i < 3;i++){
      choice[i] = tolower(choice[i]);
    }
    if(strcmp(choice,"no") == 0 || strcmp(choice,"n") == 0){
      break;
    }
  }

  return 0;
}
