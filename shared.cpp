/*
*Authored by: Chris Rook
*/


#include "shared.h"
#include "dictionary.h"
#include <string>
#include <queue>
#include <pthread.h>
//shared data object
struct SHARED_DATA;

///@brief Makes shared data object with initialized defaults explicitly declared
struct SHARED_DATA makeSharedData(void)
{
    struct SHARED_DATA SharedData;
    SharedData.dictRootNode = makeDictNode();
    SharedData.numOfProgressMarks = DEFAULT_NUMOF_MARKS;
    SharedData.hashmarkInterval = DEFAULT_HASHMARKINTERVAL;
    SharedData.minNumOfWordsWithAPrefixForPrinting = DEFAULT_MINNUM_OFWORDS_WITHAPREFIX;
    SharedData.numOfProcessedPrefixes = 0;
    SharedData.queue_mutex = PTHREAD_MUTEX_INITIALIZER;
    SharedData.progress_mutex = PTHREAD_MUTEX_INITIALIZER;
    SharedData.busyWaiting = false;

    for (int i=0; i<NUMOFFILES;i++){
        SharedData.filePath[i] = "";
        SharedData.totalNumOfCharsInFile[i] = 0;
        SharedData.numOfCharsReadFromFile[i] = 0;
        SharedData.wordCountInFile[i] = 0;
        SharedData.taskCompleted[i] = false;

    }
    return SharedData;
}