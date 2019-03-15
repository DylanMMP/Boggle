#ifndef WORD_FIND_H
#define WORD_FIND_H

struct foundWord{
  char storedWord[MAX_WORD_SIZE];
  struct foundWord *next;
};

struct foundWord *foundRoot;

int NumberOfWords;

bool isSafe(int i,int j);

struct foundWord *newFoundWordNode(void);

void newFoundWord(char *word);

void scanBoard(int i,int j,int count, char *word);

void emptyWord(char *word);

void wordFind();

#endif
