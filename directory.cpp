#include "directory.hpp"

void Directory::revert(void) {
	std::ifstream txtFile;
	txtFile.open(saveFile);
	std::string dir, oldName, newName;
	while (std::getline(txtFile, dir)) {
		std::getline(txtFile, oldName);
		std::getline(txtFile, newName);
		std::rename(newName.c_str(), oldName.c_str());
		if (std::filesystem::is_empty(dir)) {
      std::filesystem::remove(dir.c_str());
		}
	}
	txtFile.close();
  std::filesystem::remove(saveFile);
}

void Directory::initMap(void) {
  std::ifstream infile;
  infile.open(mapFile);
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
void Directory::move(std::string oldName, std::string targetDir,
    std::ofstream& txtFile) {
  // targetDir taken from extension
  std::string newName = targetDir + "/" + oldName;
  // check with a tag to avoid computation
  if (std::filesystem::exists(targetDir)) {
    if (std::filesystem::exists(newName)) {
      replaceName(targetDir, oldName, newName, 0);
    }
    std::rename(oldName.c_str(), newName.c_str());
  } else {
    std::filesystem::create_directory(targetDir);
    std::rename(oldName.c_str(), newName.c_str());
    // set tag to true
  }
  writeChanges(txtFile, targetDir, oldName, newName);
}

// auto-only functions
void Directory::move(std::string oldName, std::string targetDir) {
  // targetDir taken from extension
  std::string newName = targetDir + "/" + oldName;
  // check with a tag to avoid computation
  if (std::filesystem::exists(targetDir)) {
    if (std::filesystem::exists(newName)) {
      replaceName(targetDir, oldName, newName, 0);
    }
    std::rename(oldName.c_str(), newName.c_str());
  } else {
    std::filesystem::create_directory(targetDir);
    std::rename(oldName.c_str(), newName.c_str());
    // set tag to true
  }
}

int Directory::cleanFile(std::string filePath, std::string fileName) {
  if (fileName[0] == '.' || std::filesystem::is_directory(filePath)) {
    // ignore hidden files and directories
    return 0;
  } else {
    std::string targetDir = groupings[extension(fileName)].value;
    if (targetDir == "others") {
      // let user decide what to do...
      return 0;   
    }
    move(fileName, targetDir);
  }
  return 1;
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

void Directory::autoClean(void) {
  newNumFiles = 0;
  for(auto& p: std::filesystem::directory_iterator(dirPath)) {
    std::filesystem::path currPath = p.path();
    std::string currFile = currPath.filename();
    if (!fileExists(currFile)) {
      // adding to the map and cleaning it up
      dirManager[currFile] = true;
      if (cleanFile(currPath, currFile)) {
        // since file has now disappeared from directory
        dirManager[currFile] = false;
        break;
      }
    }
    newNumFiles++;
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
