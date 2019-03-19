#ifndef COMPUTER_VERSUS_COMPUTER_H
#define COMPUTER_VERSUS_COMPUTER_H

#define PLAYER_ONE (0)
#define PLAYER_TWO (1)

struct ScoredWordCVC{
  char word[45];
  struct ScoredWordCVC *next;
};

struct ScoredWordCVC *ScoredWordCVCNode(void);

struct ScoredWordCVC *ScoredCVCRoot;

void newScoredWordCVC(char *word);
int scoreWordCVC(char *word);

int ComputerVersusComputerAcc(void);

#endif
