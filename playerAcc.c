#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "WordFind.h"

struct scoredWord{
  char word[MAX_WORD_SIZE];
  struct scoredWord *next;
};

struct scoredWord *scoredWordNode(void) {
  struct scoredWord *node = NULL;                               //Creating node
  node = (struct scoredWord *)malloc(sizeof(struct scoredWord)); //Dynamically allocating node

  if(node) {
    strcpy(node->word,"\0");
    node->next = NULL;
  }
  return node;
}

struct scoredWord *scoredRoot;

void newScoredWord(char *word){
  struct scoredWord *newNode = scoredWordNode();
  struct scoredWord *check = scoredRoot;
  strcpy(newNode->word,word);
  if(check->next == NULL){
    printf("test\n");
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

int scoreWord(char *word){
  struct scoredWord *check = scoredRoot;
  while(check != NULL){
    if(strcmp(check->word,word) == 0){
      printf("You have already entered %s!\n",word);
      return 0;
    }
    check = check->next;
  }
  if(strlen(word) == 3){
    newScoredWord(word);
    return 1;
  }else if(strlen(word) == 4){
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

int playerAcc(void){
  struct foundWord *check;
  scoredRoot = scoredWordNode();
  char input[MAX_WORD_SIZE];
  int pointTotal = 0;
  int pointValue = 0;
  printf("Input words (or 'q' to quit)\n");
  while(1){
    check = foundRoot;
    printf("Guess: ");
    scanf("%s",input);
    if(strcmp(input,"q") == 0){
      break;
    }
    while(1){
      if(strcmp(input,check->storedWord) == 0){
        pointValue = scoreWord(input);
        pointTotal += pointValue;
        printf("%s found! %s is worth %d points!\n",input,input,pointValue);
        break;
      } else if(strcmp(input,check->storedWord) != 0 && check->next == NULL) {
        printf("Word not found!\n");
        break;
      } else {
        check = check->next;
      }
    }
  }
  return pointTotal;
}
