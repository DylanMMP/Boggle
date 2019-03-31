//The intent of this program is to allow player to play Boggle in both
//a singleplayer and multiplayer mode.
//This function acts as a main menu and a main function.
#include <stdio.h>
#include <ctype.h>
#include "SinglePlayer.c"
#include "Multiplayer.c"
#include "WordList.h"

int main(void){
  wordList();
  char choice[10]; //Stores user choices
select:
  printf("Would you like to play singleplayer or multiplayer?\n");
  while(1){
    scanf("%s",choice);
    if(strcmp(choice,"single") != 0 && strcmp(choice,"singleplayer") != 0
          && strcmp(choice,"multi") != 0 && strcmp(choice,"multiplayer") != 0
          && strcmp(choice,"q") != 0){
          goto select;
    }
    if(strcmp(choice,"single") == 0 || strcmp(choice,"singleplayer") == 0){
      singlePlayer(); //Takes player to single player menu
    } else if(strcmp(choice,"multi") == 0 || strcmp(choice,"multiplayer") == 0){
      multiplayer(); //Takes player to multiplayer menu
    } else if(strcmp(choice,"q") == 0){
      break; //Exits loop
    } else {
      printf("Please enter a valid input\n");
    }
    printf("Enter 'q' to quit\n");
    printf("Enter game mode: (singleplayer or multiplayer)\n");
  }
  freeTrie(root);
  exit(0);
}
