#include "directory.hpp"

namespace fs = std::filesystem;

/* for now, sort by file extension */
int main() {

  // manual mode
  const int MANUAL = 1;

  // initialising directory class
  std::string dirPath = fs::current_path();
  Directory currDir(dirPath);

  // initialising the map betwen extensions and groups
  currDir.initMap();

  // initialising save file used for reverting
  currDir.openSaveFile();

  // looping through each file in the directory
  for(auto& p: fs::directory_iterator(dirPath)) {
    fs::path currPath = p.path();
    std::string currFile = currPath.filename();
    if (currFile[0] == '.' || fs::is_directory(currPath)) {
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
