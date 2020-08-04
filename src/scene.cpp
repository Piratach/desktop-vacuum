#include "scene.hpp"

// ctor
Scene::Scene()
  : manualTab(MANUAL)
  , autoTab(AUTO)
  , grpTab(GROUPINGS)
  , ignTab(IGNORELST)
  , manualButton()
  , revertButton()
  , autoButton()
{}

void Scene::redrawAll(sf::RenderWindow &window) {

  /* Lines common in all tabs */
  window.draw(upperTabLine);
  window.draw(tabLineL);
  window.draw(tabLineR);

  /* tab names */
  for (auto t : tabNameArray) {
    window.draw(t);
  }

  /* tab specific objects */
  switch(mode) {
    case MANUAL: {
      manualTab.draw(window);
      manualButton.draw(window);
      revertButton.draw(window);
      break;
    }

    case AUTO: {
      autoTab.draw(window);
      autoButton.draw(window);
      break;
    }

    case GROUPINGS: {
      grpTab.draw(window);
      break;
    }

    case IGNORELST: {
      ignTab.draw(window);
      break;
    }
  }
}

void Scene::getMode(TabMode &mainMode) {
  mainMode = mode;
}

int Scene::getWidth(void) {
  return width;
}

int Scene::getHeight(void) {
  return height;
}

int Scene::getWidth2(void) {
  return width2;
}

int Scene::getHeight2(void) {
  return height2;
}

sf::Color Scene::getBgColour(void) {
  return bgColour;
}

void Scene::finishManualC(int &MANUALCLEAN) {
  MANUALCLEAN = 0;
  manualButton.finish();
}

void Scene::finishRevert(int &REVERT) {
  REVERT = 0;
  revertButton.finish();
}

void Scene::finishAutoC(int &AUTOCLEAN) {
  AUTOCLEAN = 0;
  autoButton.finish();
}

bool Scene::modeChange(float x, float y) {
  if (manualTab.checkPressed(x, y)) {
    mode = MANUAL;
    tabLineL.setSize(sf::Vector2f(0, 0));
    tabLineR.setPosition(manualTab.right, tabHeight);
    tabLineR.setSize(sf::Vector2f(width - manualTab.right, 1));
    return true;
  } else if (autoTab.checkPressed(x, y)) {
    mode = AUTO;
    tabLineL.setSize(sf::Vector2f(autoTab.left, 1));
    tabLineR.setSize(sf::Vector2f(width - autoTab.right, 1));
    tabLineR.setPosition(autoTab.right, tabHeight);
    return true;
  } else if (grpTab.checkPressed(x, y)) {
    mode = GROUPINGS;
    tabLineL.setSize(sf::Vector2f(grpTab.left, 1));
    tabLineR.setSize(sf::Vector2f(width - grpTab.right, 1));
    tabLineR.setPosition(grpTab.right, tabHeight);
    return true;
  } else if (ignTab.checkPressed(x, y)) {
    mode = IGNORELST;
    tabLineL.setSize(sf::Vector2f(ignTab.left, 1));
    tabLineR.setSize(sf::Vector2f(width - ignTab.right, 1));
    tabLineR.setPosition(ignTab.right, tabHeight);
    return true;
  }
  return false;
}

void Scene::updateAll(float x, float y, int &MANUALCLEAN, int &REVERT, 
    int &AUTOCLEAN, int isAutoActive, int &MODECHANGED)  {
  // assert(MANUALCLEAN == 0);
  // assert(REVERT == 0);
  // assert(AUTOCLEAN == 0);

  // take into account button presses
  if (!modeChange(x, y)) {
    switch(mode) {
      case MANUAL: {
        if (!isAutoActive && manualButton.checkPressed(x, y)) {
          MANUALCLEAN = 1;
        } else if (!isAutoActive && revertButton.checkPressed(x, y)) {
          REVERT = 1;
        } else {
          manualTab.update(x, y);
        }
        break;
      }

      case AUTO: {
        if (autoButton.checkPressed(x, y)) {
          // toggle for auto
          AUTOCLEAN = not AUTOCLEAN;
        } else {
          autoTab.update(x, y);
        }
        break;
      }

      case GROUPINGS: {
        grpTab.update(x, y);
        break;
      }

      case IGNORELST: {
        ignTab.update(x, y);
        break;
      }
    }
  } else {
    MODECHANGED = 1;
  }
}

