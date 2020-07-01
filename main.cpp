#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cerrno>
#include <filesystem>
#include <fstream>
#include <map>

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
 *										 - use a dictionary, and new files are mapped to a 
 *											 certain group
 * TODO: A simple interface - must also allow users to rename dir grouping
 *														to something different
 *													- and ask user if want to keep updating that dir or
 *														add new files to a diff default grouping
 * TODO: Maybe also allow recursive option - but probably not
 ****************************************************************************/


/****************************************************************************
 * -1. BUG FIX!!! Screen Shot 2563.. in desktop is not working...
 * 0. hash extensions to grouping [OK]
 * 0.1. store and load dict efficiently...
 * 1. modularise functions and files [OK]
 * 2. keep track if a dir has already been created or not for efficiency
 * 3. interface
 ****************************************************************************/

namespace fs = std::filesystem;

// not sure if this is the best method possible
// TIL c++ dict does not support definition of default values...
struct DefaultString
{
	DefaultString() : value("others") {}
	DefaultString(std::string s) : value(s) {}
	std::string value;
};

// getting extension while ignoring trailing whitespace
static inline std::string extension(std::string s) {
	int len = 0;
	for (int i = s.size() - 1; i >= 0; i--) {
		if (std::isspace(s[i])) continue;
		else if (s[i] == '.') {
			return s.substr(i, len+1);
		}
		len++;
	}
	return "";
}

static inline void writeChanges(std::ofstream& txtFile,
		const std::string &targetDir, const std::string &oldName,
		const std::string &newName) {
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

	// initialising dict - loading from a .txt file
	std::map<std::string, DefaultString> groupings;
	std::ifstream mapFile;
	mapFile.open(".map.txt");
	std::string key, val;
	while (mapFile >> key >> val) {
		groupings[key] = DefaultString(val);
	}

	std::string dirPath = fs::current_path();
	std::ofstream saveFile;
	saveFile.open(".save.txt", std::ofstream::trunc);
	for(auto& p: fs::directory_iterator(dirPath)) {
		fs::path currPath = p.path();
		std::string currFile = currPath.filename();
		if (currFile[0] == '.' || fs::is_directory(currPath)) {
			// std::cout << currFile << std::endl;
			// ignore hidden files and directories
			// we don't want to mess with those - they're already clean
			continue;
		} else {
			// std::string currExt = currPath.extension();
			// TIL c++ does not support str switch statements...
			std::string targetDir = groupings[extension(currPath)].value;
			if (targetDir == "others") continue; // let user decide what to do...
			move(currFile, targetDir, saveFile);
		}
	}
	saveFile.close();
  return 0;
}
