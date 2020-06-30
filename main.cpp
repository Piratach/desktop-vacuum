#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cerrno>
#include <filesystem>
#include <fstream>

/****************************************************************************
 * TODO: Flag to check if revert has already been used.
 * TODO: Two modes - automatic and manual
 *								 - automatic keeps checking for new changes
 *								 - automatic does NOT run the manual once
 *								 - manual means the programme is called once in a while
 *									 to clean up the directory [DONE]
 * TODO: Include an "ignore" list
 * TODO: Check for screenshots on mac and separate that from the other .png
 * TODO: Default groupings - screenshots, images, videos (.mp4, .mov), 
 *													 audio (.mid, .mp3, .wav etc.)
 * TODO: Custom groups - allows user to define a custom folder with a mix of
 *											 extensions (e.g. .cpp, .py for coding)
 * TODO: A simple interface - must also allow users to rename dir grouping
 *														to something different
 *													- and ask user if want to keep updating that dir or
 *														add new files to a diff default grouping
 * TODO: Maybe also allow recursive option - but probably not
 ****************************************************************************/


/****************************************************************************
 * 0. hash extensions to grouping
 * 1. modularise functions and files [OK]
 * 2. keep track if a dir has already been created or not for efficiency
 * 3. interface
 ****************************************************************************/

namespace fs = std::filesystem;

void writeChanges(std::ofstream& txtFile, std::string targetDir,
		std::string oldName, std::string newName) {
	txtFile << targetDir << '\n'; 
	txtFile << oldName << '\n';
	txtFile << newName << '\n';
}

void move(std::string oldName, std::string targetDir, std::ofstream& txtFile) {
	// targetDir taken from extension
	std::string newName = targetDir + "/" + oldName;
	// check with a tag to avoid computation
	if (fs::exists(targetDir)) {
		std::rename(oldName.c_str(), newName.c_str());
	} else {
		fs::create_directory(targetDir);
		std::rename(oldName.c_str(), newName.c_str());
		// set tag to true
	}
	writeChanges(txtFile, targetDir, oldName, newName);
}

/* for now, sort by file extension */
int main() {
	std::string dirPath = fs::current_path();
	std::ofstream txtFile;
	txtFile.open(".saveState.txt", std::ofstream::trunc);
	for(auto& p: fs::directory_iterator(dirPath)) {
		fs::path currPath = p.path();
		std::string currFile = currPath.filename();
		if (currFile[0] == '.' || fs::is_directory(currPath)) { 
			// ignore hidden files and directories
			// we don't want to mess with those - it's already clean
			continue;
		} else {
			std::string currExt = currPath.extension();
			// TIL c++ does not support str switch statements...
			if (currExt == ".jpg" || currExt == ".jpeg") {
				// hash extension to target directory name...
				// for now, hardcode it as jpg etc.
				move(currFile, "jpg", txtFile);
			} else if (currExt == ".png") {
				move(currFile, "png", txtFile);
			} else if (currExt == ".txt") {
				move(currFile, "txt", txtFile);
			} else if (currExt == ".md") {
				move(currFile, "md", txtFile);
			} else if (currExt == ".pdf") {
				move(currFile, "pdf", txtFile);
			} else {
				// give user option to do nothing or move to others
				// move(currFile, "others");
				continue;
			}
		}
	}
	txtFile.close();
  return 0;
}
