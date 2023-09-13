/*
*Authored by: Chris Rook
*
*
*/

#include "shared.h"
#include "dictionary.h"
#include "populatetree.h"
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <string.h>
#include <cstring>
#include <unistd.h>


/// @brief populate tree thread's worker method; Method populates the dictionary tree.
/// @param arg SHARED_DATA pointer
/// @return NULL
void* populatetree(void *arg) { 
    SHARED_DATA *data = static_cast<SHARED_DATA*>(arg);
    const char* file = data->filePath[VOCAB_FILE_IDX];
    std::string textLine;
    struct dictTree *root = data->dictRootNode;
    std::ifstream vocabulary(file); //creates file stream

    if (vocabulary.is_open()) 
    {
        while (vocabulary.good()) 
        {
            getline(vocabulary, textLine);
            char* start = &textLine[0]; 
            char* word = strtok(start, DELIMITER_CHARS);
            while (word != nullptr)
            {
                //insert each word to the dictionary tree
                insert(root, word);
                data->wordCountInFile[VOCAB_FILE_IDX]++;
                word = strtok(NULL, DELIMITER_CHARS);
            }
            data->numOfCharsReadFromFile[VOCAB_FILE_IDX] = data->numOfCharsReadFromFile[VOCAB_FILE_IDX] + textLine.length() + 1;
        }
        vocabulary.close();
        vocabulary.clear();
    }
    pthread_mutex_lock(&data->queue_mutex);
    data->busyWaiting = true;
    pthread_mutex_unlock(&data->queue_mutex);
    pthread_exit(NULL);
} 