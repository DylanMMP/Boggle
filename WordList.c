#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

//For consistency so we'll know when we're using
//the size of the alphabet without having to state so
#define ALPHABET_SIZE (26)

// Need to have words be lower case for check
#define CHAR_TO_INDEX(c) ((int)c - (int)'A')

// Trie node
struct TrieNode {
    //There should be a child for each letter of the alphabet
    struct TrieNode *children[ALPHABET_SIZE];
    //Registers when we're at the end of a word
    bool isEndOfWord;
};

// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void) {
    struct TrieNode *node = NULL;

    node = (struct TrieNode *)malloc(sizeof(struct TrieNode));

    if (node) {
        node->isEndOfWord = false;

        for (int i = 0; i < ALPHABET_SIZE; i++)
            node->children[i] = NULL;
    }
    return node;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(struct TrieNode *root, const char *key) {
    int level;
    int length = strlen(key);
    int index;

    struct TrieNode *check = root;

    for (level = 0; level < length; level++) {
        index = CHAR_TO_INDEX(key[level]);

      if (!check->children[index]){ //If statement causing segfault
            check->children[index] = getNode();
        }
        check = check->children[index];
    }

    // mark last node as leaf
    check->isEndOfWord = true;
}

// Returns true if key presents in trie, else false
bool search(struct TrieNode *root, const char *key) {
    int level;
    int length = strlen(key);
    int index;
    struct TrieNode *check = root;
    for (level = 0; level < length; level++) {
        index = CHAR_TO_INDEX(key[level]);

        if (!check->children[index])
            return false;

        check = check->children[index];
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
void wordList(void) {
    struct TrieNode *root = getNode();
    // Construct trie
    FILE *fp;
    char str[46]; //The longest word in the English language is 45 letters long
    char temp[46];
    fp = fopen("wordList.txt","r");

    //Veryifying that wordList.txt exists
    if(fp == NULL){
      printf("Could not open file wordList.txt\n");
      return 1;
    }
    printf("test\n");
    //Segfault in while loop
    while(fgets(temp,47,fp) != NULL){
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
    printf("%s --- %s\n", "AXSADADS", output[search(root, "AXSADADS")] );
    printf("%s --- %s\n", "AA", output[search(root, "AA")] );
    printf("%s --- %s\n", "AAS", output[search(root, "AAHS")] );
    printf("%s --- %s\n", "UNKET", output[search(root, "UNKET")] );

    return 0;
}
