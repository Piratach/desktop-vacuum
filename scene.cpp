#include "scene.hpp"

void Scene::redrawAll(sf::RenderWindow &window) {
  switch(mode) {
    case MANUAL: {
      manualTab.draw(window);
    }

    case AUTO: {
      autoTab.draw(window);
    }

    case GROUPINGS: {
      grpTab.draw(window);
    }

    case IGNORELST: {
      ignTab.draw(window);
    }
  }
}
