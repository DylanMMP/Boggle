#include <stdio.h>
#include <ctype.h>
#include "SinglePlayer.c"
#include "Multiplayer.c"

int main(void){
  char choice[10];
    printf("Would you like to play single player or multiplayer?\n");
  while(1){
    scanf("%s",choice);
    if(strcmp(choice,"single") == 0 || strcmp(choice,"singleplayer") == 0){
      singlePlayer();
    } else if(strcmp(choice,"multi") == 0 || strcmp(choice,"multiplayer") == 0){
      multiplayer();
    } else if(strcmp(choice,"q") == 0){
      break;
    } else {
      printf("Please enter a valid input\n");
    }
    printf("Enter 'q' to quit\n");
    printf("Enter game mode: (singleplayer or multiplayer)\n");
  }

  return 0;
}
