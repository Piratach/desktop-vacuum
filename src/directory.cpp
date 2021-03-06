/****************************************************************************
 * directory.cpp
 * 1. contains the implementation of the Directory class functions
 ****************************************************************************/

#include "directory.hpp"

/**************************** Public Functions *******************************/

// ctor
Directory::Directory(std::string path, std::string res) : 
  mapFileName(res + "/groupings.txt"), 
  ignFileName(res + "/ignoreList.txt"),
  saveFileName(res + "/.save.txt")
{
  dirPath = path;
};

// Reverts changes made by Manual-Cleanup by checking the writes made 
// in res/.save.txt. 
void Directory::revert(void) {

  // in the case that revert has already been used or 
  // manual-cleanup has not been called
  if (!std::filesystem::exists(saveFileName)) {
    std::cout << "Nothing to revert." << std::endl;
    return;
  }

	std::ifstream txtFile;
	txtFile.open(saveFileName);
	std::string dir, oldName, newName;
	while (std::getline(txtFile, dir)) {
		std::getline(txtFile, oldName);
		std::getline(txtFile, newName);
    if (std::rename(newName.c_str(), oldName.c_str())) {
      std::cout << oldName << " could not be found in the directory: ";
      std::cout << dir << "." << std::endl;
    }
		if (std::filesystem::is_empty(dir)) {
      std::filesystem::remove(dir.c_str());
		}
	}
	txtFile.close();
  std::filesystem::remove(saveFileName);
}

// Initialises the target directory map by reading from .map.txt
void Directory::initMap(void) {
  std::ifstream infile;
  infile.open(mapFileName);
  if (!infile) {
    std::cerr << "Error opening " << mapFileName;
    /* TODO: Error handling */
    return;
  }
  std::string key, val;
  groupings.clear();
  while (infile >> key >> val) {
    if (groupings.find(key) == groupings.end()) {
      groupings[key] = DefaultString(val);
    }
  }
  infile.close();
}

void Directory::initIgnLst(void) {
  std::ifstream infile;
  infile.open(ignFileName);
  if (!infile) {
    std::cerr << "Error opening " << ignFileName;
    /* TODO: Error handling */
    return;
  }
  std::string key;
  ignLst.clear();
  while (infile >> key) {
    ignLst[key] = true;
  }
  infile.close();
}

// Returns the target directory of a file type by using a map
std::string Directory::getTargetDir(std::string currPath) {
  return groupings[extension(currPath)].value;
}

// Directory.move will ALWAYS move the file out of immediate directory
// Arguments: name of current file, target directory to move to, current mode
// Returns: 1, if new directory has been created
//          0, otherwise
int Directory::move(std::string oldName, std::string targetDir, int manual) {
  // targetDir taken from extension
  targetDir = dirPath + "/" + targetDir;
  std::string newName = targetDir + "/" + oldName;
  oldName = dirPath + "/" + oldName; // full path name used

  int flag; // return
  std::cout << "Attempting to move..." << std::endl;
  std::cout << oldName << " to " << newName << std::endl;
  // check with a tag to avoid computation
  if (std::filesystem::exists(targetDir)) {
    if (std::filesystem::exists(newName)) {
      replaceName(targetDir, oldName, newName, 0);
    }
    std::rename(oldName.c_str(), newName.c_str());
    flag = 0;
  } else {
    std::filesystem::create_directory(targetDir);
    std::cout << "Created new directory!" << std::endl;
    std::rename(oldName.c_str(), newName.c_str());
    // set tag to false
    flag = 1;
  }
  if (manual) {
    writeChanges(targetDir, oldName, newName);
  }
  return flag;
}

// ignore: checks whether or not to move the file without checking the 
//         corresponding file extension
// returns: 1, if file should be ignored
//          0, otherwise
int Directory::ignore(std::string filePath, std::string fileName, 
    bool checkIgnLst) {
  if (fileName[0] == '.' || std::filesystem::is_directory(filePath)) {
    // include ignore list in the future
    return 1;
  } else if (checkIgnLst && ignLst[fileName]) {
    return 1;
  }
  return 0;
}

/************************ Public SaveFile Functions **************************/
/* (Manual-mode Functions) */

