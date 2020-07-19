#include "rectbutton.hpp"
#include <iostream>


/* to be redefined later */
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
    rect.setOutlineColor(sf::Color(174, 191, 235));
    return true;
  }
  return false;
}

// to be called once during the switch/case handling
// and once in the usual drawing section....
void RectButton::draw(sf::RenderWindow &window) {
  window.draw(rect);
  if (pressed) {
    window.draw(runText);
  } else {
    window.draw(idleText);
  }
}

void RectButton::finish(void) {
  rect.setOutlineColor(sf::Color(36, 50, 84));
  rect.setOutlineColor(borderCol);
  pressed = false;
}

void RectButton::init(void) {

  // initialising the rect
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
