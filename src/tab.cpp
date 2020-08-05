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

int Tab::writeChanges(void) {
  tinyxml2::XMLDocument xmlDoc;
  if (xmlDoc.LoadFile(xmlFilename.c_str()) != tinyxml2::XML_SUCCESS) {
    std::cerr << "Error: XML file not found." << std::endl;
    return -1;
  }
  tinyxml2::XMLNode *pRoot = xmlDoc.FirstChild();
  for (auto &button : circButtonArray) {
    button.writeChanges(pRoot);
  }
  xmlDoc.SaveFile(xmlFilename.c_str());
  return 0;
}

/* For ignoreLst tab ONLY */
int Tab::loadIgnoreLst(int x, int y, int space) {
  std::string ignoreLst = monitorDir + "/desktop-vacuum/res/ignoreList.txt";
  textArray.clear();
  std::ifstream infile;
  infile.open(ignoreLst);
  if (!infile) {
    std::cerr << "Error opening " << ignoreLst;
    return -1;
  }

  std::string filename;
  while (infile >> filename) {
    sf::Text text(filename, font, 16); // universal size is 16
    text.setFillColor(sf::Color::White);
    text.setPosition(x, y);
    textArray.push_back(text);
    y = y + space;
  }

  if (textArray.empty()) {
    sf::Text text("Ignorelist is empty!", font, 16);
    text.setPosition(x, y);
    textArray.push_back(text);
  }
  infile.close();
  return 0;
}

/************************ Config Loading Functions ***************************/

int Tab::loadConfig(std::string filename, std::string monitorPath, sf::Font f,
    sf::Color defaultC, sf::Color lightButtonC) {

  /* tmp variables used for initialisation */
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
  sf::Color lightButtonCol = lightButtonC;

  // loading XML
  tinyxml2::XMLDocument xmlDoc;
  loadXML(xmlDoc, filename);
  // if (xmlDoc.LoadFile(filename.c_str()) != tinyxml2::XML_SUCCESS) {
    // std::cerr << "Error: XML file not found." << std::endl;
    // return -1;
  // }

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
          lightButtonCol, "button1", p); 
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
          lightButtonCol, "button2", p); 
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

      if (monitorDir.length() >= maxCWDLen) 
        monitorDir = dirNameOnly(monitorDir); 

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
          lightButtonCol, "button1", p); 
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
          lightButtonCol, "button2", p); 
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
          lightButtonCol, "button3", p); 
      circButtonArray.push_back(button3);

      pElement = pRoot->FirstChildElement("text5");
      getTextAttr(pElement, s, size, x, y);
      sf::Text text5(s, font, size);
      text5.setFillColor(defaultCol);
      text5.setPosition(x, y);
      textArray.push_back(text5);

      break; 
    }

    /* Groupings tab! */
    case GROUPINGS: {

      pElement = pRoot->FirstChildElement("topLeftX");
      pElement->QueryIntText(&topLeftX);

      pElement = pRoot->FirstChildElement("topLeftY");
      pElement->QueryIntText(&topLeftY);

      pElement = pRoot->FirstChildElement("width");
      pElement->QueryIntText(&width);

      pElement = pRoot->FirstChildElement("height");
      pElement->QueryIntText(&height);

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

      sf::Text text1(".jpg ======> jpg", font, 16);
      text1.setFillColor(defaultCol);
      text1.setPosition(25, 52);
      textArray.push_back(text1);

      break; 
    }

    /* Ignorelist tab! */
    case IGNORELST: {

      pElement = pRoot->FirstChildElement("topLeftX");
      pElement->QueryIntText(&topLeftX);

      pElement = pRoot->FirstChildElement("topLeftY");
      pElement->QueryIntText(&topLeftY);

      pElement = pRoot->FirstChildElement("width");
      pElement->QueryIntText(&width);

      pElement = pRoot->FirstChildElement("height");
      pElement->QueryIntText(&height);

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

      break; 
    }
  }
  return 0;
}
