#include <stdbool.h>
#ifndef GENERATE_BOARD_H
#define GENERATE_BOARD_H

extern struct boardNode{
  char boardChar;
  bool isChecked;
} boardNode;

extern struct boardNode **Board;
extern int height;
extern int width;

char getRandomChar(void);

struct boardNode **genBoard(void);

#endif
