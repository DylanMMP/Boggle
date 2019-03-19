#ifndef WORD_FIND_H
#define WORD_FIND_H

struct foundWord{
  char storedWord[45];
  struct foundWord *next;
};

extern struct foundWord *foundRoot;

extern int numStored;

bool isSafe(int i,int j);

struct foundWord *newFoundWordNode(void);

void newFoundWord(char *word);

void scanBoard(int i,int j,int count, char *word);

void emptyWord(char *word);

void wordFind();

#endif
