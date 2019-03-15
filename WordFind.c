/* TODO: fix bug where words that are detected before other words with the same base word are overwritten
 * The above might not be the issue, but some words aren't being stored.
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "GenBoard.h"
#include "WordList.h"

//TODO: Store found words
struct foundWord{
  char storedWord[MAX_WORD_SIZE];
  struct foundWord *next;
};

struct foundWord *foundRoot;

int numFound;
int numStored;

bool isSafe(int i,int j){
  return((i >= 0 && i < height) && (j >= 0) && (j < width) && (Board[i][j].isChecked == false));
}

struct foundWord *newFoundWordNode(void) {
  struct foundWord *node = NULL;                               //Creating node
  node = (struct foundWord *)malloc(sizeof(struct foundWord)); //Dynamically allocating node

  if(node) {
    strcpy(node->storedWord,"\0");
    node->next = NULL;
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
    numFound++;
  }
  if(count > 0 && !lettersInTree(root,word)){
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
  numFound = 0;

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
