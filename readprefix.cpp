/*
*Authored by: Chris Rook
*
*
*/

#include "shared.h"
#include "dictionary.h"
#include "readprefix.h"
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <string.h>

/// @brief Readprefix thread's worker method. Method read's prefixes from testfile1.txt adds them to a queue and counts the total number 
///of them.
/// @param arg SHARED_DATA pointer
/// @return NULL
void* readPrefixToQueue(void *arg){
    SHARED_DATA *data = static_cast<SHARED_DATA*>(arg);
    const char *file = data->filePath[TEST_FILE_IDX];
    std::string textLine; 
   
    std::ifstream prefixText(file); //creates file stream
    if (prefixText.is_open())
    {
        while(!data->taskCompleted[READ_IN]){

            if (data->busyWaiting)
            {

                while (prefixText.good()) {
                    getline(prefixText, textLine);
                    char* start = &textLine[0];
                    char* word = strtok(start, DELIMITER_CHARS);
                    while(word != nullptr)
                    {
                        // prefix into the queue
                        std::string prefix = word;

                        pthread_mutex_lock(&data->queue_mutex);
                        data->prefixQueue.push(prefix);
                        pthread_mutex_unlock(&data->queue_mutex);

                        data->wordCountInFile[TEST_FILE_IDX]++;
                        
                        word = strtok(NULL, DELIMITER_CHARS);
                    }
                }
                prefixText.close();
                prefixText.clear();

                data->taskCompleted[READ_IN] = true; 

            }
        }
    }
pthread_exit(NULL);
}