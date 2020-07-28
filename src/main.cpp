#include "cleanuptools.hpp"
#include "scene.hpp"
// #include <SFML/Graphics.hpp>
#include "SFML-2.5.1-macos-clang/include/SFML/Graphics.hpp"
#include "SFML-2.5.1-macos-clang/include/SFML/Window.hpp"
#include "whereami/whereami.h"
#include <csignal>
#include <string>

// temp includes
#include <chrono>
#include <thread>

/*****************************************************************************
 *
 *
 *****************************************************************************/

namespace fs = std::filesystem;

int main() {

  int pid;
  TabMode mode = MANUAL;
  int MANUALCLEAN = 0;
  int REVERT = 0;
  int AUTOCLEAN = 0; // activate everytime button pressed
  int EVENTPROCESSED = 1; // start off by drawing the base
  
  int isAutoActive= 0;  

  // desktop-vacuum/src/main.cpp
  // monitor directory that contains desktop-vacuum
  int length = wai_getExecutablePath(NULL, 0, NULL);
  char *path = new char[length + 1];
  wai_getExecutablePath(path, length, NULL);
  path[length] = '\0';
  // std::cout << path << std::endl;
  fs::path buildPath = fs::path(path).parent_path(); // desktop-vacuum/build
  fs::path dirPath = buildPath.parent_path(); // desktop-vacuum
  fs::path resPath = fs::path(dirPath.string() + "/res");
  fs::path monitorPath = dirPath.parent_path();
  // std::cout << dirPath << std::endl;
  // std::cout << monitorPath << std::endl;

  Scene interface;
  interface.loadConfig(monitorPath, resPath);

  int width = interface.getWidth();
  int height = interface.getHeight();
  sf::Color bgColour = interface.getBgColour();
  
  sf::RenderWindow window(sf::VideoMode(width, height), "Cleanup",
      sf::Style::Titlebar | sf::Style::Close);
  window.setVerticalSyncEnabled(true);

  // [>* Cleaner *<]

  CleanupTools cleaner(monitorPath, resPath);

  delete[] path;

  // [> Event-based rendering <]
  while (window.isOpen()) {
    sf::Event event;

    /* Separate loop for performing the cleans */
    if (MANUALCLEAN && !isAutoActive) {
      interface.writeChanges();
      cleaner.manualCleanup();
      // std::this_thread::sleep_for(std::chrono::milliseconds(400));
      interface.finishManualC(MANUALCLEAN);
      EVENTPROCESSED = 1;
    } else if (REVERT && !isAutoActive) {
      cleaner.revert();
      // std::this_thread::sleep_for(std::chrono::milliseconds(400));
      interface.finishRevert(REVERT);
      EVENTPROCESSED = 1;
    } else if (AUTOCLEAN) {
      // needs more AUTOCLEAN checks...this case is different
      // std::this_thread::sleep_for(std::chrono::milliseconds(400));
      if (isAutoActive) {
        // killing running process
        // "toggle"
        kill(pid, SIGKILL);
        interface.finishAutoC(isAutoActive);
      } else {
        // start autoclean process
        interface.writeChanges();
        pid = fork();
        if (pid == 0) {
          cleaner.autoCleanup();
          exit(0);
        }
        isAutoActive = 1;
      }
      AUTOCLEAN = 0;
      EVENTPROCESSED = 1;
    }

    while (window.pollEvent(event)) {

      EVENTPROCESSED = 1;
      float x = sf::Mouse::getPosition(window).x;
      float y = sf::Mouse::getPosition(window).y;

      switch(event.type) {

        case sf::Event::Closed:
          window.close();
          if (isAutoActive) kill(pid, SIGKILL);
          interface.writeChanges();
          break;

        case sf::Event::MouseButtonPressed:
          // passing in x, y coord and flags
          interface.updateAll(x, y, MANUALCLEAN, REVERT, AUTOCLEAN, 
              isAutoActive);
          break; 

        default:
          break;
      }
    }

    if (EVENTPROCESSED) {

      interface.getMode(mode);
      window.clear(bgColour);
      interface.redrawAll(window);

      window.display();
      EVENTPROCESSED = 0;
    }
  }

	return 0;
}
