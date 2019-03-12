#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include "GenBoard.c"
#include "WordFind.c"
#include "WordList.h"
#include "GenBoard.h"

int main(void){
  extern struct boardNode **Board;
  extern struct TrieNode *root;
  extern int height;
  extern int width;
  wordList();
  printf("\n");
  genBoard();
  printf("\n");
  wordFind();
  printf("\n");

  printf("In main:\n");

  char output[][32] = {"Not present in trie", "Present in trie"};
  // Search for different keys
  printf("%s --- %s\n", "axsadad", output[search(root, "axsadad")] );
  printf("%s --- %s\n", "Aaron", output[search(root, "Aaron")] );
  printf("%s --- %s\n", "blast", output[search(root, "blast")] );
  printf("%s --- %s\n", "blasted", output[search(root, "blasted")] );
  printf("%s --- %s\n", "zoos", output[search(root, "zoos")] );

  for(int j = 0; j < height; j++){
    for(int k = 0; k < width; k++){
      printf("%c",Board[j][k].boardChar);
    }
    printf("\n");
  }

 return 0;
}
