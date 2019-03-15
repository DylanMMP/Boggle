#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "WordFind.h"

int scoreWord(char *word){
  if(strlen(word) == 3){
    return 1;
  }else if(strlen(word) == 4){
    return 1;
  }else if(strlen(word) == 5){
    return 2;
  }else if(strlen(word) == 6){
    return 3;
  }else if(strlen(word) == 7){
    return 4;
  }else if(strlen(word) >= 8){
    return 11;
  } else {
    return 0;
  }
}

int playerAcc(void){
  struct foundWord *check;
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
        printf("%s found! Word %d points!\n",input,pointValue);
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
