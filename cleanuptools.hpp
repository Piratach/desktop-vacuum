#include "directory.hpp"

class CleanupTools {

  public:

    CleanupTools (std::string dirName) : currDir(dirName) {
      dirPath = dirName;
    };

    int manualCleanup(void);
    int revert(void);
    int autoCleanup(void);

    int initCurrDir(std::string dirName);

  private:
    Directory currDir;
    std::string dirPath;

};
