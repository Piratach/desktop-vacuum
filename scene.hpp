#include "tab.hpp" // no rect button
#include "rectbutton.hpp" 

// scene contains tabs, clean/revert buttons, and other shapes that are 
// to be displayed across all tabs

class Scene {

  public:

    Scene()
      : manualTab(MANUAL)
      , autoTab(AUTO)
      , grpTab(GROUPINGS)
      , ignTab(IGNORELST)
      , manualButton()
      , revertButton()
      , autoButton()
    {}

    void redrawAll(sf::RenderWindow &window);
    void updateAll(float x, float y);

    void getMode(TabMode &mode);
    void loadConfig(void);

    int getWidth(void);
    int getHeight(void);
    sf::Color getBgColour(void);

  private:

    TabMode mode; 
    sf::Font font;
    int width, height; //of screen
    sf::Color bgColour, lesserBgColour;

    // don't need an array for this, just check all cases. A bit more tedious,
    // but it will be clearer
    Tab manualTab, autoTab, grpTab, ignTab;

    // for all the "function buttons"
    RectButton manualButton;
    RectButton revertButton;
    RectButton autoButton;

    // for all the tab names
    std::vector<sf::Text> tabNameArray;

    // for the horizontal lines below the tabs
    sf::RectangleShape tabLineL, tabLineR;

    // dark line on top
    sf::RectangleShape upperTabLine;

    /** Private helper functions **/
    bool modeChange(float x, float y);

};
