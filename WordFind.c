#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "GenBoard.h"
#include "WordList.h"

//TODO: Store found words

int wordsFound;

bool isSafe(int i,int j){
  return((i >= 0 && i < height) && (j >= 0) && (j < width) && (Board[i][j].isChecked == false));
}

void scanBoard(int i,int j,int count, char *word){    //Algorithm to recursively scan through board

  word[count] = tolower(Board[i][j].boardChar);
  Board[i][j].isChecked = true;
  if(search(root,word)){
    printf("%s\n",word);
    wordsFound++;
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
  Board[i][j].isChecked = false;
}

void emptyWord(char *word){
  for(int i = 0; i < MAX_WORD_SIZE;i++){
    word[i] = '\0';
  }
}

void wordFind(){
  char word[MAX_WORD_SIZE];        //Word will store the checked letters
  emptyWord(word);
  wordsFound = 0;
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      scanBoard(i,j,0,word);
      emptyWord(word);
    }
  }
  printf("Found %d words\n",wordsFound);
}
