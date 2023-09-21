# Concurrent-Prefix-Search-of-Dictionary-Tree

&nbsp;&nbsp; This project enhances the functionality of a prior Dictionary Tree project by incorporating multi-threading through POSIX pthreads. It maintains the core functionality of parsing a text file to build a trie data structure containing the words discovered within it. Furthermore, it tackles a distinct text file to search for each word, employing the established trie structure to efficiently count the words for which the searched term acts as a prefix. All of this is achieved through concurrent execution, harnessing the advantages of parallel processing.

## Purpose
&nbsp;&nbsp; The purpose of this project is to demonstrate proficiency in C++ programming, including object-oriented programming, command-line argument parsing, complex data structures, file I/O, pointer manipulation, multithreading, protecting data with mutex locks, and concurrency, all within a Linux environment.

## Development Environment
- **<u>Operating System:</u>** [Ubuntu 20.04.5 LTS on Windows Subsystem for Linux.](https://ubuntu.com/tutorials/install-ubuntu-on-wsl2-on-windows-10#1-overview)
- **<u>IDE: </u>**[Visual Studio Code (VS Code)](https://code.visualstudio.com/download)
- **<u>Compiler:</u>** [g++ (GNU C++ Compiler)](https://gcc.gnu.org/)
- **<u>C++ Standard:</u>** C++11 (extension in VS Code)
- **<u>Build Tool:</u>** GNU Make 4.2.1 (extension in VS Code)

#### **Dependencies:**
- **pthread.h** - used to implement the individual threads, create and use mutex locks for critical section control.
- **unistd.h** - used to parse command line optional arguments
- **sys/types.h** and **sys.stat.h** - used to measure text file size in terms of numbers of chars
- **queue** - data shared between threads are contained in a queue

## Features
 - **<u>Trie Data Structure:</u>** This program implements a Trie (prefix tree) for constructing the dictionary
 - **<u>Pointer Utilization:</u>** The extensive use of pointers in C++ demonstrates memory management and manipulation, illustrating how to work with complex data structures efficiently
 - **<u>File I/O Operations:</u>** - Read Files: Program reads input from two seperate files .txt files for flexibility. - Write Files: Writes a output to a .txt file to evaluate program functionality
 - **<u>Command-Line Argument Parsing:</u>** - The program offers user-friendly command-line interface functionality for building and running the program. Additionally it makes it easy for the user to change the .txt files for the program to use.

- **<u>Multi-Threading:</u>** - The program uses a main thread, a thread to make the dictionary, a thread to read words from a text file to be searched and added to a queue,  and a thread to search the number of prefix occurances for the word popped from the queue. 

- **<u>Mutex Locking for Critical Sections:</u>** Data is shared between the two threads and is protected with the use of a mutext locks that wrap around critical sections.

- **<u>Dynamic Progress Bar:</u>** The program includes a dynamic progress bar within the terminal window, allowing the user to monitor real-time progress. Users can customize the size and update intervals of the progress bar to suit their preferences.

## Getting Started
&nbsp;&nbsp; The program requires a Unix based operating system for the program to execute with the POSIX library for multiple threading and mutex locks.

### Prerequisites

Before you can run this program, make sure you have the following:
- GNU Make 4.2.1 or newer: required to build using the Makefile and make commands
- g++ Compiler: The GNU compiler is used to build and run the program. The compiler must support C++11.

### Installation
**Download the following files into the same folder:**
- 'Makefile': Used for building the program
- 'dictionary.h' and 'dictionary.cpp': Contain implementation for the Trie data structure and its supporting functions.
- 'countprefix.h' and 'countprefix.cpp': Contains the thread function responsible for counting the occurrences of words matching the search term
- 'populatetree.h' and 'populatetree.cpp': Contains the thread function responsible for creating the dictionary tree from the input file.
- 'readprefix.h' and 'readprefix.cpp': Contains the thread function responsible for reading words from an input file and adding them to a queue.
- 'shared.h' and 'shared.cpp': Contains the shared data structures and variables that are manipulated by each of the threads.
- 'main.cpp': Main driver function for the program. Parses command line arguments and creates the multithreaded environment.
- 'testfile1.txt' and 'vocabulary.txt': Sample text files for test the program.
## Usage
This project is built and operated through the command line interface. 
 - Open a terminal window and navigate to the folder that contains the project files. 
 - Run the following command to build the program:
    _make ./countprefx_
- Run the following command to run the program:
    _./countprefix vocabulary.txt testfile1.txt_ and any desired optional arguments; refer to the **Optional Arguments** section below.

    #### <u>**Optional Arguments**</u>
    - **_-p N_**: &nbsp;&nbsp; _N_ is the number of progress marks of the dynamic progress bar. If not specified the default is **50** with **10** has a minimum

    - **_-h N_**: &nbsp;&nbsp; The progress bar prints a '#' every _N_ characters. The default is **10** with an acceptable range from **0** to **10**.

    - **_-n N_**: &nbsp;&nbsp; Prints the word and the number of prefixes found if the number of prefixes is greater than _N_. The default is **1** if not specified. 

## Output

The output of the program can be seen <a href="./countprefix_output.txt">here</a>!