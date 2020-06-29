#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cerrno>
#include <filesystem>

/****************************************************************************
 * TODO: Two modes - automatic and manual
 *								 - automatic keeps checking for new changes
 *								 - manual means the programme is called once in a while
 *									 to clean up the directory
 * TODO: Custom groups - allows user to define a custom folder with a mix of
 *											 extensions (e.g. .cpp, .py for coding)
 * TODO: Check for screenshots on mac and separate that from the other .png
 * TODO: A simple interface - must also allow users to rename dir grouping
 *														to something different
 *													- and ask user if want to keep updating that dir or
 *														add new files to a diff default grouping
 * TODO: Maybe also allow recursive option - but probably not
 ****************************************************************************/

namespace fs = std::filesystem;

/* for now, sort by file extension */
int main() {
	std::string dirPath = fs::current_path();
	for(auto& p: fs::directory_iterator(dirPath)) {
		fs::path currPath = p.path();
		std::string currFile = currPath.filename();
		if (currFile[0] == '.' || fs::is_directory(currPath)) { 
			// ignore hidden files and directories
			// we don't want to mess with those - it's already clean
			continue;
		}
		else {
			std::string currExt = currPath.extension();
			// TIL c++ does not support str switch statements...
			if (currExt == ".jpg" || currExt == ".jpeg") {
				std::cout << "jpeg!\n";
			} else if (currExt == ".png") {
				std::cout << "png!\n";
			} else if (currExt == ".txt") {
				std::cout << "text files!\n";
			} else if (currExt == ".md") {
				std::cout << "markdown\n";
			} else {
				std::cout << "others\n";
		}
	}
	/* perhaps try to check if dir exists first */
  // if(std::rename("test.png", "new/changed.png") < 0) {
		// std::string error = strerror(errno);
		// std::string dirError = "No such file or directory";
		// if (error.compare(dirError) == 0) {
			/* Make a new directory */
			// fs::create_directory("new");
			// system("mkdir new"); // system call to create new dir
			// std::rename("test.png", "new/changed.png");
		// }
	// }
  return 0;
}
