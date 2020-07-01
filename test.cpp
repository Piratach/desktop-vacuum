#include <errno.h>       // for errno
#include <fcntl.h>       // for O_RDONLY
#include <stdio.h>       // for fprintf()
#include <stdlib.h>      // for EXIT_SUCCESS
#include <string.h>      // for strerror()
#include <sys/event.h>   // for kqueue() etc.
#include <unistd.h>      // for close()

int main (int argc, const char *argv[])
{
   int kq = kqueue ();
   // dir name is in argv[1], NO checks for errors here
   int dirfd = open(argv[1], O_RDONLY);

   struct kevent direvent;
   EV_SET (&direvent, dirfd, EVFILT_VNODE, EV_ADD | EV_CLEAR | EV_ENABLE, 
			 NOTE_WRITE, 0, (void *)argv[1]);

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
        printf ("%s\n", (char*)change.udata);
       }
   }
   close (kq);
   return 0;
}
