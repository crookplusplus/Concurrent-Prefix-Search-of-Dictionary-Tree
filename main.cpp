/*
*Authored by: Chris Rook
*
*
*/

#include "shared.h"
#include "dictionary.h"
#include "populatetree.h"
#include "readprefix.h"
#include "countprefix.h"
#include <iostream>
#include <pthread.h>
#include <fstream>
#include <queue>
#include <stdio.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;


/// @brief Method that produces a progress bar for the populate tree thread
/// @param data pointer to the Shared Data object
void progressBarForPopulateTree(struct SHARED_DATA *data) {
int progressGoal = 0; //level for pregress to reach to print mark
double progress = 0.0; //variable that tracks populate tree thread progress

for (int i = 0; i< data->numOfProgressMarks; i++) {

    if (i%data->hashmarkInterval == data->hashmarkInterval - 1)
    {
        std::cout<<HASHMARK;
        std::cout.flush();
    }
    else {
        std::cout<<HYPHEN;
        std::cout.flush();
    }
    progressGoal++;
    //while loop updates progress
    while (progress < ((double)progressGoal/data->numOfProgressMarks))
    {
        progress = (double)data->numOfCharsReadFromFile[VOCAB_FILE_IDX]/(double)data->totalNumOfCharsInFile[VOCAB_FILE_IDX];
    }

}   
    std::cout<<std::endl;
    std::cout<<"There are "<< data->wordCountInFile[VOCAB_FILE_IDX]<<" words in the vocabulary.txt"<<std::endl;
    std::cout.flush();
}


/// @brief Method that produces a progress bar for the countprefix thread
/// @param data pointer to the Shared Data object
void progressBarForCountPrefix(struct SHARED_DATA *data) {
    int progressGoal = 0; //level for pregress to reach to print mark
    double progress = 0.0; //variable that tracks populate tree thread progress
    
    //while loop waits for readprefix to complete before it begins printing
    while (!data->taskCompleted[READ_IN])
    {
        continue;
    }
    

    for (int i = 0; i< data->numOfProgressMarks; i++) {

        if (i%data->hashmarkInterval == data->hashmarkInterval - 1 )
        {
            std::cout<<HASHMARK;
            std::cout.flush();
        }
        else {
            std::cout<<HYPHEN;
            std::cout.flush();
        }
        //loop updates progress
        while (progress < ((double)progressGoal/data->numOfProgressMarks))
        {
            progress = (double)data->numOfProcessedPrefixes/(double)data->wordCountInFile[TEST_FILE_IDX];
            
        }
        progressGoal++;
    }
    std::cout<<std::endl;
    std::cout<<"There are "<< data->wordCountInFile[TEST_FILE_IDX]<<" words in the testfile1.txt"<<std::endl;
    std::cout.flush();
}

int main (int argc, char* argv[])
{
    int option; //command line switch
    int idx = MANDATORYARGS; // general purpose index for parsing main args
    //int idxOptind; //what is this
    int nArg; // value set by -n
    int hArg; // value set by -h
    struct stat sb; // struct to get input file size in bytes (chars)
    struct SHARED_DATA sharedData = makeSharedData(); 

    //loop to process optional args
    while ( (option = getopt(argc, argv, "p:h:n:")) != -1) {

        switch (option) {
        case 'p':
            nArg = atoi(optarg);
            if (nArg<MIN_NUMOF_MARKS) 
            {
                std::cout<< "Number of progress marks must be a number and at least 10";
                ::exit(BADHYPHENARG);
            }
            else if (nArg != DEFAULT_NUMOF_MARKS)
            {
                sharedData.numOfProgressMarks = nArg;
            }
            break;

        case 'h': 
            hArg = atoi(optarg);
            if ((hArg<= 0) || (hArg >DEFAULT_HASHMARKINTERVAL)) 
            {
                std::cout<<"Hash mark interval for progress must be a number, greater than 0, and less than or equal to 10"<<std::endl;
                ::exit(BADHASHARG);
            }
            else if (hArg != DEFAULT_HASHMARKINTERVAL)
            {
                sharedData.hashmarkInterval = hArg;
            }
            break;

        case 'n': 
            nArg = atoi(optarg);
            sharedData.minNumOfWordsWithAPrefixForPrinting = nArg;
            break;
        
        default: 
        std::cout<<"Usage: " << argv[0]<< "[-p N of progress marks]" 
        << " [-h \"#\" every N characters (0<N<=10)]" 
        << " [-n N print prefixes >]"<<std::endl;
        ::exit(BADFLAG);
        }
    }
    
    //statement process the mandatory args
    if (idx < argc) 
    {
        std::string argVocFile = argv[argc-idx];
        const char* pArgVocFile = argVocFile.c_str();
        sharedData.filePath[VOCAB_FILE_IDX] = pArgVocFile;
        std::ifstream vocFile(pArgVocFile);

        //tests if vocabulary.txt file can be opened and if it can be measured for chars
        if (vocFile.is_open()){
            if (stat(sharedData.filePath[VOCAB_FILE_IDX], &sb) == 0) {
                sharedData.totalNumOfCharsInFile[VOCAB_FILE_IDX]=sb.st_size;
            }
            else {
                std::cout<<"Bad system call for <<vocabulary.txt>>."<<std::endl;
                ::exit(BADSYSTEMCALL);
            }
        }

        else if(!vocFile.is_open()){
            std::cout<<"Unable to open <<vocabulary.txt>>."<<std::endl;
            ::exit(BADVOCABFILE);
        }
        vocFile.close();
        vocFile.clear();

        idx--;
        std::string argTestFile;
        const char* pArgTestFile = argTestFile.c_str();
        argTestFile = argv[argc-idx];
        sharedData.filePath[TEST_FILE_IDX] = pArgTestFile;
        std::ifstream testFile(pArgTestFile);

        //tests if testfile1.txt file can be opened and if it can be measured for chars
        if(testFile.is_open()){
            if (stat(sharedData.filePath[TEST_FILE_IDX], &sb) == 0) {
                sharedData.totalNumOfCharsInFile[TEST_FILE_IDX]=sb.st_size;
            }
            else {
                    std::cout<<"Bad system call for <<testfile1.txt>>."<<std::endl;
                    ::exit(BADSYSTEMCALL);
                }
        }
        else if(!testFile.is_open()){
            std::cout<<"Unable to open <<testfile1.txt>>."<<std::endl;
            ::exit(BADTESTFILE);
        }

    }

    pthread_t populateTreeThread;
    pthread_t readPrefixThread;
    pthread_t countPrefixThread;

    //create Threads and check for errors
    if ((pthread_create(&populateTreeThread, NULL, &populatetree, &sharedData)) != NORMALEXIT)
    {
        std::cout<<"Unable to create populateTreeThread"<<std::endl;
        ::exit(BADTHREADCREATE);
    }

    if ((pthread_create(&readPrefixThread, NULL, &readPrefixToQueue, &sharedData) != NORMALEXIT))
    {
        std::cout<<"Unable to create readPrefixThread"<<std::endl;
        ::exit(BADTHREADCREATE);
    }


    if ((pthread_create(&countPrefixThread, NULL, &countprefix, &sharedData)) != NORMALEXIT) 
    {
        std::cout<<"Unable to create countPrefixThread"<<std::endl;
        ::exit(BADTHREADCREATE);
    }

    progressBarForPopulateTree(&sharedData);
    pthread_join(populateTreeThread, NULL);
    pthread_join(readPrefixThread, NULL);
    progressBarForCountPrefix(&sharedData);
    pthread_join(countPrefixThread, NULL);

    

    ::exit(NORMALEXIT);
}