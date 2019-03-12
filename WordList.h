#ifndef WORD_LIST_H
#define WORD_LIST_H
#define ARRAY_SIZE(array) sizeof(array)/sizeof(array[0])

//For consistency so we'll know when we're using
//the size of the alphabet without having to state so
#define ALPHABET_SIZE (26)

// Need to have words be lower case for check
#define CHAR_TO_INDEX(c) ((int)c - (int)'A')

// Trie node
struct TrieNode {
  //There should be a child for each letter of the alphabet
  struct TrieNode *child[ALPHABET_SIZE];
  //Registers when we're at the end of a word
  bool isEndOfWord;
};

// Returns new trie node (initialized to NULLs)
struct TrieNode *getTrieNode(void);

// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(struct TrieNode *root, const char *key);

// Returns true if key presents in trie, else false
bool search(struct TrieNode *root, const char *key);

char* clear(char* array);

// Driver
struct TrieNode wordList(void);

#endif
