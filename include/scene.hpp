#include "tab.hpp" // no rect button
#include "rectbutton.hpp" 

// scene contains tabs, clean/revert buttons, and other shapes that are 
// to be displayed across all tabs

class Scene {

  public:

    Scene();

    void redrawAll(sf::RenderWindow &window);
    void updateAll(float x, float y, int &MANUALCLEAN, 
        int &REVERT, int &AUTOCLEAN, int isAutoActive, int &MODECHANGED);
    int writeChanges(void);

    void getMode(TabMode &mode);
    void loadConfig(std::string monitorPath, std::string resPath);

    int getWidth(void);
    int getHeight(void);
    sf::Color getBgColour(void);
    int getWidth2(void);
    int getHeight2(void);

    void finishManualC(int &MANUALCLEAN);
    void finishRevert(int &REVERT);
    void finishAutoC(int &AUTOCLEAN);

  private:

    TabMode mode; 
    sf::Font font;
    int width, height; //of screen
    int width2, height2; // resized screen for groupings and ignorelist
    int tabHeight;
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
