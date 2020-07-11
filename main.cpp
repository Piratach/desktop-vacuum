/*****************************************************************************
 * 1. Build a basic interface using SFML
 * 2. "Ignore" list
 * 3. Keep track if a dir has already been created or not for efficiency
 * 4. Wrap it up as an "app" available for download
 *****************************************************************************/

/*****************************************************************************
 * Interface (look at sfml-practice for reference)
 * TODO: Use Moom's size as reference for how big the window should be
 * TODO: Mac's default "X" button to close window but not the programme running
 * TODO: Auto, manual/revert button
 * TODO: Settings - with the ability to define groupings
 *                  (e.g. audio - .mid, .mp3, .wav)
 *                - add extensions
 *                - what to do with "others" (ignore/add to "others' folder)
 * TODO: Display relevant error messages!
 *****************************************************************************/


#include "cleanuptools.hpp"
#include <SFML/Graphics.hpp>
#include <csignal>

namespace fs = std::filesystem;

// some starter interface.
// Let's use SFML!

/* Functions to support
 * 1. support most recently opened projects
 * 2. create new project
 * 3. open finder
 * 4. import
 * 5. on selection, rename, delete, run */

int main()
{
	/* 1. Find out how to change colour of render window
	 *		- we want the base to be dark blue colour, not black
	 * 2. Make a button to find files in the directory */
  int pid;
  int AUTOCLEAN = 0;
  sf::Color bgColour(56, 59, 62);
  sf::Font font;
  sf::Text manualText, autoText, groupText, ignoreText;
	sf::RenderWindow window(sf::VideoMode(510, 290), "Cleanup",
      sf::Style::Default);
  sf::RectangleShape line(sf::Vector2f(510, 2));
  line.setFillColor(sf::Color::Black);
  line.setPosition(0, 0);
	// sf::RectangleShape rectangle1(sf::Vector2f(100.f, 100.f));
	// rectangle1.setFillColor(sf::Color::Blue);
  // rectangle1.setPosition(20, 95);
	// sf::RectangleShape rectangle2(sf::Vector2f(100.f, 100.f));
	// rectangle2.setFillColor(sf::Color::Blue);
  // rectangle2.setPosition(390, 95);

  std::string dirPath = fs::current_path();

  CleanupTools cleaner(dirPath);

  // loading font
  if (!font.loadFromFile("OpenSans-Light.ttf")) {
    std::cerr << "Error: OpenSans-Light.ttf not found" << std::endl;
    exit(EXIT_FAILURE);
  }

  // displaying fonts -- hardcoded
  manualText.setFont(font);
  manualText.setString("Manual");
  manualText.setCharacterSize(16);
  manualText.setFillColor(sf::Color::White);
  manualText.setPosition(10, 5);

  autoText.setFont(font);
  autoText.setString("Auto");
  autoText.setCharacterSize(16);
  autoText.setFillColor(sf::Color::White);
  autoText.setPosition(76, 5);

  groupText.setFont(font);
  groupText.setString("Groupings");
  groupText.setCharacterSize(16);
  groupText.setFillColor(sf::Color::White);
  groupText.setPosition(120, 5);

  ignoreText.setFont(font);
  ignoreText.setString("Ignorelist");
  ignoreText.setCharacterSize(16);
  ignoreText.setFillColor(sf::Color::White);
  ignoreText.setPosition(205, 5);

	while (window.isOpen()) {
		sf::Event event;
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

        case sf::Event::MouseButtonPressed:
          // first button
          if (AUTOCLEAN) kill(pid, SIGKILL);
          if (20 <= x && x <= 120 && y >= 95 && y <= 195) {
            // rectangle1.setFillColor(sf::Color::Red);
            // rectangle2.setFillColor(sf::Color::Blue);
            // cleaner.manualCleanup();
          } else if (390 <= x && x <= 490 && y >= 95 && y <= 195) {
            // rectangle2.setFillColor(sf::Color::Red);
            // rectangle1.setFillColor(sf::Color::Blue);
            // cleaner.revert();
          } else {
            // if (!AUTOCLEAN) {
              // rectangle2.setFillColor(sf::Color::Blue);
              // rectangle1.setFillColor(sf::Color::Blue);
              // pid = fork();
              // if (pid == 0) {
                // cleaner.autoCleanup();
                // exit(0);
              // }
              // AUTOCLEAN = 1;
            // }
          }
          std::cout << "x: " << x << std::endl;
          std::cout << "y: " << y << std::endl;
          break;

				default:
					break;
			}
		}

		window.clear(bgColour);
    window.draw(line);
		// window.draw(rectangle1);
		// window.draw(rectangle2);
    window.draw(manualText);
    window.draw(autoText);
    window.draw(groupText);
    window.draw(ignoreText);
		window.display();
	}

	return 0;
}
