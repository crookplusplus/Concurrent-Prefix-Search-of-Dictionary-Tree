/*
*Authored by: Chris Rook
*/

#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <iostream>
#define NCHILD 30 //number of valid characters
#define END_OF_WORD 29

/// @brief Struct of a dictionary node with just an array of pointers for child  dictionary nodes
struct dictTree
{
    struct dictTree *children[NCHILD];
};

/// @brief creates dictionary nodes
struct dictTree *makeDictNode(void);

/// @brief Method retrieves end node of the last char of a node (not the null character). This method
/// is used as a helper function
struct dictTree *getDictNode(struct dictTree , const char*);

/// @brief Method inserts a word into the pointer dictionary tree. 
/// @param  dictTree* is the pointer to the root node of the dictionary
/// @param  const char* is the pointer that points to the word to be added into the dictionary tree
void insert(struct dictTree* , const char*);

/// @brief Method searches the dictionary tree for a word. 
/// @param  dictTree* is the pointer to the root node of the dictionary
/// @param  const char* is the pointer that points to the word that is being searched for.
/// @return returns true if word exists in the tree and false otherwise
bool search(struct dictTree*, const char*);

/// @brief Method counts the number of times a word is a prefix for other words starting from a dictionary node
/// pointer that is passed to the method. 
/// @param  dictTree* that points to the last character node so its child nodes can be transversed
/// @param  int& variable that keeps count of the number of words that the word being searched is a prefix for.
void countWordsStartingFromANode(struct dictTree*, int&);

/// @brief Method combines getDictNode() and countWordsStartingFromANode() methods into one method call. 
/// @param  dictTree* is the pointer to the root node of the dictionary
/// @param  const char* is a pointer for the prefix word
/// @param  int& variable that counts the number of times the word is a prefix for other words
void prefixCounter(struct dictTree*, const char*, int&);

#endif