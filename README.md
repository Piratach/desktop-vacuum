# desktop-vacuum

## Contents  
1. Overview 
2. Functionality 
3. Installation and Usage
4. Repo Structure  
5. Planned Updates

## Overview  
desktop-vacuum is intended to help keep your computer's desktop clean. Its 
functionality allows it to be used for other folders as well. Using user-defined 
groupings, the programme sorts files into their respective groupings based on 
the file's extension. Currently only works for unix systems. 

## Functionality   
There are two main modes in the programme.  
### Manual Cleanup  
  * Moves files in the immediate directory into their respective folders  
  * Once all the files have been sorted, the programme stops  
  * If unsatisfactory changes were made, the user will be able to "revert" the
  changes  
### Auto Cleanup
  * The programme listens for changes in the background, and automatically 
    moves new files into their respective directory  

## Installation and Usage
The user will have to download a few packages/libraries before being able to 
run the programme.  

  1. Clone this repository and move it to the folder you want to clean up  
  2. Download the required libraries as specified in ext/  
  3. Run "make main". This should create a new folder called build/ and an 
     executable inside.  
  4. To start the programme, run "./build/main"  

## Repo Structure
### ext  
ext contains all the external libraries used to build the programme. All of the 
libraries needed are included in ext/README.md  

### include
include contains the header files necessary for src/main.cpp. This is separated 
out from src/ to add another level of abstraction for users that may want to 
read the code for whatever reason.  

### res
res contains config files and other temporary files maintained by the programme.  

### src
src contains all the other files (including main.cpp), both header files and 
implementation files, but are not included directly in main.cpp.  

## Planned Updates
Here is a short list of things that are planned to be including in the future:
  1. Scrolling for groupings and ignore tab
  2. Update interface for groupings and ignore tab to allow users to enter 
     their own preferences  
  3. Reduce computations done in the background for the interface  

