#include "cleanuptools.hpp"
#include <SFML/Graphics.hpp>
#include <csignal>
#include <string>

// temp includes
#include <chrono>
#include <thread>
#include "scene.hpp"

/*****************************************************************************
 * expected makefile
 *
 * all: main
 *
 * main: main.o cleanuptools.o directory.o tab.o rectbutton.o
 *****************************************************************************/

namespace fs = std::filesystem;

int main() {
  // Scene Interface/UI; -- maybe copy constructor inits as well
  int pid;
  TabMode mode = MANUAL;
  int AUTOCLEAN = 0;
  int MANUALCLEAN = 0;
  int EVENTPROCESSED = 1; // start off by drawing the base

  Scene interface;
  interface.loadConfig();

  int width = interface.getWidth();
  int height = interface.getHeight();
  sf::Color bgColour = interface.getBgColour();
  
  sf::RenderWindow window(sf::VideoMode(width, height), "Cleanup",
      sf::Style::Titlebar | sf::Style::Close);
  window.setVerticalSyncEnabled(true);

  // ON SECOND THOUGHT: initialise colours through a different function...
  // maybe
  // colour definitions and drawing the UI hopefully initialised in UI
  // font loading and all that...

  // [>* Cleaner *<]

  std::string dirPath = fs::current_path();

  CleanupTools cleaner(dirPath);

  // [> Event-based rendering <]
  while (window.isOpen()) {
    sf::Event event;

    if (MANUALCLEAN) {
      // cleaner.manualCleanup();
      // manualButton.finish();
      MANUALCLEAN = 0;
      EVENTPROCESSED = 1;
    }

    while (window.pollEvent(event)) {

      EVENTPROCESSED = 1;
      float x = sf::Mouse::getPosition(window).x;
      float y = sf::Mouse::getPosition(window).y;
      switch(event.type) {
        case sf::Event::Closed:
          window.close();
          if (AUTOCLEAN) kill(pid, SIGKILL);
          break;

        case sf::Event::LostFocus:
          break;

        case sf::Event::GainedFocus:
          break;

        case sf::Event::MouseButtonPressed:
            
          // // interface.getMode(mode); // checking for mode changes
          // // if mode change -- break? think about this
          // // because process one event at once
          interface.updateAll(x, y);

          // // switch(mode) {

            // // pass x and y into these functions...

            // // case MANUAL:
              // // perform various checks
              // // can only have one event at once so if else if else pls
              // // UI.updateManTab(); // other checks
              // //
              // // else:
              // // if (manualButton.checkPressed(x, y)) {
                // // MANUALCLEAN = 1;
              // // }
              // // break;

            // // case AUTO:
              // // UI.updateAutoTab();
              // // else if (autoButton.checkPressed(x, y)) {
                // // if (!AUTOCLEAN) {
                // // pid = fork();
                // // if (pid == 0) {
                  // // cleaner.autoCleanup();
                  // // exit(0);
                // // }
                // // AUTOCLEAN = 1; // currently autocleaning... 
                // // // make it so you can only change settings during AUTOCLEAN
              // // }
              // // }
              // // break;

            /** Last two cases need to support adding new fields and scrolling
             **/
            // // case GROUPINGS:
              // // UI.updateGroupTab();
              // // break;

            // // case IGNORELIST:
              // // UI.updateIgnoreTab();
              // // break;
          // // }
          break; // end of mousePressed event case

        default:
          break;
      }
    }

    if (EVENTPROCESSED) {

      // // we need a colour initialiser
      interface.getMode(mode);
      window.clear(bgColour);
      interface.redrawAll(window);

      window.display();
      EVENTPROCESSED = 0;
    }
  }

	return 0;
}
