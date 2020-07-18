#include "scene.hpp"

void Scene::redrawAll(sf::RenderWindow &window) {
  switch(mode) {
    case MANUAL: {
      manualTab.draw(window);
      manualButton.draw(window);
      revertButton.draw(window);
    }

    case AUTO: {
      autoTab.draw(window);
      autoButton.draw(window);
    }

    case GROUPINGS: {
      grpTab.draw(window);
    }

    case IGNORELST: {
      ignTab.draw(window);
    }
  }
}

void Scene::getMode(TabMode &mainMode) {
  mainMode = mode;
}

void Scene::updateAll(float x, float y)  {
  switch(mode) {
    case MANUAL: {
      manualTab.update(x, y);
    }

    case AUTO: {
      autoTab.update(x, y);
    }

    case GROUPINGS: {
      grpTab.update(x, y);
    }

    case IGNORELST: {
      ignTab.update(x, y);
    }
  }
}
