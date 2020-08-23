#include "tab.hpp" // no rect button
#include "rectbutton.hpp" 

/* The Scene class contains four tabs, three different buttons, and other 
 * shapes that are needed to be displayed across all tabs (non tab-specific 
 * shapes). 
 *
 * It manages all the updates and displaying for the programme. */
class Scene {

  public:

    Scene();

    /* The main redrawAll function that has to be called every loop in
     * main.cpp */
    void redrawAll(sf::RenderWindow &window);

    /* Takes in different changes to the programme and updates the graphics 
     * accordingly.
     * Arguments: float x, float y - coordinates of user's click
     *            MANUALCLEAN - 1, if the programme is manual cleaning
     *            REVERT - 1, if the programme is reverting
     *            AUTOCLEAN - 1, if autoclean has been clicked
     *            isAutoActive - 1, if auto cleaning is actually taking place
     *            MODECHANGED - 1, if a new tab has been selected
     */
    void updateAll(float x, float y, int &MANUALCLEAN, 
        int &REVERT, int &AUTOCLEAN, int isAutoActive, int &MODECHANGED);

    /* Write all the changes to the appropriate config file. This is to be 
     * called before every clean, and after the programme has been closed. */
    int writeChanges(void);

    /* Gets the tab the user is currently seeing. This will be assigned to the
     * reference passed in as an argument. */
    void getMode(TabMode &mode);

    /* To be called at the beginning of main.cpp to initialise the interface.
     * Arguments: monitorPath - the absolute path to the directory that is to
     *                          be monitored
     *            resPath - the absolute path to the directory that contains
     *                      the resources (/res/) 
     */
    void loadConfig(std::string monitorPath, std::string resPath);

    /* The following functions are called to be used in main.cpp */
    int getWidth(void);
    int getHeight(void);
    sf::Color getBgColour(void);
    int getWidth2(void);
    int getHeight2(void);

    /* These functions are to be called after the corresponding clean/revert 
     * function has stopped running. It updates the interface accordingly. */
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

    // for ignore/group tabs

    // starting position for texts in the tab
    int startTextX, startTextX2, startTextY; 
    int space; // space between each lines

    /** Private helper functions **/
    bool modeChange(float x, float y);

};
