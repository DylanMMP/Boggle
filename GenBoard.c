#include <stdio.h>
#include <time.h>
#include <stdlib.h>
void genBoard(void){
  /*There are 96 faces to the dice in boggle
   *To maintain the same liklihood for each letter as in the original game
   *We are using the same weight for each number to appear
  */
  char dice[] = {'E','E','E','E','E','E','E','E','E','E','E',
                'A','A','A','A','A','A',
                'I','I','I','I','I','I',
                'O','O','O','O','O','O','O',
                'L','L','L','L',
                'N','N','N','N','N','N',
                'S','S','S','S','S','S',
                'T','T','T','T','T','T','T','T','T',
                'D','D','D',
                'R','R','R','R','R',
                'U','U','U',
                'B','B',
                'C','C',
                'G','G',
                'H','H','H','H','H',
                'M','M',
                'P','P',
                'Y','Y','Y',
                'F','F',
                'K',
                'V','V',
                'W','W','W',
                'J',
                'Q',
                'X',
                'Z'};

  int width = 0;  //The width of the board
  int height = 0; //the height of the board

  //A print and scan to prompt and retrieve width from user.
  printf("Please input desired width:\n");
  scanf("%d",&width);

  //A print and scan to prompt and retrieve width from user.
  printf("Please input desired height:\n");
  scanf("%d",&height);

  char Board[width][height]; //Creating array to store board

  //Preparing random number generation.
  time_t t;
  srand((unsigned) time(&t));

  int randNum = 0; //randNum will store a random number to replicate dice roll
  //Loop to fill board with psuedo-random letters
  for(int j = 0;j < height; j++){
    for(int k = 0; k < width; k++){
      randNum = rand() % 96; //Generating random number
      Board[j][k] = dice[randNum]; //Placing a randomly selected letter into a spot in the board
    }
  }

  //Outputting board for testing purposes
  for(int j = 0; j < height; j++){
    for(int k = 0; k < width; k++){
      printf("%c",Board[j][k]);
    }
    printf("\n");
  }
  printf("\n");
}
