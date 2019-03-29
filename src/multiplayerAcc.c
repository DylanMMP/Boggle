#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "WordFind.h"

#define PLAYER_ONE (0)
#define PLAYER_TWO (1)

struct scoredWordMP{
  char word[MAX_WORD_SIZE];
  struct scoredWordMP *next;
};

struct scoredWordMP *scoredWordMPNode(void) {
  struct scoredWordMP *node = NULL;                               //Creating node
  node = (struct scoredWordMP *)malloc(sizeof(struct scoredWordMP)); //Dynamically allocating node

  if(node) {
    strcpy(node->word,"\0");
    node->next = NULL;
  }
  return node;
}

struct scoredWordMP *scoredMPRoot;

void newscoredWordMP(char *word){
  struct scoredWordMP *newNode = scoredWordMPNode();
  struct scoredWordMP *check = scoredMPRoot;
  strcpy(newNode->word,word);
  if(check->next == NULL){
    check->next = newNode;
    return;
  }
  while(check != NULL){
    if(check->next == NULL){
        check->next = newNode;
        return;
    } else if(strcmp(check->next->word,newNode->word) < 0){
        check = check->next;
    } else if(strcmp(check->next->word,newNode->word) > 0){
      newNode->next = check->next;
      check->next = newNode;
      return;
    } else if(strcmp(check->next->word,newNode->word) == 0){
      return;
    }
  }
}

int scoreWordMP(char *word){
  struct scoredWordMP *check = scoredMPRoot;
  while(check != NULL){
    if(strcmp(check->word,word) == 0){
      printf("You have already entered %s!\n",word);
      return 0;
    }
    check = check->next;
  }
  if(strlen(word) == 3){
    newscoredWordMP(word);
    return 1;
  }else if(strlen(word) == 4){
    newscoredWordMP(word);
    return 1;
  }else if(strlen(word) == 5){
    newscoredWordMP(word);
    return 2;
  }else if(strlen(word) == 6){
    newscoredWordMP(word);
    return 3;
  }else if(strlen(word) == 7){
    newscoredWordMP(word);
    return 4;
  }else if(strlen(word) >= 8){
    newscoredWordMP(word);
    return 11;
  } else {
    newscoredWordMP(word);
    return 0;
  }
}

int multiplayerAcc(void){
  bool turn = PLAYER_ONE;
  int winner = 0;
  struct foundWord *check;
  scoredMPRoot = scoredWordMPNode();
  char input[MAX_WORD_SIZE];
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
    scanf("%45s", input);
    int c;
    while ((c = fgetc(stdin)) != '\n' && c != EOF);
    if(strcmp(input,"q") == 0){
      break;
    }
    while(1){
      if(strcmp(input,check->storedWord) == 0){
        pointValue = scoreWordMP(input);
        printf("%s found! %s is worth %d points!\n",input,input,pointValue);
        break;
      } else if(strcmp(input,check->storedWord) != 0 && check->next == NULL) {
        printf("Word not found!\n");
        break;
      } else {
        check = check->next;
      }
    }
    if(turn == PLAYER_ONE){
      turn = PLAYER_TWO;
    } else {
      turn = PLAYER_ONE;
    }
  }
  if(pointTotalP1 > pointTotalP2){ //Player 1 wins
    winner = 1;
  } else if (pointTotalP1 < pointTotalP2){ //Player 2 wins
    winner = 2;
  } else {  //It's a tie
    winner = 0;
  }
  return winner;
}
