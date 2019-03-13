#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/* Converts characters to their ascii values and subtracts the ascii value of 'a'
 * We do this so that the letters 'a' through 'z' will have the values between 0 and 25
*/
#define ASSIGN_CHAR_INDEX(c) ((int)c - (int)'a')

//For consistency so we'll know when we're using
//the size of the alphabet without having to state so
#define ALPHABET (26)
#define MAX_WORD_SIZE (45)

// Trie node
struct TrieNode {
  //There should be a child for each letter of the alphabet
  struct TrieNode *child[ALPHABET];
  //Registers when we're at the end of a word (True = end of word/ False = Not end of word)
  bool isEndOfWord;
};

struct TrieNode *root; //Global variable for root

// Creates new trie node, by default is empty
struct TrieNode *newNode(void) {
  struct TrieNode *node = NULL;                               //Creating node
  node = (struct TrieNode *)malloc(sizeof(struct TrieNode)); //Dynamically allocating node

  if(node) {
    //By default, a node is not at the end of a word.
    node->isEndOfWord = false;
    //By default, node does not have any child nodes.
    for(int i = 0; i < ALPHABET; i++){
      node->child[i] = NULL;
    }
  }
  return node;
}

//A simple function to check to see if a string has non-lowercase or non-alpha characters
bool checkString(const char *word){
  int value; //Index is used to store values of characters
  for(int i = 0; i < strlen(word);i++){
    value = ASSIGN_CHAR_INDEX(word[i]); //Assigning modified ascii values to value
    if(value < 0 || value > ALPHABET){ //If value < 0 (Ascii value <'a') or value > 26 (ascii value > 'z')
       return true;
    }
  }
  //If all letters are lowercase, alpha characters
  return false;
}

// If not present, inserts word into trie
// If the word is prefix of trie node, just marks leaf node
void insert(struct TrieNode *root, const char *word) {

  int depth;                    //depth is used to represent the current level inside the tree
  int wordLength = strlen(word); //wordLength gets size of word currently being checked
  int index;                    //Index is used to see where in the trie a letter goes (Ie: a has an index of 0 so it is child[0])
  struct TrieNode *check = root; //Start word insertion at the root
  if(checkString(word)){ //If words violate lowercase, alpha rules, then word is NOT added to tree
    return;
  }
  for(depth = 0; depth < wordLength; depth++) { //A word must occupy a space in the trie = its length because all characters require a node
    index = ASSIGN_CHAR_INDEX(word[depth]); //Find index to assign letter to
    if(!check->child[index]){ //If the next letter does not exist in the trie as a child of the node
      check->child[index] = newNode(); //Add the letter as a child
    }
    check = check->child[index]; //If the child didn't exist before, it does now. Move to it.
  } //For loop iterates until at the end of the word.
  // mark last node as leaf
  check->isEndOfWord = true;
}

// Checks through trie to see if word exists in it. Returns true if word exists, otherwise false
bool search(struct TrieNode *root, const char *word) {
  int depth;                     //depth is used to represent the current level inside the tree
  int wordLength = strlen(word); //wordLength gets size of word currently being checked
  int index;                     //Index is used to see where in the trie a letter goes (Ie: a has an index of 0 so it is child[0])
  struct TrieNode *check = root; //Begin search at root
  for(depth = 0; depth < wordLength; depth++) { //The deepest we can go searching for a word is its length
    index = ASSIGN_CHAR_INDEX(word[depth]);      //Get index of next character to check for.
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
  root = newNode();

  //str and temp are both strings to store and initialize words.
  //longest word in the english language is 45 characters (pneumonoultramicroscopicsilicovolcanoconiosis)
  char str[MAX_WORD_SIZE];
  char temp[MAX_WORD_SIZE];

  //file will be used to open our wordList
  FILE *file;
  file = fopen("wordList.txt","r");

  //Veryifying that wordList.txt exists
  if(file == NULL){
    printf("Could not open file wordList.txt\n");
    return 1;
  }
  //Begin going through the text file until you reach end of file
  while(fgets(temp,MAX_WORD_SIZE+1,file) != NULL){
    //From line 128 to line 133, we are ensuring that we do not try to add the newline to the trie
    int j = 0;
    while(temp[j+1] != '\n'){
      str[j] = temp[j];
      j++;
    }

    clear(temp); //We empty out the temp string
    insert(root,str); //we add the string to the root
    clear(str); //we empty str
  }
  //The remainder until the return is for testing purposes
  char output[][32] = {"Not present in trie", "Present in trie"};
  // Search for different words
  printf("%s --- %s\n", "axsadad", output[search(root, "axsadad")] );
  printf("%s --- %s\n", "Aaron", output[search(root, "Aaron")] );
  printf("%s --- %s\n", "blast", output[search(root, "blast")] );
  printf("%s --- %s\n", "blasted", output[search(root, "blasted")] );
  printf("%s --- %s\n", "zoos", output[search(root, "zoos")] );

  return 0;
}