void Scene::loadConfig(std::string monitorPath, std::string resPath) {

  /* Things needed for Tab.loadConfig */
  std::string resDir = resPath;
  std::string fontPath = resDir + "/OpenSans-Light.ttf";
  std::string confPath = resDir + "/conf/sceneConfig.xml";

  /* XML Document variables */
  tinyxml2::XMLDocument xmlDoc;
  loadXML(xmlDoc, confPath);
  tinyxml2::XMLNode *pRoot = xmlDoc.FirstChild();
  tinyxml2::XMLElement *pElement;

  // temporary variables used to load data
  int r, g, b;
  int x, y, w, h, fontSize;
  std::string s1, s2;

  pElement = pRoot->FirstChildElement("defaultCol");
  getColour(pElement, r, g, b);
  sf::Color defaultCol = sf::Color(r, g, b);

  pElement = pRoot->FirstChildElement("buttonCol");
  getColour(pElement, r, g, b);
  sf::Color buttonCol = sf::Color(r, g, b);

  pElement = pRoot->FirstChildElement("lightButtonCol");
  getColour(pElement, r, g, b);
  sf::Color lightButtonCol = sf::Color(r, g, b);

  /* start off at manual */
  mode = MANUAL;

  pElement = pRoot->FirstChildElement("width");
  pElement->QueryIntText(&width);

  pElement = pRoot->FirstChildElement("height");
  pElement->QueryIntText(&height);

  pElement = pRoot->FirstChildElement("tabHeight");
  pElement->QueryIntText(&tabHeight);

  pElement = pRoot->FirstChildElement("width2");
  pElement->QueryIntText(&width2);

  pElement = pRoot->FirstChildElement("height2");
  pElement->QueryIntText(&height2);

  // dark blue
  pElement = pRoot->FirstChildElement("bgColour");
  getColour(pElement, bgColour.r, bgColour.g, bgColour.b);

  // lighter shade of blue
  pElement = pRoot->FirstChildElement("lesserBgColour");
  getColour(pElement, lesserBgColour.r, lesserBgColour.g, lesserBgColour.b);

  // loading fonts
  if (!font.loadFromFile(fontPath)) {
  // if (!font.loadFromFile("OpenSans-Light.ttf")) {
    std::cerr << "Error: OpenSans-Light.ttf not found." << std::endl;
    exit(EXIT_FAILURE);
  }

  /* Load & init 4 different tabs */
  manualTab.loadConfig(resDir + "/conf/manualConfig.xml", monitorPath, font,
      defaultCol, lightButtonCol);
  autoTab.loadConfig(resDir + "/conf/autoConfig.xml", monitorPath, font,
      defaultCol, lightButtonCol);
  grpTab.loadConfig(resDir + "/conf/grpConfig.xml", monitorPath, font,
      defaultCol, lightButtonCol);
  ignTab.loadConfig(resDir + "/conf/ignConfig.xml", monitorPath, font,
      defaultCol, lightButtonCol);

  /* The 3 function buttons */

  pElement = pRoot->FirstChildElement("manualButton");
  getButtonAttr(pElement, x, y, w, h, s1, s2, fontSize);
  manualButton.setAttr(x, y, w, h, buttonCol, lesserBgColour, s1, s2,
      font, fontSize);

  // x is an offset
  pElement = pRoot->FirstChildElement("revertButton");
  getButtonAttr(pElement, x, y, w, h, s1, s2, fontSize);
  revertButton.setAttr(width - x, y, w, h, buttonCol, lesserBgColour, s1, s2,
      font, fontSize);

  // x is an offset
  pElement = pRoot->FirstChildElement("autoButton");
  getButtonAttr(pElement, x, y, w, h, s1, s2, fontSize);
  autoButton.setAttr(width/2 - x, y, w, h, buttonCol, lesserBgColour, s1, s2,
      font, fontSize);

  /* Lines above and below the tabs */
  pElement = pRoot->FirstChildElement("upperTabLine");
  getTabLineAttr(pElement, w, h, x, y);
  upperTabLine.setSize(sf::Vector2f(w, h));
  upperTabLine.setFillColor(bgColour);
  upperTabLine.setFillColor(sf::Color::Black);
  upperTabLine.setPosition(x, y);

  pElement = pRoot->FirstChildElement("tabLineL");
  getTabLineAttr(pElement, w, h, x, y);
  tabLineL.setPosition(x, y);
  tabLineL.setFillColor(sf::Color::White);

  pElement = pRoot->FirstChildElement("tabLineR");
  getTabLineAttr(pElement, w, h, x, y);
  tabLineR.setSize(sf::Vector2f(width - manualTab.right, h));
  tabLineR.setPosition(manualTab.right, y);
  tabLineR.setFillColor(sf::Color::White);

  /* Tab names */
  sf::Text manualText, autoText, groupText, ignoreText;

  pElement = pRoot->FirstChildElement("manualText");
  getTextAttr(pElement, s1, fontSize, x, y);
  manualText.setFont(font);
  manualText.setString(s1);
  manualText.setCharacterSize(fontSize);
  manualText.setFillColor(sf::Color::White);
  manualText.setPosition(x, y);
  tabNameArray.push_back(manualText);

  pElement = pRoot->FirstChildElement("autoText");
  getTextAttr(pElement, s1, fontSize, x, y);
  autoText.setFont(font);
  autoText.setString(s1);
  autoText.setCharacterSize(fontSize);
  autoText.setFillColor(sf::Color::White);
  autoText.setPosition(x, y);
  tabNameArray.push_back(autoText);

  pElement = pRoot->FirstChildElement("groupText");
  getTextAttr(pElement, s1, fontSize, x, y);
  groupText.setFont(font);
  groupText.setString(s1);
  groupText.setCharacterSize(fontSize);
  groupText.setFillColor(sf::Color::White);
  groupText.setPosition(x, y);
  tabNameArray.push_back(groupText);

  pElement = pRoot->FirstChildElement("ignoreText");
  getTextAttr(pElement, s1, fontSize, x, y);
  ignoreText.setFont(font);
  ignoreText.setString(s1);
  ignoreText.setCharacterSize(fontSize);
  ignoreText.setFillColor(sf::Color::White);
  ignoreText.setPosition(x, y);
  tabNameArray.push_back(ignoreText);
}

int Scene::writeChanges(void) {
  manualTab.writeChanges();
  autoTab.writeChanges();
  grpTab.writeChanges();
  ignTab.writeChanges();
  return 0;
}
