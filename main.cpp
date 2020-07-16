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
#include "rectbutton.hpp"
#include "tab.hpp"
#include <chrono>
#include <thread>

namespace fs = std::filesystem;

int main()
{
  int pid;
  int AUTOCLEAN = 0;
  int EVENTPROCESSED = 1;
  int MANUALCLEAN = 0;

  const int MANUAL = 0;
  const int AUTO = 1;

  /* Text */
  sf::Font font;
  sf::Text manualText, autoText, groupText, ignoreText;

  // loading font
  if (!font.loadFromFile("OpenSans-Light.ttf")) {
    std::cerr << "Error: OpenSans-Light.ttf not found." << std::endl;
    exit(EXIT_FAILURE);
  }

  /* Temp variables */
  Tab manualTab(MANUAL, 0, 0, 69, 32, font);
  manualTab.loadConfig("ok");
  Tab autoTab(AUTO, 69, 0, 49, 32, font);
  autoTab.loadConfig("");

  bool isManual = true;
  bool isAuto = false;

  /* Background Settings */
  sf::Color buttonColour(100, 111, 124); // dark grey
  sf::Color bgColour(38, 45, 58);  // dark blue
  sf::Color lesserBgColour(50, 60, 70);  // dark blue
	sf::RenderWindow window(sf::VideoMode(510, 290), "Cleanup",
      sf::Style::Titlebar | sf::Style::Close); // default
  window.setVerticalSyncEnabled(true);
  sf::RectangleShape line(sf::Vector2f(510, 2));
  line.setFillColor(bgColour);
  line.setFillColor(sf::Color::Black);
  line.setPosition(0, 0);

  // displaying fonts -- hardcoded
  manualText.setFont(font);
  manualText.setString("Manual");
  manualText.setCharacterSize(16);
  manualText.setFillColor(sf::Color::White);
  manualText.setPosition(6, 5);

  autoText.setFont(font);
  autoText.setString("Auto");
  autoText.setCharacterSize(16);
  autoText.setFillColor(sf::Color::White);
  autoText.setPosition(76, 5);

  groupText.setFont(font);
  groupText.setString("Groupings");
  groupText.setCharacterSize(16);
  groupText.setFillColor(sf::Color::White);
  groupText.setPosition(124, 5);

  ignoreText.setFont(font);
  ignoreText.setString("Ignorelist");
  ignoreText.setCharacterSize(16);
  ignoreText.setFillColor(sf::Color::White);
  ignoreText.setPosition(210, 5);

  /* Boxes around text */
  sf::RectangleShape divLineL;
  divLineL.setPosition(0, 31);
  divLineL.setFillColor(sf::Color::White);

  sf::RectangleShape divLineR(sf::Vector2f(441, 1));
  divLineR.setPosition(69, 31);
  divLineR.setFillColor(sf::Color::White);

  /** Rectangular buttons */
  RectButton manualButton(150, 240, 160, 30, sf::Color(36, 50, 84), 
      lesserBgColour, "Manual Cleanup",
      "Cleaning...", font, 14);

  /** Cleaner **/

  std::string dirPath = fs::current_path();

  CleanupTools cleaner(dirPath);

  /* Event-based rendering */
	while (window.isOpen()) {
		sf::Event event;

    if (MANUALCLEAN) {
      // process shit here
      std::this_thread::sleep_for(std::chrono::milliseconds(1500));
      manualButton.finish();
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

				case sf::Event::LostFocus:
					// rectangle1.setFillColor(sf::Color::Red);
          // cleaner.manualCleanup();
					break;

				case sf::Event::GainedFocus:
					// rectangle1.setFillColor(sf::Color::Blue);
          // cleaner.revert();
					break;

        case sf::Event::MouseButtonPressed: {
          // first button
          EVENTPROCESSED = 1;
          if (AUTOCLEAN) kill(pid, SIGKILL);
          if (manualButton.checkPressed(x, y)) {
            MANUALCLEAN = 1;
          }
          if (manualTab.checkPressed(x, y)) {
            isManual = true;
            isAuto = false;
            divLineL.setSize(sf::Vector2f(0, 0));
            divLineR.setPosition(69, 31);
            divLineR.setSize(sf::Vector2f(441, 1));
          } else if (autoTab.checkPressed(x, y)) {
            isManual = false;
            isAuto = true;
            divLineL.setSize(sf::Vector2f(69, 1));
            divLineR.setPosition(118, 31);
            divLineR.setSize(sf::Vector2f(392, 1));
          } else {
            // no tab changes
            if (isManual) {
              manualTab.update(x, y);
            } else if (isAuto) {
              autoTab.update(x, y);
            }
          }
          std::cout << "x: " << x << std::endl;
          std::cout << "y: " << y << std::endl;
          break;
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
      if (isManual) {
        manualTab.draw(window);
        manualButton.draw(window);
      } else if (isAuto) {
        autoTab.draw(window);
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
