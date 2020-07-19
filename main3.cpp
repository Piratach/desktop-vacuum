/*****************************************************************************
 * 1. Build a basic interface using SFML
 * 2. "Ignore" list
 * 3. Keep track if a dir has already been created or not for efficiency
 * 4. Wrap it up as an "app" available for download
 *****************************************************************************/

/*****************************************************************************
 * Interface (look at sfml-practice for reference)
 * TODO: Look into .yaml, .xml, .json for storing configs/settings values
 * TODO: Reading user's input for directory to clean
 * TODO: Reading user's input for groupings + allow users to scroll if list
 *       gets long...
 * TODO: Auto, manual/revert button
 * TODO: Settings - with the ability to define groupings
 *                  (e.g. audio - .mid, .mp3, .wav)
 *                - add extensions
 *                - what to do with "others" (ignore/add to "others' folder)
 * TODO: Display relevant error messages!
 *****************************************************************************/

	// sf::RectangleShape rectangle1(sf::Vector2f(100.f, 100.f));
	// rectangle1.setFillColor(sf::Color::Blue);
  // rectangle1.setPosition(20, 95);
	// sf::RectangleShape rectangle2(sf::Vector2f(100.f, 100.f));
	// rectangle2.setFillColor(sf::Color::Blue);
  // rectangle2.setPosition(390, 95);


#include "cleanuptools.hpp"
#include <SFML/Graphics.hpp>
#include <csignal>
#include <string>

// temp includes
#include <chrono>
#include <thread>
#include "scene.hpp"


namespace fs = std::filesystem;

int main()
{
  int pid;
  int AUTOCLEAN = 0;
  int EVENTPROCESSED = 1;
  int MANUALCLEAN = 0;

  Scene interface;

  int width = interface.getWidth();
  int height = interface.getHeight();

  sf::Color bgColour = interface.getBgColour();

  /* Background Settings */
	sf::RenderWindow window(sf::VideoMode(width, height), "Cleanup",
      sf::Style::Titlebar | sf::Style::Close); // default
  window.setVerticalSyncEnabled(true);
  /** Cleaner **/

  std::string dirPath = fs::current_path();

  CleanupTools cleaner(dirPath);

  /* Event-based rendering */
	while (window.isOpen()) {
		sf::Event event;

    if (MANUALCLEAN) {
      // process shit here
      std::this_thread::sleep_for(std::chrono::milliseconds(1500));
      // manualButton.finish();
      MANUALCLEAN = 0;
      EVENTPROCESSED = 1;
    }

		while (window.pollEvent(event)) {

      float x = sf::Mouse::getPosition(window).x;
      float y = sf::Mouse::getPosition(window).y;
			switch(event.type) {

				case sf::Event::Closed:
          window.close();
          if (AUTOCLEAN) kill(pid, SIGKILL);
					break;

        case sf::Event::MouseButtonPressed: {
          // first button
          EVENTPROCESSED = 1;
          if (AUTOCLEAN) kill(pid, SIGKILL);
          if (manualButton.checkPressed(x, y)) {
            MANUALCLEAN = 1;
          }

          } else {
            // no tab changes
            switch(mode) {

            case MANUAL:
              manualTab.update(x, y);
              break;

            case AUTO:
              autoTab.update(x, y);
              break;

            case GROUPINGS:
              grpTab.update(x, y);
              break;

            case IGNORE:
              ignTab.update(x, y);
              break;
            }
          std::cout << "x: " << x << std::endl;
          std::cout << "y: " << y << std::endl;
          break;
          }
        }

				default:
					break;
			}
		}

    if (EVENTPROCESSED) {
      window.clear(bgColour);

      /** Drawing text first **/
      window.draw(manualText);
      window.draw(autoText);
      window.draw(groupText);
      window.draw(ignoreText);

      /** Drawing text boxes **/
      switch(mode) {

      case MANUAL:
        manualTab.draw(window);
        manualButton.draw(window);
        revertButton.draw(window);
        break;

      case AUTO:
        autoTab.draw(window);
        autoButton.draw(window);
        break;

      case GROUPINGS:
        grpTab.draw(window);
        break;

      case IGNORE:
        ignTab.draw(window);
        break;
      }

      window.draw(divLineL);
      window.draw(divLineR);
      
      /* line bar at the top last */
      window.draw(line);

      window.display();
      EVENTPROCESSED = 0;
    }
	}

	return 0;
}
