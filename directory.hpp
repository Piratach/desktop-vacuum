#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <map>

// basically a string that has a default "value" of "others"
struct DefaultString
{
  DefaultString() : value("others") {}
  DefaultString(std::string s) : value(s) {}
  std::string value;
};

// getting extension while ignoring trailing whitespace
inline std::string extension(std::string s) {
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

class Directory {

  public:

    // Directory(int mode)
    Directory(std::string path) : mapFileName(".map.txt"), 
                                  saveFileName(".save.txt") 
    {
      dirPath = path;
    };

    // reverting for manual mode
    void revert(void);

    /** function for both modes **/
    
    // initialises the map using .map.txt
    void initMap(void);
    std::string getTargetDir(std::string currPath);

    /** manual-only functions **/

    // moves file to target directory

    void openSaveFile(void);
    void closeSaveFile(void);
  
    /** auto-only functions **/

    // function overloading!
    void move(std::string oldName, std::string targetDir, int manual=0);

    // does the cleaning
    void autoClean(void);

    // checks and adjust dirManager for removals
    void removalCheck(void);

    // initialises both dirManager and currNumFiles
    void initDirManager(void);

  private:

    // variables needed for both auto and manual
    int mode; // manual or auto [not yet implemented]
    std::string mapFileName;
    std::string dirPath; // path of dir to monitor
    std::map<std::string, DefaultString> groupings;

    // manual-only variables
    std::string saveFileName;
    std::ofstream saveFile;

    // auto-only variables
    std::map<std::string, bool> dirManager;
    int currNumFiles;
    int newNumFiles;

    /** function for both modes **/
    // used when target directory already contains file of the same name
    void replaceName(std::string &targetDir, std::string &oldName,
        std::string &newName, int count);

    /** manual-only function **/
    // write changes to .save.txt
    inline void writeChanges(const std::string &targetDir,
        const std::string &oldName, const std::string &newName) {
      saveFile << targetDir << '\n'; 
      saveFile << oldName << '\n';
      saveFile << newName << '\n';
    }

    /** auto-only function **/

    // checks file before moving
    int cleanFile(std::string filePath, std::string fileName);

    // check if file exists within immediate directory
    bool fileExists(std::string currFile);

};
