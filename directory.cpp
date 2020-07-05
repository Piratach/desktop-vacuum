#include "directory.hpp"

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

void Directory::initMap(void) {
  std::ifstream infile;
  infile.open(mapFileName);
  std::string key, val;
  while (infile >> key >> val) {
    groupings[key] = DefaultString(val);
  }
}

std::string Directory::getTargetDir(std::string currPath) {
  return groupings[extension(currPath)].value;
}

void Directory::replaceName(std::string &targetDir, std::string &oldName,
    std::string &newName, int count) {
  newName = targetDir + "/" + std::to_string(count) + "-" + oldName;
  if (std::filesystem::exists(newName)) {
    replaceName(targetDir, oldName, newName, count + 1);
  }
  return;
}

// manual-only functions
// manual is 0 by default
int Directory::move(std::string oldName, std::string targetDir, int manual) {
  // targetDir taken from extension
  std::string newName = targetDir + "/" + oldName;
  // check with a tag to avoid computation
  if (std::filesystem::exists(targetDir)) {
    if (std::filesystem::exists(newName)) {
      replaceName(targetDir, oldName, newName, 0);
    }
    std::rename(oldName.c_str(), newName.c_str());
    return 1;
  } else {
    std::filesystem::create_directory(targetDir);
    std::rename(oldName.c_str(), newName.c_str());
    // set tag to true
    return 0;
  }
  if (manual) writeChanges(targetDir, oldName, newName);
  return 1;
}

int Directory::ignore(std::string filePath, std::string fileName) {
  if (fileName[0] == '.' || std::filesystem::is_directory(filePath)) {
    // include ignore list in the future
    return 1;
  }
  return 0;
}

int Directory::cleanFile(std::string fileName) {
  std::string targetDir = groupings[extension(fileName)].value;
  if (targetDir == "others") {
    // let user decide what to do...
    return 0;   
  }
  return move(fileName, targetDir);
}

void Directory::initDirManager(void) {
  currNumFiles = 0;
  for(auto& p: std::filesystem::directory_iterator(dirPath)) {
    std::filesystem::path currPath = p.path();
    std::string currFile = currPath.filename();
    dirManager[currFile] = true;
    currNumFiles++;
  }
}

bool Directory::fileExists(std::string currFile) {
  return dirManager[currFile];
}

int Directory::autoClean(void) {
  std::string fileFound = "";
  newNumFiles = 0;
  for(auto& p: std::filesystem::directory_iterator(dirPath)) {
    std::filesystem::path currPath = p.path();
    std::string currFile = currPath.filename();
    if (!fileExists(currFile)) {
      if (ignore(currPath, currFile)) {
        dirManager[currFile] = true;
        return 0;
      }
      // file is at least not in current map and is not dir or hidden file
      // (or in ignore list...)
      fileFound = currFile;
    }
    newNumFiles++;
  }

  // ASSERT: (file not in map) && (file not in ignore list)
  //      || (fileFound == "")
  
  // we are now casing on number of files to check for renamings
  if (currNumFiles == newNumFiles) {
    // file renamed
    dirManager[fileFound] = true;
    removalCheck(); // remove old name from dirManager
    return 0;
  } else if (currNumFiles < newNumFiles) {
    // this is a new file -> clean it up
    dirManager[fileFound] = true;
    // line below could be false if "others" dir
    if (cleanFile(fileFound)) dirManager[fileFound] = false;
    else currNumFiles = newNumFiles;
    return 1;
  } else {
    // currNumFiles > newNumFiles case
    // a file has been removed
    // update dirManager
    if (fileFound != "") {
      std::cerr << "File " << fileFound << " seems to have been removed";
      std::cerr << " but is not." << std::endl;
      std::exit(EXIT_FAILURE);
    }
    removalCheck(); 
    return 0;
  }
}

void Directory::removalCheck(void) {
  if (currNumFiles >= newNumFiles) {
    // a file has been deleted/moved
    currNumFiles = newNumFiles;
    for (const auto &pair : dirManager) {
      if (!std::filesystem::exists(pair.first)) {
        dirManager[pair.first] = false;
      }
    }
  }
}

void Directory::openSaveFile(void) {
  saveFile.open(saveFileName, std::ofstream::trunc);
}

void Directory::closeSaveFile(void) {
  saveFile.close();
}
