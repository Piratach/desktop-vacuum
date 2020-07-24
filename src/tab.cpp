#include "tab.hpp"
// #include <iostream>

Tab::Tab (TabMode m) {
  mode = m;
}

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

int Tab::loadConfig(std::string filename, std::string monitorPath, sf::Font f,
    sf::Color defaultC, sf::Color button2C) {

  /* tmp variables */
  int w, h, x, y, size, r1, r2;
  bool p;
  std::string s;

  /* less-tmp variables */
  int maxCWDLen;

  /* permanent variables */
  xmlFilename = filename; // will have to load and get info later, abs path
  monitorDir = monitorPath;

  font = f;
  sf::Color defaultCol = defaultC;
  sf::Color button2Col = button2C;

  // loading XML
  tinyxml2::XMLDocument xmlDoc;
  if (xmlDoc.LoadFile(filename.c_str()) != tinyxml2::XML_SUCCESS) {
    std::cerr << "Error: XML file not found." << std::endl;
    return -1;
  }

  // error checking?
  tinyxml2::XMLNode *pRoot = xmlDoc.FirstChild();
  tinyxml2::XMLElement *pElement;
  
  switch (mode) {

    /* Manual tab! */
    case MANUAL: {

      pElement = pRoot->FirstChildElement("topLeftX");
      pElement->QueryIntText(&topLeftX);

      pElement = pRoot->FirstChildElement("topLeftY");
      pElement->QueryIntText(&topLeftY);

      pElement = pRoot->FirstChildElement("width");
      pElement->QueryIntText(&width);

      pElement = pRoot->FirstChildElement("height");
      pElement->QueryIntText(&height);

      pElement = pRoot->FirstChildElement("maxCWDLen");
      pElement->QueryIntText(&maxCWDLen);

      pElement = pRoot->FirstChildElement("rightTabLine");
      getTabLineAttr(pElement, w, h, x, y);

      rightTabLine.setSize(sf::Vector2f(w, h));
      rightTabLine.setFillColor(defaultCol);
      rightTabLine.setPosition(x, y);

      left = topLeftX;
      right = topLeftX + width;

      /** For future updates **/
      pElement = pRoot->FirstChildElement("text1");
      getTextAttr(pElement, s, size, x, y);
      sf::Text text1(s, font, size);
      text1.setFillColor(defaultCol);
      text1.setPosition(x, y);
      textArray.push_back(text1);

      if (monitorDir.length() >= maxCWDLen) monitorDir = dirNameOnly(monitorDir); 

      pElement = pRoot->FirstChildElement("text2");
      getTextAttr(pElement, size, x, y);
      sf::Text text2(monitorDir, font, size);
      text2.setFillColor(defaultCol);
      text2.setPosition(x, y);
      textArray.push_back(text2);

      /** Settings **/

      pElement = pRoot->FirstChildElement("button1");
      getButtonAttr(pElement, x, y, r1, r2, p);
      CircButton button1(x, y, r1, r2, defaultCol, 
          button2Col, p); 
      circButtonArray.push_back(button1);

      pElement = pRoot->FirstChildElement("text3");
      getTextAttr(pElement, s, size, x, y);
      sf::Text text3(s, font, size);
      text3.setFillColor(defaultCol);
      text3.setPosition(x, y);
      textArray.push_back(text3);

      pElement = pRoot->FirstChildElement("button2");
      getButtonAttr(pElement, x, y, r1, r2, p);
      CircButton button2(x, y, r1, r2, defaultCol, 
          button2Col, p); 
      circButtonArray.push_back(button2);

      pElement = pRoot->FirstChildElement("text4");
      getTextAttr(pElement, s, size, x, y);
      sf::Text text4(s, font, size);
      text4.setFillColor(defaultCol);
      text4.setPosition(x, y);
      textArray.push_back(text4);

      break; 
    }

    /* Auto tab! */
    case AUTO: {

      pElement = pRoot->FirstChildElement("topLeftX");
      pElement->QueryIntText(&topLeftX);

      pElement = pRoot->FirstChildElement("topLeftY");
      pElement->QueryIntText(&topLeftY);

      pElement = pRoot->FirstChildElement("width");
      pElement->QueryIntText(&width);

      pElement = pRoot->FirstChildElement("height");
      pElement->QueryIntText(&height);

      pElement = pRoot->FirstChildElement("maxCWDLen");
      pElement->QueryIntText(&maxCWDLen);

      pElement = pRoot->FirstChildElement("leftTabLine");
      getTabLineAttr(pElement, w, h, x, y);
      leftTabLine.setSize(sf::Vector2f(w, h));
      leftTabLine.setFillColor(defaultCol);
      leftTabLine.setPosition(x, y);

      pElement = pRoot->FirstChildElement("rightTabLine");
      getTabLineAttr(pElement, w, h, x, y);
      rightTabLine.setSize(sf::Vector2f(w, h));
      rightTabLine.setFillColor(defaultCol);
      rightTabLine.setPosition(x, y);

      left = topLeftX;
      right = topLeftX + width;

      /** For future updates **/
      pElement = pRoot->FirstChildElement("text1");
      getTextAttr(pElement, s, size, x, y);
      sf::Text text1(s, font, size);
      text1.setFillColor(defaultCol);
      text1.setPosition(x, y);
      textArray.push_back(text1);

      if (monitorDir.length() >= maxCWDLen) monitorDir = dirNameOnly(monitorDir); 

      pElement = pRoot->FirstChildElement("text2");
      getTextAttr(pElement, size, x, y);
      sf::Text text2(monitorDir, font, size);
      text2.setFillColor(defaultCol);
      text2.setPosition(x, y);
      textArray.push_back(text2);

      /** Settings **/

      pElement = pRoot->FirstChildElement("button1");
      getButtonAttr(pElement, x, y, r1, r2, p);
      CircButton button1(x, y, r1, r2, defaultCol, 
          button2Col, p); 
      circButtonArray.push_back(button1);

      pElement = pRoot->FirstChildElement("text3");
      getTextAttr(pElement, s, size, x, y);
      sf::Text text3(s, font, size);
      text3.setFillColor(defaultCol);
      text3.setPosition(x, y);
      textArray.push_back(text3);

      pElement = pRoot->FirstChildElement("button2");
      getButtonAttr(pElement, x, y, r1, r2, p);
      CircButton button2(x, y, r1, r2, defaultCol, 
          button2Col, p); 
      circButtonArray.push_back(button2);

      pElement = pRoot->FirstChildElement("text4");
      getTextAttr(pElement, s, size, x, y);
      sf::Text text4(s, font, size);
      text4.setFillColor(defaultCol);
      text4.setPosition(x, y);
      textArray.push_back(text4);

      pElement = pRoot->FirstChildElement("button3");
      getButtonAttr(pElement, x, y, r1, r2, p);
      CircButton button3(x, y, r1, r2, defaultCol, 
          button2Col, p); 
      circButtonArray.push_back(button3);

      pElement = pRoot->FirstChildElement("text5");
      getTextAttr(pElement, s, size, x, y);
      sf::Text text5(s, font, size);
      text5.setFillColor(defaultCol);
      text5.setPosition(x, y);
      textArray.push_back(text5);

      break; 
      // topLeftX = 69;
      // topLeftY = 0;
      // width = 49;
      // height = 32;

      // leftTabLine.setSize(sf::Vector2f(1, 30));
      // leftTabLine.setFillColor(sf::Color::White);
      // leftTabLine.setPosition(69, 2);

      // rightTabLine.setSize(sf::Vector2f(1, 30));
      // rightTabLine.setFillColor(sf::Color::White);
      // rightTabLine.setPosition(118, 2);

      // left = 69;
      // right = 118;

      // [>* For future updates *<]
      // sf::Text text1("Cleaning :", font, 16);
      // text1.setFillColor(sf::Color::White);
      // text1.setPosition(25, 52);
      // textArray.push_back(text1);

      // // check 55 again...
      // if (monitorDir.length() >= 55) monitorDir = dirNameOnly(monitorDir);
      // sf::Text text2(monitorDir, font, 16);
      // text2.setFillColor(sf::Color::White);
      // text2.setPosition(97, 52);
      // textArray.push_back(text2);

      // [>* Settings *<]

      // CircButton button1(25, 93, 3, 6, sf::Color::White, 
          // sf::Color(100, 111, 124), true); 
      // circButtonArray.push_back(button1);

      // sf::Text text3("Ignore extensions not in groupings", font, 16);
      // text3.setFillColor(sf::Color::White);
      // text3.setPosition(55, 88);
      // textArray.push_back(text3);

      // CircButton button2(25, 129, 3, 6, sf::Color::White, 
          // sf::Color(100, 111, 124), true); 
      // circButtonArray.push_back(button2);

      // sf::Text text4("Use ignorelist", font, 16);
      // text4.setFillColor(sf::Color::White);
      // text4.setPosition(55, 124);
      // textArray.push_back(text4);

      // CircButton button3(25, 165, 3, 6, sf::Color::White, 
          // sf::Color(100, 111, 124), true); 
      // circButtonArray.push_back(button3);

      // sf::Text text5("Only clean up new additions to the directory",
          // font, 16);
      // text5.setFillColor(sf::Color::White);
      // text5.setPosition(55, 160);
      // textArray.push_back(text5);

      // break; 
    }

    /* Groupings tab! */
    case GROUPINGS: {
      topLeftX = 118;
      topLeftY = 0;
      width = 87;
      height = 32;

      leftTabLine.setSize(sf::Vector2f(1, 30));
      leftTabLine.setFillColor(sf::Color::White);
      leftTabLine.setPosition(118, 2);

      rightTabLine.setSize(sf::Vector2f(1, 30));
      rightTabLine.setFillColor(sf::Color::White);
      rightTabLine.setPosition(205, 2);

      left = 118;
      right = 205;

     break; 
    }

    /* Ignorelist tab! */
    case IGNORELST: {
      topLeftX = 205;
      topLeftY = 0;
      width = 79;
      height = 32;

      leftTabLine.setSize(sf::Vector2f(1, 30));
      leftTabLine.setFillColor(sf::Color::White);
      leftTabLine.setPosition(205, 2);

      rightTabLine.setSize(sf::Vector2f(1, 30));
      rightTabLine.setFillColor(sf::Color::White);
      rightTabLine.setPosition(284, 2);

      left = 205;
      right = 284;
      break; 
    }
  }
  return 0;
}
