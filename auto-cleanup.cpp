#include <errno.h>       // for errno
#include <fcntl.h>       // for O_RDONLY
#include <stdio.h>       // for fprintf()
#include <stdlib.h>      // for EXIT_SUCCESS
#include <sys/event.h>   // for kqueue() etc.
#include <unistd.h>      // for close()

#include "cleanup-tools.hpp"

namespace fs = std::filesystem;

int main() {
	std::string dirPath = fs::current_path();
	int kq = kqueue();
	int dirfd = open(dirPath.c_str(), O_RDONLY);

	// map of files in immediate directory
	std::map<std::string, bool> dirManager;
	int oldNumFiles = 0;
	int newNumFiles = 0;
	for(auto& p: fs::directory_iterator(dirPath)) {
		fs::path currPath = p.path();
		std::string currFile = currPath.filename();
		dirManager[currFile] = true;
		oldNumFiles++;
	}

	// map initialised once at the start - may change later
	std::map<std::string, DefaultString> groupings;
	groupings = initMap(".map.txt");
	
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
 		 // camp on kevent() until something interesting happens
		struct kevent change;
		if (kevent(kq, NULL, 0, &change, 1, NULL) == -1) { exit(1); }
		// The signal event has NULL in the user data.  Check for that first.
		if (change.udata == NULL) {
			break;
		} else {
			// udata is non-null, so it's the name of the directory
			for(auto& p: fs::directory_iterator(dirPath)) {
				fs::path currPath = p.path();
				std::string currFile = currPath.filename();
				if (!dirManager[currFile]) {
					// adding to the map and cleaning it up
					dirManager[currFile] = true;
					cleanFile(currPath, currFile, groupings);
					// dirManager is set to true even if it is cleaned up because
					// if user decides to drag it out again, it will not be cleaned
				}
				newNumFiles++;
			}
			if (oldNumFiles >= newNumFiles) {
				// a file has been deleted/moved
				oldNumFiles = newNumFiles;
				for (const auto &pair : dirManager) {
					if (!fs::exists(pair.first)) {
						dirManager[pair.first] = false;
					}
				}
			}
 		}
		newNumFiles = 0;
  }
  close(kq);
  return 0;
}
