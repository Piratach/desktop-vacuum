/*****************************************************************************
 * cleanuptools.hpp
 * 1. Wrapper class for cleanup functions
 * 2. Initialised by giving it the directory name
 *
 * TODO
 * 1. Directory name error checking
 *****************************************************************************/

#include <errno.h>       // for errno
#include <fcntl.h>       // for O_RDONLY
#include <stdio.h>       // for fprintf()
#include <stdlib.h>      // for EXIT_SUCCESS
#include <sys/event.h>   // for kqueue() etc.
#include <unistd.h>      // for close()

#include "directory.hpp"

class CleanupTools {

  public:

    CleanupTools (std::string dirName);

    int manualCleanup(void);
    int revert(void);
    int autoCleanup(void);

    int initCurrDir(std::string dirName);

  private:
    Directory currDir;
    std::string dirPath;

};
