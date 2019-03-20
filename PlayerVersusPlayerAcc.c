//This class manages the player vs player scenario for Boggle.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "WordFind.h"

#define PLAYER_ONE (0)
#define PLAYER_TWO (1)

//We use a linked list of strings to store all words that have already been found
struct scoredWordMP{
  char word[45];
  struct scoredWordMP *next;
};

//Function to create nodes for scored word list
struct scoredWordMP *scoredWordMPNode(void) {
  struct scoredWordMP *node = NULL;                               //Creating node
  node = (struct scoredWordMP *)malloc(sizeof(struct scoredWordMP)); //Dynamically allocating node

  if(node) {
    strcpy(node->word,"\0");
    node->next = NULL;
  }
  return node;
}

//The root of the linked list
struct scoredWordMP *scoredMPRoot;

//Function for adding new scored words to the ScoredWordCVC linked list
void newscoredWordMP(char *word){
  struct scoredWordMP *newNode = scoredWordMPNode();
  struct scoredWordMP *check = scoredMPRoot;
  strcpy(newNode->word,word);
  if(check->next == NULL){ //If the list has no words, we simply make this the first word in the list
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
int scoreWordMP(char *word){
  struct scoredWordMP *check = scoredMPRoot;
  //This while loop verifies that a word already scored cannot be scored again.
  while(check != NULL){
    if(strcmp(check->word,word) == 0){
      printf("%s has already been entered!\n",word);
      return -1;
    }
    check = check->next;
  }
  if(strlen(word) == 3 || strlen(word) == 4){    //Words with 3 to 4 letters get 1 point
    newscoredWordMP(word);
    return 1;
  }else if(strlen(word) == 5){    //Words with 5 letters get 2 points
    newscoredWordMP(word);
    return 2;
  }else if(strlen(word) == 6){    //Words with 6 letters get 3 points
    newscoredWordMP(word);
    return 3;
  }else if(strlen(word) == 7){    //Words with 7 letters get 4 points
    newscoredWordMP(word);
    return 4;
  }else if(strlen(word) >= 8){    //Words with 8 or more letters get 11 points
    newscoredWordMP(word);
    return 11;
  } else {                        //Words with less than 3 letters get 0 points
    newscoredWordMP(word);
    return 0;
  }
}

//This is a driver function that carries out the computer vs computer gameplay from the user's perspective
//The reason we do this instead of calling the above functions in the function which calls ComputerVersusComputerAcc
//Is to minimize coupling between functions.
int multiplayerAcc(void){
  bool turn = PLAYER_ONE;
  int winner = 0;
  struct foundWord *check;
  scoredMPRoot = scoredWordMPNode();
  char input[45];
  int pointTotalP1 = 0;
  int pointTotalP2 = 0;
  int pointValue = 0;
  printf("Input words (or 'q' to quit)\n");
  while(1){

    check = foundRoot;

    if(turn == PLAYER_ONE){
      printf("Player 1 Guess: ");
    } else {
      printf("Player 2 Guess: ");
    }
    scanf("%s",input);

    if(strcmp(input,"q") == 0){
      break;
    }
    //This loop iterates through the list of found words to see if the entered word exists
    while(1){
      if(strcmp(input,check->storedWord) == 0){
        pointValue = scoreWordMP(input);
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
    if(turn == PLAYER_ONE && pointValue != -1){
      pointTotalP1 += pointValue;
      turn = PLAYER_TWO;
    } else if(turn == PLAYER_TWO && pointValue != -1){
      pointTotalP2 += pointValue;
      turn = PLAYER_ONE;
    } else {
      turn = !turn;
    }
  }
  printf("\n");
  printf("Player 1 had %d points\n",pointTotalP1);
  printf("Player 2 had %d points\n",pointTotalP2);

  if(pointTotalP1 > pointTotalP2){ //Player 1 wins
    printf("Player 1 wins by %d points!",pointTotalP1 - pointTotalP2);
    winner = 1;
  } else if (pointTotalP1 < pointTotalP2){ //Player 2 wins
    printf("Player 2 wins by %d points!",pointTotalP2 - pointTotalP1);
    winner = 2;
  } else {  //It's a tie
    winner = 0;
  }
  return winner;
}
