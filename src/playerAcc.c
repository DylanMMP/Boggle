//Dylan Marcum-Pollard | dmmarcumpollard@crimson.ua.edu
//This class manages the singleplayer scenario for Boggle.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "WordFind.h"

#define THREE_MINUTES (180)

//We use a linked list of strings to store all words that have already been found
struct scoredWord{
  char word[45];
  struct scoredWord *next;
};

//Function to create nodes for scored word list

struct scoredWord *scoredWordNode(void) {
  struct scoredWord *node = NULL;
  node = (struct scoredWord *)malloc(sizeof(struct scoredWord));

  if(node) {
    strcpy(node->word,"\0");
    node->next = NULL;
  }
  return node;
}

//The root of the linked list
struct scoredWord *scoredRoot;

//Function for adding new scored words to the ScoredWordCVC linked list
void newScoredWord(char *word){
  struct scoredWord *newNode = scoredWordNode();
  struct scoredWord *check = scoredRoot;
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
      free(newNode);
      return;
    }
  }
}

void clearScoredWord(){
  struct scoredWord *temp;
  while(scoredRoot != NULL){
    temp = scoredRoot;
    scoredRoot = scoredRoot->next;
    free(temp);
  }
}

//Function to get the point value for words based on their length, as per the rules of Boggle
int scoreWord(char *word){
  struct scoredWord *check = scoredRoot;
  //This while loop verifies that a word already scored cannot be scored again.
  while(check != NULL){
    if(strcmp(check->word,word) == 0){
      printf("You have already entered %s!\n",word);
      return -1;
    }
    check = check->next;
  }
  if(strlen(word) == 3 || strlen(word) == 4){
    newScoredWord(word);
    return 1;
  }else if(strlen(word) == 5){
    newScoredWord(word);
    return 2;
  }else if(strlen(word) == 6){
    newScoredWord(word);
    return 3;
  }else if(strlen(word) == 7){
    newScoredWord(word);
    return 4;
  }else if(strlen(word) >= 8){
    newScoredWord(word);
    return 11;
  } else {
    newScoredWord(word);
    return 0;
  }
}

//This is a driver function that carries out the computer vs computer gameplay from the user's perspective
//The reason we do this instead of calling the above functions in the function which calls ComputerVersusComputerAcc
//Is to minimize coupling between functions.
int playerAcc(void){

  struct foundWord *check;
  scoredRoot = scoredWordNode();
  char input[45];
  int pointTotal = 0;
  int pointValue = 0;
  time_t start;
  time_t curTime;
  int diff = 0;
  int minutes = 0;
  int seconds = 0;
  int remaining = 0;
  time(&start);
  printf("Input words (or 'q' to quit)\n");

  while(1){
    time(&curTime);
    diff = difftime(curTime,start);
    remaining = THREE_MINUTES - diff;
    minutes = remaining / 60;
    seconds = remaining % 60;
    if(diff >= THREE_MINUTES){
      printf("Time is up!\n");
      break;
    }
    printf("\n%d minutes %d seconds remaining\n",minutes,seconds);
    check = foundRoot;
    printf("Guess: ");
    scanf("%45s", input);
    int c;
    while ((c = fgetc(stdin)) != '\n' && c != EOF);

    if(strcmp(input,"q") == 0){
      break;
    }
    //This loop iterates through the list of found words to see if the entered word exists
    while(1){
      //This if statement triggers if the word is found.
      if(strcmp(input,check->storedWord) == 0){
        pointValue = scoreWord(input);
        //This if statement verifies that the word has not been previously entered.
        if(pointValue == -1){
          pointValue = 0;
          break;
        }
        //We update the point total;
        pointTotal += pointValue;
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
  }
  clearScoredWord();
  clearFoundWord();
  return pointTotal;
}
