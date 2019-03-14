#ifndef WORD_FIND_H
#define WORD_FIND_H

int wordsFound;
//We need an algorithm to reset checked ones back to isChecked->false

bool isSafe(int i,int j);

void scanBoard(int i,int j,int count, char *word);

void emptyWord(char *word);

void wordFind();

#endif
