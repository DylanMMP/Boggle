#ifndef MULTIPLAYER_ACC_H
#define MULTIPLAYER_ACC_H


#define PLAYER_ONE (0)
#define PLAYER_TWO (1)

struct scoredWordMP{
  char word[MAX_WORD_SIZE];
  struct scoredWordMP *next;
};

struct scoredWordMP *scoredWordMPNode(void);

struct scoredWordMP *scoredMPRoot;

void newscoredWordMP(char *word);
  while(check != NULL);

int scoreWordMP(char *word);

int multiplayerAcc(void);

#endif
