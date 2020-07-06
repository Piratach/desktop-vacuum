#include <errno.h>       // for errno
#include <fcntl.h>       // for O_RDONLY
#include <stdio.h>       // for fprintf()
#include <stdlib.h>      // for EXIT_SUCCESS
#include <sys/event.h>   // for kqueue() etc.
#include <unistd.h>      // for close()

#include "directory.hpp"

/****************************************************************************
 * TODO: Ask user whether to clean up everything immediately first (run manual)
 *       or to save all files right now into an ignore list
***************************************************************************/

namespace fs = std::filesystem;

int main() {
  std::string dirPath = fs::current_path();

  // kqueue is used to "listen" to new files being added
  int kq = kqueue();
  int dirfd = open(dirPath.c_str(), O_RDONLY);
  int cleaned;

  // initialising Directory object
  Directory currDir(dirPath);

  // initialising map between file extensions and groups
  currDir.initMap();

  // dirManager is used to check status of files in the current directory
  currDir.initDirManager();

  // initialising kevent
  struct kevent direvent;
  EV_SET (&direvent, dirfd, EVFILT_VNODE, EV_ADD | EV_CLEAR | EV_ENABLE, 
     NOTE_WRITE, 0, (void *)dirPath.c_str());

  kevent(kq, &direvent, 1, NULL, 0, NULL);
  kevent(kq, &direvent, 1, NULL, 0, NULL);

  // Register interest in SIGINT with the queue.  The user data
  // is NULL, which is how we'll differentiate between
  // a directory-modification event and a SIGINT-received event.
  struct kevent sigevent;
  EV_SET (&sigevent, SIGINT, EVFILT_SIGNAL, EV_ADD | EV_ENABLE, 0, 0, NULL);
  // kqueue event handling happens after the legacy API, so make
  // sure it doesn eat the signal before the kqueue can see it.
  signal(SIGINT, SIG_IGN);
  // Register the signal event.
  kevent(kq, &sigevent, 1, NULL, 0, NULL);

  while (1) {
    struct kevent change;
    // waits until file within directory has been modified
    if (kevent(kq, NULL, EVFILT_VNODE, &change, 1, NULL) == -1) { exit(1); }
    // The signal event has NULL in the user data.  Check for that first.
    if (change.udata == NULL) {
      break;
    } else {
      // std::cout << "Change!" << std::endl;
      // clean up new files and check status of files
      if (cleaned) cleaned = 0;
      else cleaned = currDir.autoClean();
    }
  }
  close(kq);
  return 0;
}
