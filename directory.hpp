#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cerrno>
#include <filesystem>
#include <fstream>
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
    Directory(std::string path) : mapFile(".map.txt"), saveFile(".save.txt") 
    {
      dirPath = path;
    };

    inline void writeChanges(std::ofstream& txtFile,
        const std::string &targetDir, const std::string &oldName,
        const std::string &newName) {
      txtFile << targetDir << '\n'; 
      txtFile << oldName << '\n';
      txtFile << newName << '\n';
    }

    // maybe don't need to return anything? Void?
    std::map<std::string, DefaultString> initMap(void);

    // manual-only functions
    void move(std::string oldName, std::string targetDir,
        std::ofstream& txtFile);
  
    // auto-only functions
    void autoMove(std::string oldName, std::string targetDir);
    int cleanFile(std::string filePath, std::string fileName,
        std::map<std::string, DefaultString> groupings);
    void updateNumFiles(int newNumFiles);
    void initNumFiles(void);

  private:

    // variables needed for both auto and manual
    int mode; // manual or auto [not yet implemented]
    std::string mapFile;
    std::string dirPath; // path of dir to monitor
    std::map<std::string, DefaultString> groupings;

    // manual-only variables
    std::string saveFile;

    // auto-only variables
    std::map<std::string, bool> dirManager;
    int currNumFiles;

};
