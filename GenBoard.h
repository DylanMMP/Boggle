#include <stdbool.h>
#ifndef GENERATE_BOARD_H
#define GENERATE_BOARD_H

extern struct boardNode{
  char boardChar;
  bool isChecked;
} boardNode;

struct boardNode **Board;

char getRandomChar(void);


struct boardNode *getBoardNode(void);

struct boardNode **genBoard(void);

#endif
