#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cerrno>
#include <filesystem>
#include <fstream>

/****************************************************************************
 * TODO: Two modes - automatic and manual
 *								 - automatic keeps checking for new changes
 *								 - manual means the programme is called once in a while
 *									 to clean up the directory
 * TODO: Include an "ignore" list
 * TODO: Support for mp3, mp4 etc.
 * TODO: Undo cleanup - store save data as a txt file maybe (and then undo
 *											based on the txt file)
 * TODO: Custom groups - allows user to define a custom folder with a mix of
 *											 extensions (e.g. .cpp, .py for coding)
 * TODO: Check for screenshots on mac and separate that from the other .png
 * TODO: A simple interface - must also allow users to rename dir grouping
 *														to something different
 *													- and ask user if want to keep updating that dir or
 *														add new files to a diff default grouping
 * TODO: Maybe also allow recursive option - but probably not
 ****************************************************************************/


/****************************************************************************
 * 1. modularise functions and files
 * 2. implement the actual create dir and move functions
 *		keep track if a dir has already been created or not for efficiency
 * 3. implement and test the actual cleaning up 
 ****************************************************************************/

namespace fs = std::filesystem;

int main() {
	std::string dirPath = fs::current_path();
	std::ifstream txtFile;
	txtFile.open(".saveState.txt");
	std::string dir, oldName, newName;
	while (std::getline(txtFile, dir)) {
		std::getline(txtFile, oldName);
		std::getline(txtFile, newName);
		std::rename(newName.c_str(), oldName.c_str());
		if (fs::is_empty(dir)) {
			fs::remove(dir.c_str());
		}
	}
	txtFile.close();
  return 0;
}
