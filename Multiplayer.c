#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "WordList.h"
#include "WordFind.h"
#include "GenBoard.h"
#include "multiplayerAcc.c"

int multiplayer(void){
  int winner = 0;
  int winCount[] = {0,0,0};
  char choice[3];
  wordList();
  while(1){
    genBoard();
    wordFind();
    winner = multiplayerAcc();
    winCount[winner]++;
    printf("\n");
    printf("\n");
    printf("Player 1 wins: %d\n",winCount[1]);
    printf("Player 2 wins: %d\n",winCount[2]);
    if(winCount[0] > 0){
      printf("Number of draws: %d",winCount[0]);
    }
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
