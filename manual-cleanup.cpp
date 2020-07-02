#include "cleanup-tools.hpp"
/****************************************************************************
 * TODO: Make a directory class (with move, initMap etc.).
 * TODO: Flag to check if revert has already been used. 
 * TODO: Two modes - automatic and manual [DONE]
 *                 - automatic keeps checking for new changes [DONE]
 *                 - automatic does NOT run the manual once [DONE]
 *                 - manual means the programme is called once in a while
 *                   to clean up the directory [DONE]
 * TODO: Include an "ignore" list
 * TODO: Check for screenshots on mac and separate that from the other .png
 * TODO: Default groupings - screenshots, images, videos (.mp4, .mov), 
 *                           audio (.mid, .mp3, .wav etc.)
 * TODO: Custom groups - allows user to define a custom folder with a mix of
 *                       extensions (e.g. .cpp, .py for coding)
 *                     - use a dictionary, and new files are mapped to a 
 *                       certain group
 * TODO: A simple interface - must also allow users to rename dir grouping
 *                            to something different
 *                          - and ask user if want to keep updating that dir or
 *                            add new files to a diff default grouping
 * TODO: Maybe also allow recursive option - but probably not
 ****************************************************************************/


/****************************************************************************
 * -1. BUG FIX!!! Screen Shot 2563.. in desktop is not working... [OK]
 * 0. hash extensions to grouping [OK]
 * 0.1. store and load dict efficiently...[OK]
 * 1. modularise functions and files [OK]
 * 2. keep track if a dir has already been created or not for efficiency
 * 3. interface
 ****************************************************************************/

namespace fs = std::filesystem;

/* for now, sort by file extension */
int main() {

  // initialising dict - loading from a .txt file
  std::map<std::string, DefaultString> groupings;
  groupings = initMap(".map.txt");

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
