#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "WordFind.h"

#define PLAYER_ONE (0)
#define PLAYER_TWO (1)

struct ScoredWordVC{
  char word[45];
  struct ScoredWordVC *next;
};

struct ScoredWordVC *ScoredWordVCNode(void) {
  struct ScoredWordVC *node = NULL;                               //Creating node
  node = (struct ScoredWordVC *)malloc(sizeof(struct ScoredWordVC)); //Dynamically allocating node

  if(node) {
    strcpy(node->word,"\0");
    node->next = NULL;
  }
  return node;
}

struct ScoredWordVC *ScoredVCRoot;

void newScoredWordVC(char *word){
  struct ScoredWordVC *newNode = ScoredWordVCNode();
  struct ScoredWordVC *check = ScoredVCRoot;
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

int scoreWordVC(char *word){
  struct ScoredWordVC *check = ScoredVCRoot;
  while(check != NULL){
    if(strcmp(check->word,word) == 0){
      printf("%s has already been printed!\n",word);
      return -1;
    }
    check = check->next;
  }
  if(strlen(word) == 3){
    newScoredWordVC(word);
    return 1;
  }else if(strlen(word) == 4){
    newScoredWordVC(word);
    return 1;
  }else if(strlen(word) == 5){
    newScoredWordVC(word);
    return 2;
  }else if(strlen(word) == 6){
    newScoredWordVC(word);
    return 3;
  }else if(strlen(word) == 7){
    newScoredWordVC(word);
    return 4;
  }else if(strlen(word) >= 8){
    newScoredWordVC(word);
    return 11;
  } else {
    newScoredWordVC(word);
    return 0;
  }
}

int versusComputerAcc(void){
  bool turn = PLAYER_ONE;
  int winner = 0;
  struct foundWord *check;
  struct foundWord *compCheck;
  time_t t;
  srand((unsigned) time(&t));
  compCheck = foundRoot;
  int randomNum;

  ScoredVCRoot = ScoredWordVCNode();

  char input[45];
  int pointTotalP1 = 0;
  int pointTotalP2 = 0;
  int pointValue = 0;
  printf("Input words (or 'q' to quit)\n");

  while(1){
    check = foundRoot;
    compCheck = foundRoot;
    if(turn == PLAYER_ONE){
      printf("Player Guess: ");
      scanf("%s",input);
      if(strcmp(input,"q") == 0){
        break;
      }
    } else {
      printf("Computer Guess: ");
      randomNum = rand() % 10;
      if(randomNum == 0){
        printf("Computer quits!\n");
        break;
      }
      randomNum = rand() % numStored;
      for(int i = 0; i < randomNum; i++){
        compCheck = compCheck->next;
      }
      for(int i = 0; i < 45; i++){
        input[i] = compCheck->storedWord[i];
      }
    }

    while(1){
      if(strcmp(input,check->storedWord) == 0){
        pointValue = scoreWordVC(input);
        if(pointValue == -1){
          printf("%s was already found or does not exist!\n",input);
          pointValue = 0;
          break;
        }
        printf("%s found! %s is worth %d points!\n",input,input,pointValue);
        break;
      } else if(strcmp(input,check->storedWord) != 0 && check->next == NULL) {
        printf("Word not found!\n");
        break;
      } else {
        check = check->next;
      }
    }
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
    winner = 1;
  } else if (pointTotalP1 < pointTotalP2){ //Player 2 wins
    winner = 2;
  } else {  //It's a tie
    winner = 0;
  }
  return winner;
}
