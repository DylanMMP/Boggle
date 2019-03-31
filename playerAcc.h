#ifndef PLAYER_ACC_H
#define PLAYER_ACC_H

struct scoredWord{
  char word[45];
  struct scoredWord *next;
};

struct scoredWord *scoredWordNode(void);

struct scoredWord *scoredRoot;

void newScoredWord(char *word);

void clearScoredWord();

int scoreWord(char *word);

int playerAcc(void);

#endif
