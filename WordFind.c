#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "GenBoard.h"
#include "WordList.h"

struct foundWord{ //Struct used to store found words
  char storedWord[MAX_WORD_SIZE];
  struct foundWord *next;
};

struct foundWord *foundRoot; //root of found words linked list

int numStored;  //Counts number of unique words

bool isSafe(int i,int j){ //Verifies that index is not out of board and not previously checked.
  return((i >= 0 && i < height) && (j >= 0) && (j < width) && (Board[i][j].isChecked == false));
}

struct foundWord *newFoundWordNode(void) {                      //Creates node for new found word
  struct foundWord *node = NULL;                               //Creating node
  node = (struct foundWord *)malloc(sizeof(struct foundWord)); //Dynamically allocating node

  if(node) {
    strcpy(node->storedWord,"\0");    //By default, a node is empty with no stored word
    node->next = NULL;                //By default, a node does not point towards anything
  }
  return node;
}

void newFoundWord(char *word){
  struct foundWord *newNode = newFoundWordNode();
  struct foundWord *check = foundRoot;
  strcpy(newNode->storedWord,word);
  if(check->next == NULL){
    check->next = newNode;
    return;
  }
  while(check != NULL){
    if(check->next == NULL){
        check->next = newNode;
        return;
    } else if(strcmp(check->next->storedWord,newNode->storedWord) < 0){
        check = check->next;
    } else if(strcmp(check->next->storedWord,newNode->storedWord) > 0){
      newNode->next = check->next;
      check->next = newNode;
      return;
    } else if(strcmp(check->next->storedWord,newNode->storedWord) == 0){
      return;
    }
  }
}

void scanBoard(int i,int j,int count, char *word){    //Algorithm to recursively scan through board

  word[count] = tolower(Board[i][j].boardChar);
  Board[i][j].isChecked = true;
  if(search(root,word)){
    newFoundWord(word);
  }
  if((count > 0 && !lettersInTree(root,word)) || (count > 45)){
    Board[i][j].isChecked = false;
    return;
  }

  if(isSafe(i+1,j)){
    scanBoard(i+1,j,count+1,word);
  }
  if(isSafe(i+1,j+1)){
    scanBoard(i+1,j+1,count+1,word);
  }
  if(isSafe(i,j+1)){
    scanBoard(i,j+1,count+1,word);
  }
  if(isSafe(i-1,j+1)){
      scanBoard(i-1,j+1,count+1,word);
  }
  if(isSafe(i-1,j)){
    scanBoard(i-1,j,count+1,word);
  }
  if(isSafe(i-1,j-1)){
    scanBoard(i-1,j-1,count+1,word);
  }
  if(isSafe(i,j-1)){
    scanBoard(i,j-1,count+1,word);
  }
  if(isSafe(i+1,j-1)){
    scanBoard(i+1,j-1,count+1,word);
  }
  word[strlen(word)-1] = '\0';
  Board[i][j].isChecked = false;
}

void emptyWord(char *word){
  for(int i = 0; i < MAX_WORD_SIZE;i++){
    word[i] = '\0';
  }
}

void wordFind(){

  foundRoot = newFoundWordNode();
  char word[MAX_WORD_SIZE];        //Word will store the checked letters
  emptyWord(word);

  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      scanBoard(i,j,0,word);
      emptyWord(word);
    }
  }

  struct foundWord *check = foundRoot;
  numStored = 0;
  while(check != NULL){
    check = check->next;
    numStored++;
  }
  printf("Found %d unique words\n",numStored);
}
