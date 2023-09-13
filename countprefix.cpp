/*
 *Authored by: Chris Rook
 *
 */

#include "shared.h"
#include "dictionary.h"
#include "populatetree.h"
#include "readprefix.h"
#include <iostream>
#include <pthread.h>
#include <fstream>
#include <queue>
#include <stdio.h>
#include <string>

/// @brief Countprefix thread's worker method. Method dequeues prefix's searches for them and counts the number of
/// words it is a prefix for.
/// @param arg SHARED_DATA pointer
/// @return NULLd
void *countprefix(void *arg)
{
    SHARED_DATA *data = static_cast<SHARED_DATA *>(arg);
    std::string prefix;  // string var to hold prefix for type casting
    const char *pPrefix; // char pointer for prefix
    int count = 0;
    struct dictTree *root = data->dictRootNode;

    // loop to dequeue the prefixes and write them to output
    while (!data->taskCompleted[COUNT_IN])
    {
        if (data->busyWaiting)
        {
            while (!data->taskCompleted[COUNT_IN])
            {
                if (data->taskCompleted[READ_IN])
                {
                    // countprefix_output.txt file object
                    std::ofstream outputFile("countprefix_output.txt");
                    while (!data->prefixQueue.queue::empty())
                    {

                        prefix = data->prefixQueue.queue::front();

                        pthread_mutex_lock(&data->queue_mutex);
                        data->prefixQueue.queue::pop();
                        pthread_mutex_unlock(&data->queue_mutex);

                        pPrefix = prefix.c_str();

                        if (search(root, pPrefix))
                        {
                            prefixCounter(root, pPrefix, count);
                        }
                        pthread_mutex_lock(&data->progress_mutex);
                        data->numOfProcessedPrefixes++;
                        if (data->busyWaiting)
                        {
                            data->busyWaiting = false;
                        }
                        pthread_mutex_unlock(&data->progress_mutex);

                        if (count >= data->minNumOfWordsWithAPrefixForPrinting)
                        {

                            outputFile << prefix << " " << count << std::endl;
                        }
                        count = 0;
                    }
                    outputFile.close();
                    data->taskCompleted[COUNT_IN] = true;
                }
            }
        }
    }
    pthread_exit(NULL);
}
