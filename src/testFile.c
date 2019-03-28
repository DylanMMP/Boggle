//How to bring in things from other classes?
//How to store found words?

bool checkAdjacent(char *checkWord,int i,int j,int count){
  /*if(Board[i][j] == NULL){
    return false;
  } else */if((Board[i][j].isChecked) = true){
    return false;
  } else if(search(root,checkWord)){
    checkWord[count] = Board[i][j].boardChar;
    printf("%s\n",checkWord);
    return true;
  } else if(count >= 46){
    return false;
  } else {
    Board[i][j].isChecked = true;
    checkWord[count] = Board[i][j].boardChar;
    checkAdjacent(checkWord,i-1,j-1,count+1);
    checkAdjacent(checkWord,i-1,j,count+1);
    checkAdjacent(checkWord,i,j-1,count+1);
    checkAdjacent(checkWord,i-1,j+1,count+1);
    checkAdjacent(checkWord,i+1,j-1,count+1);
    checkAdjacent(checkWord,i+1,j,count+1);
    checkAdjacent(checkWord,i,j+1,count+1);
    checkAdjacent(checkWord,i+1,j+1,count+1);
  }
}

void wordFind(){
  char checkWord[45];
  for(int i = 0; i < 5;i++){
    for(int j = 0; j < 5;j++){
      for(int k = 0; k < 46;k++){
        checkWord[k] = "";
      }
      printf("test\n");
      checkWord[0] = Board[i][j].boardChar;
      Board[i][j].isChecked = true;
      checkAdjacent(checkWord,i-1,j-1,1);
      checkAdjacent(checkWord,i-1,j,1);
      checkAdjacent(checkWord,i,j-1,1);
      checkAdjacent(checkWord,i-1,j+1,1);
      checkAdjacent(checkWord,i+1,j-1,1);
      checkAdjacent(checkWord,i+1,j,1);
      checkAdjacent(checkWord,i,j+1,1);
      checkAdjacent(checkWord,i+1,j+1,1);
    }
  }
}
