#include <iostream>
#include <cstdio>
#include <cstring>
#include <cerrno>

/* for now, sort by file extension */
int main() {
	/* perhaps try to check if dir exists first */
  if(std::rename("test.png", "new/changed.png") < 0) {
		std::string error = strerror(errno);
		std::string dirError = "No such file or directory";
		if (error.compare(dirError) == 0) {
			/* Make a new directory */
			system("mkdir new"); // system call to create new dir
			std::rename("test.png", "new/changed.png");
		}
	}
  return 0;
}
