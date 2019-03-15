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
  int highscore = 0;
  char choice[3];
  //struct foundWord *check = NULL;
  wordList();
  while(1){
    //check = foundRoot;
    genBoard();
    wordFind();
    score = playerAcc();
    printf("\n");
    printf("\n");
    printf("You scored a total of %d points!\n",score);
    printf("\n");
    if(score > highscore){
      printf("You beat the highscore of %d points!\n",highscore);
      printf("You have the new highscore!");
      highscore = score;
    }
    printf("\n");/*This portion of code doesn't print anything
    printf("Would you like to see the possible words?\n");
    scanf("%s",choice);
    for(int i = 0;i < 3;i++){
      choice[i] = tolower(choice[i]);
    }
    if(strcmp(choice,"yes") == 0 || strcmp(choice,"y") == 0){
      while(check != NULL){
        printf("%s\n",check->storedWord);
        check = check->next;
      }
    }*/
    printf("\n");
    printf("Would you like to play again?\n");
    scanf("%s",choice);
    for(int i = 0;i < 3;i++){
      choice[i] = tolower(choice[i]);
    }
    printf("\n");
    if(strcmp(choice,"no") == 0 || strcmp(choice,"n") == 0){
      break;
    }
  }

  return 0;
}
