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
#include "xmlhelper.hpp"

/* CleanupTools processes all the different cleanup functions and revert
 * functions. It will be connected with the interface (Scene) within main.cpp.
 */
class CleanupTools {

  public:

    /* dirName - absolute path to the directory that is to be monitored.
     * resName - absolute path to the resource directory ("/res/") */
    CleanupTools (std::string dirName, std::string resName);

    /* Performs a manual cleanup of the directory that is to be monitored. 
     * Returns: 0, upon completion.
     *          -1, if an error has been encountered. */
    int manualCleanup(void);

    /* Reverts the previous manual cleanup of the directory. Nothing happens if 
     * manual cleanup was not called. 
     * Returns: 0, upon completion.
     *          -1, if an error has been encountered. */
    int revert(void);

    /* Begins auto-cleaning new files. Listens to changes in the directory and 
     * performs cleaning accordingly.
     * Returns: 0, upon completion.
     *          -1, if an error has been encountered. */
    int autoCleanup(void);

  private:
    Directory currDir;
    std::string dirPath, resPath;

    bool getConfig(std::string filename, std::string buttonName);

};
