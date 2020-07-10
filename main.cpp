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
	sf::RenderWindow window(sf::VideoMode(510, 290), "Directory Cleanup", sf::Style::Default);
	sf::RectangleShape rectangle1(sf::Vector2f(100.f, 100.f));
	rectangle1.setFillColor(sf::Color::Blue);
  rectangle1.setPosition(20, 95);
	sf::RectangleShape rectangle2(sf::Vector2f(100.f, 100.f));
	rectangle2.setFillColor(sf::Color::Blue);
  rectangle2.setPosition(390, 95);

  std::string dirPath = fs::current_path();

  CleanupTools cleaner(dirPath);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
      float x = sf::Mouse::getPosition(window).x;
      float y = sf::Mouse::getPosition(window).y;
			switch(event.type)
			{
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
          if (20 <= x && x <= 120 && y >= 95 && y <= 195) {
            rectangle1.setFillColor(sf::Color::Red);
            rectangle2.setFillColor(sf::Color::Blue);
            cleaner.manualCleanup();
          } else if (390 <= x && x <= 490 && y >= 95 && y <= 195) {
            rectangle2.setFillColor(sf::Color::Red);
            rectangle1.setFillColor(sf::Color::Blue);
            cleaner.revert();
          } else {
            if (!AUTOCLEAN) {
              rectangle2.setFillColor(sf::Color::Blue);
              rectangle1.setFillColor(sf::Color::Blue);
              pid = fork();
              if (pid == 0) {
                cleaner.autoCleanup();
                exit(0);
              }
              AUTOCLEAN = 1;
            } else {
              kill(pid, SIGKILL);
            }
          }
          std::cout << "x: " << x << std::endl;
          std::cout << "y: " << y << std::endl;
          break;

				default:
					break;
			}
		}

		window.clear(sf::Color::Black);
		window.draw(rectangle1);
		window.draw(rectangle2);
		window.display();
	}

	return 0;
}
