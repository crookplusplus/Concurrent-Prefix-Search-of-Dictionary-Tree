/*
*Authored by: Chris Rook
*
*/

#include "dictionary.h"
#define BACKSLASH_IDX 26 //index of backslash char
#define HYPHEN_IDX 27 //index of hyphen char
#define UNDERSCORE_IDX 28 //index of underscore char
#define END_OF_WORD 29 // end of word index
#define TOTAL_ACCEPTABLE_CHARS 30 //total number or acceptable chars for words
#define BACKSLASH '\'' //backslash character
#define HYPHEN '-' //hyphen character
#define UNDERSCORE '_' //underscore character



//dictionary node struct
struct dictTree;

/// @brief Makes a child dictionary node and explicitly defines the elements to the nullptr
struct dictTree *makeDictNode(void)
{
    struct dictTree *pDictNode = new dictTree;
    for(int i=0;i<TOTAL_ACCEPTABLE_CHARS;i++)
    {
        pDictNode->children[i] = nullptr;
    }

    return pDictNode;
}


/// @brief Method retrieves end node of the last char of a node (not the null character). This method
/// is used as a helper function
struct dictTree *getDictNode(struct dictTree *root, const char* pChar)
{
    struct dictTree *p = root;
    const char* pCount = pChar;
    int n = 0;
    while (*pCount){
        n++;
        pCount++;
    }
    for (int i=0;i<n;i++)
    {
        int k = tolower(*pChar) - 'a';
        if (*pChar == BACKSLASH){
            k = BACKSLASH_IDX;
        }
        if (*pChar == HYPHEN){
            k = HYPHEN_IDX;
        }
        if (*pChar == UNDERSCORE){
            k = UNDERSCORE_IDX;
        }
        p = p->children[k];
        pChar++;
    }
    return p;
}

/// @brief Method inserts a word into the pointer dictionary tree.
/// @param root is the pointer to the root node of the dictionary
/// @param pChar is the pointer that points to the word to be added into the dictionary tree
void insert(struct dictTree *root, const char* pChar) {
    
    struct dictTree* p = root;
    int n = 0;
    const char* pCount = pChar;

    while (*pCount){
        n++;
        pCount++;
    }
    for (int i=0; i<n;i++){
        int k = tolower(*pChar) - 'a';
        if (*pChar == BACKSLASH){
            k = BACKSLASH_IDX;
        }
        if (*pChar == HYPHEN){
            k = HYPHEN_IDX;
        }
        if (*pChar == UNDERSCORE){
            k = UNDERSCORE_IDX;
        }
        if (p->children[k] == nullptr) 
        {
            p->children[k] = makeDictNode();
        }
        p = p->children[k]; //p is now equal to the char added to the tree
        pChar++;

    }
    p -> children[END_OF_WORD] = makeDictNode(); //creates end of word dictNode
}

/// @brief Method searches the dictionary tree for a word. 
/// @param root is the pointer to the root node of the dictionary
/// @param pChar is the pointer that points to the word that is being searched for.
/// @return returns true if word exists in the tree and false otherwise
bool search(struct dictTree *root, const char* pChar)
{
    struct dictTree *p = root;
    int n = 0;
    const char* pCount = pChar;

    while (*pCount){
        n++;
        pCount++;
    }
    for (int i=0;i<n;i++)
    {
        int k = tolower(*pChar) - 'a';
        if (*pChar == BACKSLASH){
            k = BACKSLASH_IDX;
        }
        if (*pChar == HYPHEN){
            k = HYPHEN_IDX;
        }
        if (*pChar == UNDERSCORE){
            k = UNDERSCORE_IDX;
        }
        if (p->children[k]==nullptr)
        {
            return false;
        }
        p=p-> children[k];
        pChar++;
    }
    //** condition for end of word
    if (p->children[END_OF_WORD]!=nullptr){
        return true;
    }
    return false;
}

/// @brief Method counts the number of times a word is a prefix for other words starting from a dictionary node
/// pointer that is passed to the method. 
/// @param dictNode that points to the last character node so its child nodes can be transversed
/// @param count variable that keeps count of the number of words that the word being searched is a prefix for.
void countWordsStartingFromANode(struct dictTree *dictNode, int &count){
    struct dictTree *pDictNode = dictNode;
    struct dictTree *pTemp;
    
    for (int i=0;i<TOTAL_ACCEPTABLE_CHARS; i++) {
        if ((i==END_OF_WORD) && (pDictNode->children[END_OF_WORD]!=nullptr)){
                count++;
            }
        if (pDictNode->children[i]!=nullptr){
            pTemp = pDictNode->children[i];
            countWordsStartingFromANode(pTemp, count);
        }
    }
}

/// @brief Method combines getDictNode() and countWordsStartingFromANode() methods into one method call. 
/// @param root is the pointer to the root node of the dictionary
/// @param pChar is a pointer for the prefix word
/// @param count variable that counts the number of times the word is a prefix for other words
void prefixCounter(struct dictTree *root, const char* pChar, int &count){
    struct dictTree *pStartNode = getDictNode(root, pChar);
    countWordsStartingFromANode(pStartNode, count);

}