void Directory::openSaveFile(void) {
  saveFile.open(saveFileName, std::ofstream::trunc);
}

void Directory::closeSaveFile(void) {
  saveFile.close();
}

/************************ Public Auto-mode Functions *************************/

// autoClean: performs a check on what change was made to the directory
//            and performs the appropriate action
// returns: 1, if the function has triggered another kevent (moving files)
//          0, otherwise
int Directory::autoClean(bool ignoreOthers, bool checkIgnLst) {
  std::string fileFound = "";
  newNumFiles = 0;
  bool fileIgnored = false;
  std::cout << "curr: " << currNumFiles << std::endl;
  for(auto& p: std::filesystem::directory_iterator(dirPath)) {
    std::filesystem::path currPath = p.path();
    std::string currFile = currPath.filename();
    if (!fileExists(currFile)) {

      // if new file added should be ignored
      if (ignore(currPath, currFile, checkIgnLst)) {
        dirManager[currFile] = true; // add to the ok map
        removalCheck(); // in the case of renamings
        fileIgnored = true;
      }

      // either new file or renaming
      fileFound = currFile;
    }
    newNumFiles++;
  }

  if (fileIgnored) {
    currNumFiles = newNumFiles;
    return 0;
  }

  std::cout << newNumFiles << std::endl;
  
  // we are now casing on number of files to check for renamings
  if (currNumFiles == newNumFiles) {
    // file renamed
    dirManager[fileFound] = true;
    removalCheck(); // remove old name from dirManager
    return 0; // kevent not triggered

  // find a better way to do this :(
  } else if (currNumFiles < newNumFiles) {
    // clean up new file
    dirManager[fileFound] = true;
    int flag = cleanFile(fileFound, ignoreOthers);
    if (flag == -1) { // no move needed
      currNumFiles = newNumFiles;
      return 0;
    // moved
    } else if (flag == 1) { // new dir created
      currNumFiles = newNumFiles;
    }
    dirManager[fileFound] = false;
    return 1; // kevent triggered

  } else { 
    // file removal
    if (fileFound != "") {
      std::cerr << "File " << fileFound << " seems to have been removed";
      std::cerr << " but is not." << std::endl;
      std::exit(EXIT_FAILURE);
    }
    // update dirManager
    removalCheck(); 
    return 0; // kevent not triggered
  }
}

// loops through all the files in the current directory and record their info
void Directory::initDirManager(void) {
  currNumFiles = 0;
  for(auto& p: std::filesystem::directory_iterator(dirPath)) {
    std::filesystem::path currPath = p.path();
    std::string currFile = currPath.filename();
    dirManager[currFile] = true;
    currNumFiles++;
  }
}

/**************************** Private Functions ******************************/

// replaceName: a recursive function that makes sure that files of the same
//              are not overwritten
// returns: nothing, but stores the new filename in newName
void Directory::replaceName(std::string &targetDir, std::string &oldName,
    std::string &newName, int count) {
  newName = targetDir + "/" + std::to_string(count) + "-" + oldName;
  if (std::filesystem::exists(newName)) {
    replaceName(targetDir, oldName, newName, count + 1);
  }
}

/*********************** Private Auto-mode Functions *************************/

// returns: 1, if a new directory has been created (+ move)
//         -1, if no move is needed
//          0, otherwise (move but no new directory)
int Directory::cleanFile(std::string fileName, bool ignoreOthers) {
  std::string targetDir = groupings[extension(fileName)].value;
  if (targetDir == "others" && ignoreOthers) {
    // let user decide what to do...
    return -1;  
  }
  return move(fileName, targetDir);
}

// fileExists: checks if currFile exists in the record
// if a file does not exist, then this means that it is a new file
bool Directory::fileExists(std::string currFile) {
  return dirManager[currFile];
}

// removalCheck: checks for removal and records it
void Directory::removalCheck(void) {
  // a file has been deleted/moved
  if (currNumFiles > newNumFiles) currNumFiles = newNumFiles;
  for (const auto &pair : dirManager) {
    if (!std::filesystem::exists(pair.first)) {
      dirManager[pair.first] = false;
    }
  }
}
