#ifndef PLAYER_VERSUS_COMPUTER_H
#define PLAYER_VERSUS_COMPUTER_H

#define PLAYER_ONE (0)
#define PLAYER_TWO (1)

struct ScoredWordVC{
  char word[45];
  struct ScoredWordVC *next;
};

struct ScoredWordVC *ScoredWordVCNode(void);

struct ScoredWordVC *ScoredVCRoot;

void newScoredWordVC(char *word);

int scoreWordVC(char *word);

int versusComputerAcc(void);

#endif
