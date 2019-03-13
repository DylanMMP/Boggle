#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

struct boardNode{                     //Struct for board node
  char boardChar;
  bool isChecked;
};


struct boardNode **Board;             //Global variable to hold board

int width;                            //width of board
int height;                           //height of board

char getRandomChar(void){
  /*There are 96 faces to the dice in boggle
   *To maintain the same liklihood for each letter as in the original game
   *We are using the same weight for each number to appear
  */
  char dice[] = {'E','E','E','E','E','E','E','E','E','E','E',
                'T','T','T','T','T','T','T','T','T',
                'O','O','O','O','O','O','O',
                'A','A','A','A','A','A',
                'I','I','I','I','I','I',
                'N','N','N','N','N','N',
                'S','S','S','S','S','S',
                'H','H','H','H','H',
                'R','R','R','R','R',
                'L','L','L','L',
                'D','D','D',
                'U','U','U',
                'W','W','W',
                'Y','Y','Y',
                'B','B',
                'C','C',
                'G','G',
                'F','F',
                'M','M',
                'P','P',
                'V','V',
                'K',
                'J',
                'Q',
                'X',
                'Z'};
  char randChar;
  int randNum = 0; //randNum will store a random number to replicate dice roll
  randNum = rand() % 96; //Generating random number
  randChar = dice[randNum];   //Using dice array to assign a character psuedorandomly
  return randChar;
}

void genBoard(void){

  //A print and scan to prompt and retrieve width from user.
  printf("Please input desired width:\n");
  scanf("%d",&width);

  //A print and scan to prompt and retrieve width from user.
  printf("Please input desired height:\n");
  scanf("%d",&height);

  //Dynamically allocating array
  Board = malloc(sizeof(struct boardNode *) * height);
  for(int i = 0; i < height; i++){
    Board[i] = malloc(sizeof(struct boardNode) * width);
  }

  //Preparing random number generation.
  time_t t;
  srand((unsigned) time(&t));

  //Loop to fill board with psuedo-random letters
  for(int j = 0;j < height; j++){
    for(int k = 0; k < width; k++){
      Board[j][k].boardChar = getRandomChar(); //Placing a randomly selected letter into a spot in the board
      Board[j][k].isChecked = false;           //Unnessecary but ensuring node is not checked
    }
  }
  //Outputting board for testing purposes
  for(int j = 0; j < height; j++){
    for(int k = 0; k < width; k++){
      printf("%c",Board[j][k].boardChar);
    }
    printf("\n");
  }
  printf("\n");
}
