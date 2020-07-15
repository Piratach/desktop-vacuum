#include "circbutton.hpp"

// Tab functions like a button but is not actually one...
// Tab class will deal with all the tab switching completely EXCEPT for 
// the left and right horizontal lines governing the tabs
// That will be done externally in scene.cpp
class Tab {
  public:

    Tab (int tabMode, float x, float y, float w, float h) {
      mode = tabMode;
      topLeftX = x;
      topLeftY = y;
      width = w;
      height = h;
    }

    // this will get called from scene.cpp - more explicit this way
    // will also set xmlFilename variable in this function
    //
    // hardcoded for now...
    int loadConfig(std::string xmlFilename);

    // this will be called in scene.getMode(float x, float y);
    bool checkPressed(float x, float y);

    // checking the individual buttons in the vectors for updates
    void update(float x, float y);

    // basically calls draw for all the buttons and texts
    // the decision to draw or not will be decided in scene.cpp
    void draw(sf::RenderWindow &window);

    // basically calls writeChanges for all the buttons 
    void writeChanges(void);

  private:
    int mode; // 0, 1, 2, 3 - identifies which mode this tab is assigned to
    float topLeftX, topLeftY, width, height;
    sf::RectangleShape leftTabLine, rightTabLine;

    // array of circular buttons
    // array of text lines
    std::vector<CircButton> circButtonArray;
    std::vector<sf::Text> textArray;

    std::string xmlFilename;

};
