#include "cleanuptools.hpp"

int CleanupTools::initCurrDir(std::string dirName) {
  if (std::filesystem::exists(dirName)) {
    std::cout << "Directory " << dirName;
    std::cout << " could not be found" << std::endl;
    return -1;
  }
  currDir = Directory(dirName);
  return 0;
}

/* for now, sort by file extension */
int CleanupTools::manualCleanup() {

  // manual mode
  const int MANUAL = 1;

  // initialising the map betwen extensions and groups
  currDir.initMap();

  // initialising save file used for reverting
  currDir.openSaveFile();

  // looping through each file in the directory
  for(auto& p: std::filesystem::directory_iterator(dirPath)) {
    std::filesystem::path currPath = p.path();
    std::string currFile = currPath.filename();
    if (currDir.ignore(currPath, currFile)) {
      // ignore hidden files and directories
      continue;
    } else {
      // TIL c++ does not support str switch statements...
      std::string targetDir = currDir.getTargetDir(currPath);
      if (targetDir == "others") continue; // will let user decide what to do
      currDir.move(currFile, targetDir, MANUAL);
    }
  }
  currDir.closeSaveFile();
  return 0;
}

int CleanupTools::revert() {
  currDir.revert();
  return 0;
}
