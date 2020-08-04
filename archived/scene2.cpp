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
    int &AUTOCLEAN, int isAutoActive)  {
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
  }
}

void Scene::loadConfig(std::string monitorPath, std::string resPath) {

  /* Things needed for Tab.loadConfig */
  std::string resDir = resPath;
  std::string fontPath = resDir + "/OpenSans-Light.ttf";
  sf::Color defaultCol = sf::Color::White;
  sf::Color lightButtonCol = sf::Color(100, 111, 124);

  /* start off at manual */
  mode = MANUAL;
  width = 510;
  height = 290;
  tabHeight = 31;

  // dark blue
  bgColour.r = 38;
  bgColour.g = 45;
  bgColour.b = 58;

  // lighter shade of blue
  lesserBgColour.r = 50;
  lesserBgColour.g = 60;
  lesserBgColour.b = 70;

  // loading fonts
  if (!font.loadFromFile(fontPath)) {
  // if (!font.loadFromFile("OpenSans-Light.ttf")) {
    std::cerr << "Error: OpenSans-Light.ttf not found." << std::endl;
    exit(EXIT_FAILURE);
  }

  /* Load & init 4 different tabs */
  manualTab.loadConfig(resDir + "/manualConfig.xml", monitorPath, font,
      defaultCol, lightButtonCol);
  autoTab.loadConfig(resDir + "/autoConfig.xml", monitorPath, font,
      defaultCol, lightButtonCol);
  grpTab.loadConfig(resDir + "/grpConfig.xml", monitorPath, font,
      defaultCol, lightButtonCol);
  ignTab.loadConfig(resDir + "/ignConfig.xml", monitorPath, font,
      defaultCol, lightButtonCol);

  /* The 3 function buttons */
  manualButton.setAttr(40, 240, 160, 30, sf::Color(36, 50, 84), 
      lesserBgColour, "Manual Cleanup",
      "Cleaning...", font, 14);

  revertButton.setAttr(width - 200, 240, 160, 30, sf::Color(36, 50, 84), 
      lesserBgColour, "Revert Changes",
      "Reverting...", font, 14);

  autoButton.setAttr(width/2 - 86, 240, 160, 30, sf::Color(36, 50, 84), 
      lesserBgColour, "Auto Cleanup",
      "Auto Cleaning...", font, 14);

  /* Lines above and below the tabs */
  upperTabLine.setSize(sf::Vector2f(width, 2));
  upperTabLine.setFillColor(bgColour);
  upperTabLine.setFillColor(sf::Color::Black);
  upperTabLine.setPosition(0, 0);

  tabLineL.setPosition(0, 31);
  tabLineL.setFillColor(sf::Color::White);

  tabLineR.setSize(sf::Vector2f(width - manualTab.right, 1));
  tabLineR.setPosition(manualTab.right, 31);
  tabLineR.setFillColor(sf::Color::White);

  /* Tab names */
  sf::Text manualText, autoText, groupText, ignoreText;

  manualText.setFont(font);
  manualText.setString("Manual");
  manualText.setCharacterSize(16);
  manualText.setFillColor(sf::Color::White);
  manualText.setPosition(6, 5);
  tabNameArray.push_back(manualText);

  autoText.setFont(font);
  autoText.setString("Auto");
  autoText.setCharacterSize(16);
  autoText.setFillColor(sf::Color::White);
  autoText.setPosition(76, 5);
  tabNameArray.push_back(autoText);

  groupText.setFont(font);
  groupText.setString("Groupings");
  groupText.setCharacterSize(16);
  groupText.setFillColor(sf::Color::White);
  groupText.setPosition(124, 5);
  tabNameArray.push_back(groupText);

  ignoreText.setFont(font);
  ignoreText.setString("Ignorelist");
  ignoreText.setCharacterSize(16);
  ignoreText.setFillColor(sf::Color::White);
  ignoreText.setPosition(210, 5);
  tabNameArray.push_back(ignoreText);
}

int Scene::writeChanges(void) {
  manualTab.writeChanges();
  autoTab.writeChanges();
  grpTab.writeChanges();
  ignTab.writeChanges();
  return 0;
}
