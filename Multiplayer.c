#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "WordList.h"
#include "WordFind.h"
#include "GenBoard.h"
#include "PlayerVersusPlayerAcc.h"
#include "PlayerVersusComputerAcc.h"
#include "ComputerVersusComputerAcc.h"

void multiplayer(void){
  int winner = 0;           //Holds winner of most recent game
  int winCount[] = {0,0,0}; //Stores winner of all games this session.
  char choice[3];           //Stores user input
  wordList();               //Creates trie of words
  while(1){
    printf("pvp = player vs player\n");
    printf("pvc = player vs computer\n");
    printf("cvc = computer vs computer\n");
    printf("Which mode would you like?\n");
    scanf("%s",choice);
    genBoard(); //Generates the board for the coming game
    wordFind(); //Finds all possible words in the board for the coming game
    if(strcmp(choice,"pvp") == 0 ){
      winner = multiplayerAcc();        //The player versus player function
    } else if(strcmp(choice,"pvc") == 0 || strcmp(choice,"cvp") == 0) {
      winner = versusComputerAcc();     //The Player versus Computer option
    } else if(strcmp(choice,"cvc") == 0){
      winner = ComputerVersusComputerAcc();//The computer vs computer option
    } else if(strcmp(choice,"q") == 0) {
      return;
    } else {
      printf("Please input valid option (or q to return to main menu)");
    }
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
}
