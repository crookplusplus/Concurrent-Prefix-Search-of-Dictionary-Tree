/*
*Authored by: Chris Rook
*
*/
#ifndef SHARED_H
#define SHARED_H


#include "dictionary.h"
#include <queue>
#include <pthread.h>
#include <string>
/**
* Shared constants and data structures among threads
**/
#define VOCAB_FILE_IDX 0 //index of vocabulary file
#define TEST_FILE_IDX 1 //index of test file
#define NUMOFFILES 2
#define READ_IN 0 //index of readprefix bool
#define COUNT_IN 1 //index of count in bool
const char HYPHEN = '-';
const char HASHMARK = '#';
const int BADFLAG  = 10;
const int NORMALEXIT = 0;
const int BADVOCABFILE = 1;
const int BADTESTFILE = 2;
const int BADHYPHENARG = 3;
const int BADHASHARG = 4;
const int BADTHREADCREATE = 6;
const int BADSYSTEMCALL = 7;
const int MANDATORYARGS = 2;

/* default number of progress marks for representing 100% progress */
#define DEFAULT_NUMOF_MARKS 50
/* minimum number of progress marks for representing 100% progress */
#define MIN_NUMOF_MARKS 10
/* place hash marks in the progress bar every N marks */
#define DEFAULT_HASHMARKINTERVAL 10
/* default minimum number of dictionary words starting from a prefix for printing or writing to
the output */
#define DEFAULT_MINNUM_OFWORDS_WITHAPREFIX 1
/* Common data shared between threads */
struct SHARED_DATA
{
/**
* root node of the dictionary tree
*/
struct dictTree *dictRootNode;
/**
* parameters for printing progress bar
*/
int numOfProgressMarks;
int hashmarkInterval;
/**
* print the prefix and its count to the output file only if the
* number of dictionary words starting from the prefix is equal to or
* greater than this number
*/
int minNumOfWordsWithAPrefixForPrinting;
/**
* filePath[0] - file path for the dictionary vocabulary file
* providing words to populate the dictionary tree
* filePath[1] - file path for the test source file providing prefixes
*/
const char *filePath[NUMOFFILES];
/** store total number of characters in files
* totalNumOfCharsInFile[DICTSRCFILEINDEX]
* - number of total chars in the dictionary vocabulary file.
* use stat, lstat, or fstat system call
* totalNumOfCharsInFile[TESTFILEINDEX]
* - number of total chars in the test file, you may NOT need this count
* for this assignment
*
* Hints: see man stat, lstat, or fstat to get the total number of bytes of the file
* stat or lstat uses a filename, whereas fstat requires a file descriptor from a
* low-level I/O call: e.g. open. If you are using high-level I/O, either use stat
* (or lstat), or open the file first with the low-level I/O, then call fstat,
* then close it.)
*
* Important: assume all text files are in Unix text file format, meaning, the end
* of each line only has a line feed character. The stat, lstat, fstat would include the
* count of the line feed character from each line.
*/
long totalNumOfCharsInFile[NUMOFFILES];
/**
* Use numOfCharsProcessedFromFile to track ongoing progress of
* number of characters read in from files and the subsequent thread logic.
*
* This progress indicator is updated by worker threads, and used by the main
* thread to display the progress for tracking the execution of the populatetree thread
*
* File is read in line by line, for each line read in:
* 1) tokenize the line by delimiters to a word array, with each separated word:
* insert the word to the dictionary tree or search, count, and print the word
* in the dictionary tree, and then increment the word count of the file:
* wordCountInFile (see below)
*
* 2) update the numOfCharsReadFromFile by incrementing it by the
* number of characters in the line, plus one to include the line feed
* character at the end of each line of a Unix text file.
*
* numOfCharsReadFromFile[DICTSRCFILEINDEX]
* - number of chars read in and processed from
* the dictionary vocabulary file
* numOfCharsReadFromFile[TESTFILEINDEX]
* - number of chars read in and processed from
* the test file, you may NOT this number for this assignment
*/
long numOfCharsReadFromFile[NUMOFFILES];
/**
* wordCountInFile[DICTSRCFILEINDEX]
* - number of total words in the dictionary vocabulary file.
* wordCountInFile[TESTFILEINDEX]
* - number of total words in the test file
*/
long wordCountInFile[NUMOFFILES];
/**
*INDEX[0] Total number of prefixes that have been read into the queue
*INDEX[1] number of prefixes that have been read from the prefix queue,
* searched and printed ******* UPDATED by readprefix
* this is used for tracking the progress of the countprefix thread
*/
//used by countprefix
long numOfProcessedPrefixes;
/**
* buffer prefixes read from test file
*/
std::queue<std::string> prefixQueue;
/**
* pthread mutex for accessing the prefixQueue
*/
pthread_mutex_t queue_mutex;
pthread_mutex_t progress_mutex;//added to control progress bar print out
/**
* completed flags indicate the completion of the thread logic, one
* for the populatetree thread, one for countprefix thread
* Important: the completed flag of populatetree thread may be
* used to force the precedence constraint that the
* readprefix and countprefix threads have to wait for populatetree
* thread logic to complete before executing their thread logic
*/
bool taskCompleted[NUMOFFILES];
bool busyWaiting; 
};

///@brief Makes shared data object with initialized defaults explicitly declared
struct SHARED_DATA makeSharedData(void);

#endif