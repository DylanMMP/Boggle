//This function scans the board to find every word in it.
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "GenBoard.h"
#include "WordList.h"

//We store found words in a linked list
struct foundWord{
  char storedWord[MAX_WORD_SIZE];
  struct foundWord *next;
};

struct foundWord *foundRoot;

int numStored;  //Counts number of unique words

bool isSafe(int i,int j){ //Verifies that index is not out of board and not previously checked.
  return((i >= 0 && i < height) && (j >= 0) && (j < width) && (Board[i][j].isChecked == false));
}

struct foundWord *newFoundWordNode(void) {
  struct foundWord *node = NULL;
  node = (struct foundWord *)malloc(sizeof(struct foundWord));

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
  //If there are no words in the list, we put the first word found in it
  if(check->next == NULL){
    check->next = newNode;
    return;
  }
  //Words found are stored in alphabetical order, not in the order found.
  //This is to help ensure that a word isn't found multiple times.
  while(check != NULL){
    //If we reach the end of the list, we put the word there.
    if(check->next == NULL){
        check->next = newNode;
        return;
    //If the word comes after the stored word alphabetically, we iterate forward.
    } else if(strcmp(check->next->storedWord,newNode->storedWord) < 0){
        check = check->next;
    //If the word is between two letters alphabetically, we put it between them.
    } else if(strcmp(check->next->storedWord,newNode->storedWord) > 0){
      newNode->next = check->next;
      check->next = newNode;
      return;
    //If the word is already in the list, we break out of it.
    } else if(strcmp(check->next->storedWord,newNode->storedWord) == 0){
      free(newNode);
      return;
    }
  }
}

void clearFoundWord(){
  struct foundWord *head = foundRoot;
  struct foundWord *temp = head;
  while(head != NULL){
     temp = head;
     head = head->next;
     free(temp);
  }
}

//Function to recursively scan through board
void scanBoard(int i,int j,int count, char *word){
  //We need to convert words to lower case, since the board has capital letters
  //And the trie stores words in lower case.
  word[count] = tolower(Board[i][j].boardChar);
  Board[i][j].isChecked = true;
  //We see if the word exists in the trie
  if(search(root,word)){
    newFoundWord(word);
  }
  //If the letter combination ISNT in the trie OR we've exceeded the allowed word length
  if((count > 0 && !lettersInTree(root,word)) || (count > MAX_WORD_SIZE)){
    Board[i][j].isChecked = false;
    return;
  }
  //Then we iterate in all eight direction around the index
  //Note that the isSafe function ensures we don't go outside the board and
  //that we don't check the same index twice.
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
  //After we have recursed through, we remove the letter in the word
  word[strlen(word)-1] = '\0';
  //And we mark the index as not checked for future recursions.
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

  //Since any index in the board could be the start of the word, we must
  //check each index as the head at least once.
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
