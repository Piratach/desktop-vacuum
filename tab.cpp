#include "tab.hpp"
#include <iostream>

bool Tab::checkPressed(float x, float y) {
  if (topLeftX <= x && x <= topLeftX + width && 
      topLeftY <= y && y <= topLeftY + height) {
    return true;
  }
  return false;
}

void Tab::update(float x, float y) {
  for (auto& button : circButtonArray) {
    if (button.checkPressed(x, y)) {
      // there can only be one event each loop
      // logic is processed within checkPressed
      break;
    }
  }
}

void Tab::draw(sf::RenderWindow &window) {

  for (auto button : circButtonArray) {
    // button.draw because button is the class we created...
    button.draw(window);
  }

  for (auto text : textArray) {
    window.draw(text);
  }

  window.draw(leftTabLine);
  window.draw(rightTabLine);

}

void Tab::writeChanges(void) {
  for (auto button : circButtonArray) {
    button.writeChanges(xmlFilename);
  }
}

/******************************* Incomplete  **********************************/

int Tab::loadConfig(std::string filename) {
  xmlFilename = filename; // will have to load and get info later

  switch (mode) {

    /* Manual tab! */
    case 0: {
      rightTabLine.setSize(sf::Vector2f(30, 1));
      rightTabLine.rotate(90);
      rightTabLine.setFillColor(sf::Color::White);
      rightTabLine.setPosition(69, 2);

      /** For future updates **/
      sf::Text text1("Cleaning :", font, 16);
      text1.setFillColor(sf::Color::White);
      text1.setPosition(25, 52);
      textArray.push_back(text1);

      std::string cwd = std::filesystem::current_path();
      if (cwd.length() >= 55) cwd = dirNameOnly(cwd); // check 55 again...
      sf::Text text2(cwd, font, 16);
      text2.setFillColor(sf::Color::White);
      text2.setPosition(97, 52);
      textArray.push_back(text2);

      /** Settings **/

      CircButton button1(25, 93, 3, 6, sf::Color::White, 
          sf::Color(100, 111, 124), true); 
      circButtonArray.push_back(button1);

      sf::Text text3("Ignore extensions not in groupings", font, 16);
      text3.setFillColor(sf::Color::White);
      text3.setPosition(55, 88);
      textArray.push_back(text3);

      CircButton button2(25, 129, 3, 6, sf::Color::White, 
          sf::Color(100, 111, 124), true); 
      circButtonArray.push_back(button2);

      sf::Text text4("Use ignorelist", font, 16);
      text4.setFillColor(sf::Color::White);
      text4.setPosition(55, 124);
      textArray.push_back(text4);

      break; 
    }

    /* Auto tab! */
    case 1: {
      leftTabLine.setSize(sf::Vector2f(30, 1));
      leftTabLine.rotate(90);
      leftTabLine.setFillColor(sf::Color::White);
      leftTabLine.setPosition(69, 2);

      rightTabLine.setSize(sf::Vector2f(30, 1));
      rightTabLine.rotate(90);
      rightTabLine.setFillColor(sf::Color::White);
      rightTabLine.setPosition(118, 2);

      break; 
    }

    /* Groupings tab! */
    case 2:
     break; 

    /* Ignorelist tab! */
    case 3:
     break; 
  }
  return 0;
}
