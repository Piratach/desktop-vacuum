#include "tab.hpp" // no rect button
#include "rectbutton.hpp" 

enum TabMode {
  MANUAL,
  AUTO,
  GROUPINGS,
  IGNORELST
};

// scene contains tabs, clean/revert buttons, and other shapes that are 
// to be displayed across all tabs

class Scene {
  public:
    void redrawAll(sf::RenderWindow &window);
    void updateAll(float x, float y);

    void getMode(TabMode &mode);

  private:

    TabMode mode; 

    // don't need an array for this, just check all cases. A bit more tedious,
    // but it will be clearer
    Tab manualTab, autoTab, grpTab, ignTab;

    // for all the "function buttons"
    RectButton manualButton, revertButton, autoButton;

    // for all the tab names
    std::vector<sf::Text> tabNameArray;

    // for the horizontal lines below the tabs
    sf::RectangleShape tabLineL, tabLineR;

    // dark line on top
    sf::RectangleShape upperTabLine;

};
