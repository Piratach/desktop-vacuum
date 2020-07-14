#include "button.hpp"
#include <iostream>

/**************************** Public Functions *******************************/

void Button::checkPressed(float x, float y) {
  float value = pow((x - centreX), 2) + pow((y - centreY), 2); 
  std::cout << value << std::endl;
  if (value <= pow(outerRad, 2)) {
    std::cout << "Pressed!" << std::endl;
    pressed = not pressed;
  }
}

void Button::draw(sf::RenderWindow &window) {
  if (pressed) {
    window.draw(outerButton);
    window.draw(innerButton);
  } else {
    window.draw(outerButton);
  }
}

/**************************** Private Functions ******************************/

// basically creates the circles
void Button::init(void) {

  centreX = topLeftX + outerRad;
  centreY = topLeftY + outerRad;
  innerButton.setRadius(innerRad);
  innerButton.setFillColor(innerCol);
  innerButton.setPosition(topLeftX + outerRad/2, topLeftY + outerRad/2);

  outerButton.setRadius(outerRad);
  outerButton.setFillColor(outerCol);
  outerButton.setPosition(topLeftX, topLeftY);

  pressed = false; // depends on saved configs
}
