
#ifndef PLAYER_VERSUS_PLAYER_ACC_H
#define PLAYER_VERSUS_PLAYER_ACC_H


#define PLAYER_ONE (0)
#define PLAYER_TWO (1)

struct scoredWordMP{
  char word[45];
  struct scoredWordMP *next;
};

struct scoredWordMP *scoredWordMPNode(void);

struct scoredWordMP *scoredMPRoot;

void clearScoredWordMP();

void newscoredWordMP(char *word);

int scoreWordMP(char *word);

int multiplayerAcc(void);

#endif
