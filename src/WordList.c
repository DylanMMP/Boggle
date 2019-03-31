//Dylan Marcum-Pollard | dmmarcumpollard@crimson.ua.edu
//This program creates a trie for the program.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/* Converts characters to their ascii values and subtracts the ascii value of 'a'
 * We do this so that the letters 'a' through 'z' will have the values between 0 and 25
 * and anything outside of the 0 to 25 range will not be added to trie
*/
#define ASSIGN_CHAR_INDEX(c) ((int)c - (int)'a')

#define ALPHABET (26)
#define MAX_WORD_SIZE (45)

struct TrieNode {
  struct TrieNode *child[ALPHABET];
  bool isEndOfWord;
};

struct TrieNode *root;

// Creates new trie node, by default is empty
struct TrieNode *newTrieNode(void) {
  struct TrieNode *node = NULL;
  node = (struct TrieNode *)malloc(sizeof(struct TrieNode));

  if(node) {
    node->isEndOfWord = false;
    for(int i = 0; i < ALPHABET; i++){
      node->child[i] = NULL;
    }
  }
  return node;
}

void freeTrie(struct TrieNode *check) {
    for(int i = 0; i < 26; i++) {
        if(check->child[i] != NULL) {
            freeTrie(check->child[i]);
        }
    }
    free(check);
}

//A simple function to check to see if a string has non-lowercase or non-alpha characters
//Returns true if a word violates the rules.
bool checkString(const char *word){
  int value;
  for(int i = 0; i < strlen(word);i++){
    value = ASSIGN_CHAR_INDEX(word[i]); //Assigning modified ascii values to value
    if(value < 0 || value > ALPHABET){ //If value < 0 (Ascii value <'a') or value > 26 (ascii value > 'z')
       return true;
    }
  }
  return false;
}

// If not present, inserts word into trie
// If the word is prefix of trie node, just marks leaf node
void insert(struct TrieNode *root, const char *word) {

  int depth;
  int wordLength = strlen(word);
  int index;
  struct TrieNode *check = root;
  if(checkString(word)){ //If words violate lowercase, alpha rules, then word is NOT added to tree
    return;
  }
  //Since a word can only occupy a number of nodes = its length
  //We only need to iterate a number of times = its length
  for(depth = 0; depth < wordLength; depth++) {
    index = ASSIGN_CHAR_INDEX(word[depth]);
    if(!check->child[index]){ //If the next letter does not exist in the trie as a child of the node
      check->child[index] = newTrieNode(); //Add the letter as a child
    }
    check = check->child[index]; //If the child didn't exist before, it does now. Iterate to it
  }
  // mark last node as end of word
  check->isEndOfWord = true;
}

// Checks through trie to see if word exists in it. Returns true if word exists, otherwise false
bool search(struct TrieNode *root, const char *word) {
  int depth;
  int wordLength = strlen(word);
  int index;
  struct TrieNode *check = root;
  for(depth = 0; depth < wordLength; depth++) { //The deepest we can go searching for a word is its length
    index = ASSIGN_CHAR_INDEX(word[depth]);
    if(index < 0 || index > ALPHABET){ //Nonalpha, nonlowercase character CANNOT exist in trie so it is automatically false
      return false;
    }
    if(!check->child[index]){ //If the next letter doesn't exist in trie, the word doesn't exist in trie
      return false;
    }
    check = check->child[index]; //iterate to next letter
  }
  //If we haven't gone to an invalid location AND the current node is stored as the end of a word
  //then the following line should return true
  return (check != NULL && check->isEndOfWord);
}

//We use lettersInTree to find out if a letter exists in the trie.
bool lettersInTree(struct TrieNode *root, const char *word) {
  int depth;
  int wordLength = strlen(word);
  int index;
  struct TrieNode *check = root;
  for(depth = 0; depth < wordLength; depth++) { //The deepest we can go searching for a word is its length
    index = ASSIGN_CHAR_INDEX(word[depth]);
    if(index < 0 || index > ALPHABET){ //Nonalpha, nonlowercase character CANNOT exist in trie so it is automatically false
      return false;
    }
    if(!check->child[index]){ //If the next letter doesn't exist in trie, the word doesn't exist in trie
      return false;
    }
    check = check->child[index]; //iterate to next letter
  }
  //If we haven't gone to an invalid location AND the current node is stored as the end of a word
  //then the following line should return true
  return (check != NULL);
}

//This is a simple function to reset an array to NULL
char* clear(char* array){
  for(int k = 0; k < MAX_WORD_SIZE;k++){ //
    array[k] = '\0';
  }
  return array;
}

// Function to carry out initialization of trie using text file
int wordList(void) {
  //root requires no values to initialize, since it wont be end of word nor contain any values by default
  root = newTrieNode();

  //str and temp are both strings to store and initialize words.
  //longest word in the english language is 45 characters (pneumonoultramicroscopicsilicovolcanoconiosis)
  char str[MAX_WORD_SIZE];
  char temp[MAX_WORD_SIZE];

  FILE *file;
  file = fopen("wordList.txt","r");

  //Veryifying that wordList.txt exists
  if(file == NULL){
    printf("Could not open file wordList.txt\n");
    return 1;
  }
  //Begin going through the text file until you reach end of file
  while(fgets(temp,MAX_WORD_SIZE+1,file) != NULL){
    //For the next 5 lines we ensure that we don't add newlines to the trie.
    int j = 0;
    while(temp[j+1] != '\n'){
      str[j] = temp[j];
      j++;
    }

    clear(temp);
    insert(root,str);
    clear(str);
  }
  return 0;
}
