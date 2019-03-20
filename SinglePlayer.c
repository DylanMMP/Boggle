//The intent behind this class is to provide the singleplayer menu screen

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "WordList.h"
#include "WordFind.h"
#include "GenBoard.h"
#include "playerAcc.h"

int singlePlayer(void){
  int score = 0;
  int highscore = 0;
  char choice[3];
  wordList();
  while(1){
    genBoard();
    wordFind();
    score = playerAcc();
    printf("\n");
    printf("\n");
    printf("You scored a total of %d points!\n",score);
    printf("\n");
    //Since there isn't a win-loss table, we have a highscoreboard
    //Like the win-loss, it resets when you leave the singleplayer menu.
    if(score > highscore){
      printf("You beat the highscore of %d points!\n",highscore);
      printf("You have the new highscore!");
      highscore = score;
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
    //We free the memory of the board before creating a new one
    for(int i = 0; i < height;i++){
      free(Board[i]);
    }
    free(Board);
  }

  return 0;
}
