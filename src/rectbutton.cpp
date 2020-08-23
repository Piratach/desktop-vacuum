#include "rectbutton.hpp"
#include <iostream>

/* Initial values are assigned. This is so that we are able to initialise the
 * different buttons in Scene's constructor */
RectButton::RectButton() {
  topLeftX = 0;
  topLeftY = 0;
  width = 0;
  height = 0;
  colour = sf::Color::White;
  borderCol = sf::Color::White;
  rawIdText = "";
  rawRunText = "";
  font = sf::Font();
  textSize = 0;
}

/* CURRENTLY UNUSED */
RectButton::RectButton(float x, float y, float w, float h, sf::Color fillCol,
        sf::Color outlineCol, std::string idletext, std::string runtext,
        sf::Font f, float textsize) {
  topLeftX = x;
  topLeftY = y;
  width = w;
  height = h;
  colour = fillCol;
  borderCol = outlineCol;
  rawIdText = idletext;
  rawRunText = runtext;
  font = f;
  textSize = textsize;

  init();
}

/* Assigns the button's class variables to the right values. To be called in 
 * Scene's loadConfig */
void RectButton::setAttr(float x, float y, float w, float h, sf::Color fillCol,
        sf::Color outlineCol, std::string idletext, std::string runtext,
        sf::Font f, float textsize) {
  topLeftX = x;
  topLeftY = y;
  width = w;
  height = h;
  colour = fillCol;
  borderCol = outlineCol;
  rawIdText = idletext;
  rawRunText = runtext;
  font = f;
  textSize = textsize;

  init();
}

bool RectButton::checkPressed(float x, float y) {
  if (topLeftX <= x && x <= topLeftX + width && 
      topLeftY <= y && y <= topLeftY + height) {
    pressed = true;
    rect.setOutlineColor(sf::Color(174, 191, 235)); // hardcoded colour
    return true;
  }
  return false;
}

void RectButton::draw(sf::RenderWindow &window) {
  window.draw(rect);
  if (pressed) {
    window.draw(runText);
  } else {
    window.draw(idleText);
  }
}

/* Setting pressed to false will make RectButton::draw draw the idleText next 
 * time it is called */
void RectButton::finish(void) {
  rect.setOutlineColor(sf::Color(36, 50, 84));
  rect.setOutlineColor(borderCol);
  pressed = false;
}

void RectButton::init(void) {

  // initialising the rect
  pressed = false;

  rect.setSize(sf::Vector2f(width, height));
  rect.setFillColor(colour);
  rect.setPosition(topLeftX, topLeftY);
  rect.setOutlineThickness(1); 
  rect.setOutlineColor(borderCol);

  idleText.setFont(font);
  idleText.setString(rawIdText);
  idleText.setCharacterSize(textSize);
  idleText.setFillColor(sf::Color::White); // standard - forced for all texts

  runText.setFont(font);
  runText.setString(rawRunText);
  runText.setCharacterSize(textSize);
  runText.setFillColor(sf::Color::White); 

  idleText.setPosition(topLeftX, topLeftY);
  sf::FloatRect idRect = idleText.getLocalBounds();
  idRect.left = topLeftX + (width / 2.0f) - (idRect.width / 2.0f);
  idRect.top = topLeftY + (height / 2.0f) - (idRect.height / 2.0f);
  idleText.setPosition(int(idRect.left), int(idRect.top));

  runText.setPosition(topLeftX, topLeftY);
  sf::FloatRect runRect = runText.getLocalBounds();
  runRect.left = topLeftX + (width / 2.0f) - (runRect.width / 2.0f);
  runRect.top = topLeftY + (height / 2.0f) - (runRect.height / 2.0f);
  runText.setPosition(int(runRect.left), int(runRect.top));

}
