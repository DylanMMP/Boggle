//Dylan Marcum-Pollard | dmmarcumpollard@crimson.ua.edu
//This class manages the computer versus computer scenario for Boggle.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "WordFind.h"

#define PLAYER_ONE (0)
#define PLAYER_TWO (1)
#define THREE_MINUTES (180)

//We use a linked list of strings to store all words that have already been found
struct ScoredWordCVC{
  char word[45];
  struct ScoredWordCVC *next;
};

//Function to create nodes for scored word list
struct ScoredWordCVC *ScoredWordCVCNode(void) {
  struct ScoredWordCVC *node = NULL;
  node = (struct ScoredWordCVC *)malloc(sizeof(struct ScoredWordCVC));

  if(node) {
    strcpy(node->word,"\0");
    node->next = NULL;
  }
  return node;
}

//The root of the linked list
struct ScoredWordCVC *ScoredCVCRoot;

void clearScoredWordCVC(){
  struct ScoredWordCVC *temp;
  while(ScoredCVCRoot != NULL){
    temp = ScoredCVCRoot;
    ScoredCVCRoot = ScoredCVCRoot->next;
    free(temp);
  }
}

//Function for adding new scored words to the ScoredWordCVC linked list
void newScoredWordCVC(char *word){
  struct ScoredWordCVC *newNode = ScoredWordCVCNode();
  struct ScoredWordCVC *check = ScoredCVCRoot;
  strcpy(newNode->word,word);
  if(check->next == NULL){  //If the list has no words, we simply make this the first word in the list
    check->next = newNode;
    return;
  }
  /*Otherwise, we need to iterate through until we find the appropriate location.
  * Note that this insertion loop puts the found words in alphabetical order
  * NOT the order that they were found in. This is to prevent duplicate words.
  */
  while(check != NULL){
    if(check->next == NULL){
        check->next = newNode;
        return;
    } else if(strcmp(check->next->word,newNode->word) < 0){
        //If the word appears after the checked word alphabetically, then iterate onward
        check = check->next;
    } else if(strcmp(check->next->word,newNode->word) > 0){
      //If the word appears before the checked word alphabetically, place it between the
      //word being currently checked and the next word.
      newNode->next = check->next;
      check->next = newNode;
      return;
    } else if(strcmp(check->next->word,newNode->word) == 0){
      //If the word is the same as a word currently stored, DO NOT store it twice.
      return;
    }
  }
}

//Function to get the point value for words based on their length, as per the rules of Boggle
int scoreWordCVC(char *word){
  struct ScoredWordCVC *check = ScoredCVCRoot;
  //This while loop verifies that a word already scored cannot be scored again.
  while(check != NULL){
    if(strcmp(check->word,word) == 0){
      printf("%s has already been entered!\n",word);
      return -1;
    }
    check = check->next;
  }
  if(strlen(word) == 3 || strlen(word) == 4){ //Words with 3 to 4 letters get 1 point
    newScoredWordCVC(word);
    return 1;
  }else if(strlen(word) == 5){                //Words with 5 letters get 2 points
    newScoredWordCVC(word);
    return 2;
  }else if(strlen(word) == 6){                //Words with 6 letters get 3 points
    newScoredWordCVC(word);
    return 3;
  }else if(strlen(word) == 7){                //Words with 7 letters get 4 points
    newScoredWordCVC(word);
    return 4;
  }else if(strlen(word) >= 8){                //Words with 8 or more letters get 11 points
    newScoredWordCVC(word);
    return 11;
  } else {                                    //Words with less than 3 letters get 0 points
    newScoredWordCVC(word);
    return 0;
  }
}

//This is a driver function that carries out the computer vs computer gameplay from the user's perspective
//The reason we do this instead of calling the above functions in the function which calls ComputerVersusComputerAcc
//Is to minimize coupling between functions.
int ComputerVersusComputerAcc(void){
  bool turn = PLAYER_ONE;
  int winner = 0;
  struct foundWord *check;
  time_t t;
  srand((unsigned) time(&t));
  int randomNum;

  ScoredCVCRoot = ScoredWordCVCNode();

  char input[45];
  int pointTotalP1 = 0;
  int pointTotalP2 = 0;
  int pointValue = 0;
  printf("Input words (or 'q' to quit)\n");

  while(1){
    check = foundRoot;
    if(turn == PLAYER_ONE){
      printf("Computer 1 Guess: ");
      //There is a 10% chance whenever it is the computer's turn that the computer will quit.
      //This is because in Player vs Player, either player can quit when they have the lead.
      randomNum = rand() % 10;
      if(randomNum == 0){
        printf("Computer 1 quits!\n");
        break;
      }
      //The computer 'guesses' by entering a random word that has been found.
      //The computer can 'forget' that a word has been entered already, thus entering the same word twice.
      randomNum = rand() % numStored;
      for(int i = 0; i < randomNum; i++){
        check = check->next;
      }
      for(int i = 0; i < 45; i++){
        input[i] = check->storedWord[i];
      }
    } else {  //Since turn is a boolean, if it isn't player one's turn, it HAS to be player two's
      printf("Computer 2 Guess: ");
      //There is a 10% chance whenever it is the computer's turn that the computer will quit.
      //This is because in Player vs Player, either player can quit when they have the lead.
      randomNum = rand() % 10;
      if(randomNum == 0){
        printf("Computer 2 quits!\n");
        break;
      }
      //The computer 'guesses' by entering a random word that has been found.
      //The computer can 'forget' that a word has been entered already, thus entering the same word twice.
      randomNum = rand() % numStored;
      for(int i = 0; i < randomNum; i++){
        check = check->next;
      }
      for(int i = 0; i < 45; i++){
        input[i] = check->storedWord[i];
      }
    }
    check = foundRoot;
    //This loop iterates through the list of found words to see if the entered word exists
    while(1){
      //This if statement triggers if the word is found.
      if(strcmp(input,check->storedWord) == 0){
        pointValue = scoreWordCVC(input);
        //This if statement verifies that the word has not been previously entered.
        if(pointValue == -1){
          pointValue = 0;
          break;
        }
        printf("%s found! %s is worth %d points!\n",input,input,pointValue);
        break;
      //This if statement ends the loop if the word isn't found in the found words list
      } else if(strcmp(input,check->storedWord) != 0 && check->next == NULL) {
        printf("Word not found!\n");
        break;
      } else {
        check = check->next;
      }
    }
    //The following if and else if statements simply increment points and change the player state.
    if(turn == PLAYER_ONE){
      pointTotalP1 += pointValue;
      pointValue = 0;
      turn = PLAYER_TWO;
    } else if(turn == PLAYER_TWO){
      pointTotalP2 += pointValue;
      pointValue = 0;
      turn = PLAYER_ONE;
    } else {
      turn = !turn;
    }
  }

  printf("\n");
  printf("Player 1 had %d points\n",pointTotalP1);
  printf("Player 2 had %d points\n",pointTotalP2);

  if(pointTotalP1 > pointTotalP2){ //Player 1 wins
    winner = 1;
  } else if (pointTotalP1 < pointTotalP2){ //Player 2 wins
    winner = 2;
  } else {  //It's a tie
    winner = 0;
  }
  clearFoundWord();
  clearScoredWordCVC();
  return winner;
}
