/****************************************************************************
 * directory.hpp
 * 1. header file for the Directory class
 * 2. contains a few other functions used in the cleanup files
 * 3. defines the DefaultString struct
 ****************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <map>

// String with a default value of "others"
struct DefaultString
{
  DefaultString() : value("others") {}
  DefaultString(std::string s) : value(s) {}
  std::string value;
};

// Gets the extension (.jpg) whilst ignoring the trailing whitespaces
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

    /** Constructor for Directory Class **/
    Directory(std::string path) : mapFileName(".map.txt"), 
                                  saveFileName(".save.txt") 
    {
      dirPath = path;
    };

    /** Revert Mode for Manual-Cleanup **/
    void revert(void);

    /** Functions used for Both Modes **/
    void initMap(void); 
    std::string getTargetDir(std::string currPath);
    int move(std::string oldName, std::string targetDir, int manual=0);
    int ignore(std::string filePath, std::string fileName);

    /** Manual-only Functions **
     *  Writes to a save file that is used in revert */
    void openSaveFile(void);
    void closeSaveFile(void);
 
    /** Auto-only functions **/
    int autoClean(void);
    void initDirManager(void);

  private:

    /** Variables used in both modes **/
    int mode; // manual or auto [not yet implemented]
    std::string mapFileName;
    std::string dirPath; // path of dir to monitor
    std::map<std::string, DefaultString> groupings;

    // used when target directory already contains file of the same name
    void replaceName(std::string &targetDir, std::string &oldName,
        std::string &newName, int count);

    /** Manual-only variables **/
    std::string saveFileName;
    std::ofstream saveFile;

    // write changes to .save.txt
    inline void writeChanges(const std::string &targetDir,
        const std::string &oldName, const std::string &newName) {
      saveFile << targetDir << '\n'; 
      saveFile << oldName << '\n';
      saveFile << newName << '\n';
    }

    /** Auto-only variables **/
    std::map<std::string, bool> dirManager;
    int currNumFiles;
    int newNumFiles;

    int cleanFile(std::string fileName);

    // check if file existed within immediate directory
    bool fileExists(std::string currFile);

    // checks and adjust dirManager for removals
    void removalCheck(void);

};
