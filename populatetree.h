/*
*Authored by: Chris Rook
*
*
*/

#ifndef POPULATETREE_H
#define POPULATETREE_H
#define DELIMITER_CHARS "\n\r !\"#$%&()*+,./0123456789:;<=>?@[\\]^`{|}~" //delimiter string

///@brief Method for thread that populates the dictionary tree
void* populatetree(void *);

#endif