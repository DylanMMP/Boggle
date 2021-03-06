#ifndef WORD_LIST_H
#define WORD_LIST_H

#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

#define ALPHABET_SIZE (26)
#define MAX_WORD_SIZE (46)

struct TrieNode {
  struct TrieNode *child[ALPHABET_SIZE];
  bool isEndOfWord;
};

extern struct TrieNode *root;

struct TrieNode *newTrieNode(void);

void freeTrie(struct TrieNode *check);

void insert(struct TrieNode *root, const char *key);

bool search(struct TrieNode *root, const char *key);

bool lettersInTree(struct TrieNode *root, const char *key);

char* clear(char* array);

struct TrieNode wordList(void);

#endif
