/*****************************************************************************
 * cleanuptools.cpp
 * 1. Implementations of the class functions
 *
 *****************************************************************************/

#include "cleanuptools.hpp"

CleanupTools::CleanupTools (std::string dirName, std::string resName) 
  : currDir(dirName, resName) 
{
  dirPath = dirName;
  resPath = resName;
};

/* for now, sort by file extension */
int CleanupTools::manualCleanup() {

  std::cout << "Manual Cleanup" << std::endl;

  // manual mode
  const int MANUAL = 1;

  // initialising the map betwen extensions and groups
  currDir.initMap();

  // initialising ignore list
  currDir.initIgnLst();

  // initialising save file used for reverting
  currDir.openSaveFile();

  bool ignoreOthers = getConfig("manualConfig.xml", "button1");

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
      if (targetDir == "others" && ignoreOthers) {
        continue;
      }
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

/* https://stackoverflow.com/questions/11556545/fsevents-c-example */
int CleanupTools::autoCleanup() {

  std::cout << "Auto-cleanup..." << std::endl;

  // kqueue is used to "listen" to new files being added
  int kq = kqueue();
  int dirfd = open(dirPath.c_str(), O_RDONLY);
  int cleaned = 0;

  // loading configs from xml
  bool ignoreOthers = getConfig("autoConfig.xml", "button1");
  bool useIgnLst = getConfig("autoConfig.xml", "button2");
  bool manualClean = getConfig("autoConfig.xml", "button3");

  // initialising map between file extensions and groups
  currDir.initMap();

  // initialising ignore list
  currDir.initIgnLst();

  // dirManager is used to check status of files in the current directory
  currDir.initDirManager();

  // initialising kevent
  struct kevent direvent;
  EV_SET (&direvent, dirfd, EVFILT_VNODE, EV_ADD | EV_CLEAR | EV_ENABLE, 
     NOTE_WRITE, 0, (void *)dirPath.c_str());

  kevent(kq, &direvent, 1, NULL, 0, NULL);
  kevent(kq, &direvent, 1, NULL, 0, NULL);

  // Register interest in SIGINT with the queue.  The user data
  // is NULL, which is how we'll differentiate between
  // a directory-modification event and a SIGINT-received event.
  struct kevent sigevent;
  EV_SET (&sigevent, SIGINT, EVFILT_SIGNAL, EV_ADD | EV_ENABLE, 0, 0, NULL);
  // kqueue event handling happens after the legacy API, so make
  // sure it doesn eat the signal before the kqueue can see it.
  signal(SIGINT, SIG_IGN);
  // Register the signal event.
  kevent(kq, &sigevent, 1, NULL, 0, NULL);

  /** Depending on the configs, perform one manual clean before listening **/
  if (manualClean) {
    manualCleanup();
  }

  while (1) {
    struct kevent change;
    // waits until file within directory has been modified
    if (kevent(kq, NULL, EVFILT_VNODE, &change, 1, NULL) == -1) { exit(1); }
    // The signal event has NULL in the user data.  Check for that first.
    if (change.udata == NULL) {
      break;
    } else {
      // clean up new files and check status of files
      if (cleaned) cleaned = 0;
      else cleaned = currDir.autoClean(ignoreOthers);
    }
  }
  close(kq);
  return 0;
}

/**************************** Private Functions *******************************/

// Getting info of a button in the tab 
bool CleanupTools::getConfig(std::string fileName, std::string buttonName) {
  bool res;
  tinyxml2::XMLElement *pElement;
  tinyxml2::XMLDocument xmlDoc;
  std::string xmlFilename = resPath + "/" + fileName;

  loadXML(xmlDoc, xmlFilename);
  tinyxml2::XMLNode *pRoot = xmlDoc.FirstChild();
  pElement = pRoot->FirstChildElement(buttonName.c_str());
  pElement->QueryBoolAttribute("pressed", &res);

  return res;
}
