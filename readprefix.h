/*
*Authored by: Chris Rook
*
*/

#ifndef READPREFIX_H
#define READPREFIX_H
#define DELIMITER_CHARS "\n\r !\"#$%&()*+,./0123456789:;<=>?@[\\]^`{|}~" //delimiter string
#define TEST_FILE_IDX 1 //index of test text file that contains the prefixes to be read in

///@brief Method that reads prefixes from testfile1.txt and pushes them to a queue
void* readPrefixToQueue(void *);


#endif