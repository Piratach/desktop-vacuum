# desktop-vacuum

## Contents  
1. Overview 
2. Functionality 
3. Installation and Usage
4. Repo Structure  
5. Future Updates
6. Credits 

## Overview  
desktop-vacuum is intended to help keep your computer's desktop clean. Its 
functionality allows it to be used for other folders as well. Using user-defined 
groupings, the programme sorts files into their respective groupings based on 
the file's extension.  

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

