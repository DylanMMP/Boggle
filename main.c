#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "WordFind.c"
#include "WordList.h"
#include "GenBoard.h"

int main(void){

  wordList();
  printf("wordlist complete\n");
  printf("\n");
  genBoard();
  printf("genboard complete\n");
  printf("\n");
  wordFind();
  printf("wordfind complete\n");
  printf("\n");

  printf("In main:\n");

  char output[][32] = {"Not present in trie", "Present in trie"};
  // Search for different keys
  printf("%s --- %s\n", "axsadad", output[search(root, "axsadad")] );
  printf("%s --- %s\n", "Aaron", output[search(root, "Aaron")] );
  printf("%s --- %s\n", "blast", output[search(root, "blast")] );
  printf("%s --- %s\n", "blasted", output[search(root, "blasted")] );
  printf("%s --- %s\n", "zoos", output[search(root, "zoos")] );
  printf("%s --- %s\n", "bard's", output[search(root, "bard's")] );

  for(int j = 0; j < height; j++){
    for(int k = 0; k < width; k++){
      printf("%c",Board[j][k].boardChar);
    }
    printf("\n");
  }

 return 0;
}
