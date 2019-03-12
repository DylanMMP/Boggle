#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define ARRAY_SIZE(array) sizeof(array)/sizeof(array[0])

//For consistency so we'll know when we're using
//the size of the alphabet without having to state so
#define ALPHABET_SIZE (26)

// Need to have words be lower case for check
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

// Trie node
struct TrieNode {
  //There should be a child for each letter of the alphabet
  struct TrieNode *child[ALPHABET_SIZE];
  //Registers when we're at the end of a word
  bool isEndOfWord;
};

struct TrieNode *root;

// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void) {
  struct TrieNode *node = NULL;                               //Creating node
  node = (struct TrieNode *)malloc(sizeof(struct TrieNode)); //Dynamically allocating node

  if (node) {
    //By default, a node is not at the end of a word.
    node->isEndOfWord = false;
    //By default, node does not have any child nodes.
    for (int i = 0; i < ALPHABET_SIZE; i++){
      node->child[i] = NULL;
    }
  }
  return node;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(struct TrieNode *root, const char *key) {

  int level;                    //Level is used to represent the current depth
  int wordLength = strlen(key); //wordLength gets size of word currently being checked
  int index;                    //Index is used to see where in the trie a letter goes
  struct TrieNode *check = root;
  for (level = 0; level < wordLength; level++) {
    index = CHAR_TO_INDEX(key[level]);
    if (index < 0 || index > ALPHABET_SIZE){
      return;
    }
    if (!check->child[index]){ //If statement causing segfault
      check->child[index] = getNode();
    }
    check = check->child[index];
  }
  // mark last node as leaf
  check->isEndOfWord = true;
}

// Returns true if key presents in trie, else false
bool search(struct TrieNode *root, const char *key) {
  int level;
  int wordLength = strlen(key);
  int index;
  struct TrieNode *check = root;
  for (level = 0; level < wordLength; level++) {
    index = CHAR_TO_INDEX(key[level]);
    if (index < 0 || index > ALPHABET_SIZE){
      return false;
    }
    if (!check->child[index]){
      return false;
    }
    check = check->child[index];
  }

  return (check != NULL && check->isEndOfWord);
}

char* clear(char* array){
  for(int k = 0; k < 46;k++){
    array[k] = '\0';
  }
  return array;
}

// Driver
int wordList(void) {
  struct TrieNode *root = getNode();
  // Construct trie
  FILE *file;
  char str[46]; //The longest word in the English language is 45 letters long
  char temp[46];
  file = fopen("wordList.txt","r");

  //Veryifying that wordList.txt exists
  if(file == NULL){
    printf("Could not open file wordList.txt\n");
    return 1;
  }

  while(fgets(temp,47,file) != NULL){
    int j = 0;
    while(temp[j+1] != '\n'){
      str[j] = temp[j];
      j++;
    }

    clear(temp);
    insert(root,str);
    clear(str);
  }
  char output[][32] = {"Not present in trie", "Present in trie"};
  // Search for different keys
  printf("%s --- %s\n", "axsadad", output[search(root, "axsadad")] );
  printf("%s --- %s\n", "Aaron", output[search(root, "Aaron")] );
  printf("%s --- %s\n", "blast", output[search(root, "blast")] );
  printf("%s --- %s\n", "blasted", output[search(root, "blasted")] );
  printf("%s --- %s\n", "zoos", output[search(root, "zoos")] );

  return 0;
}
