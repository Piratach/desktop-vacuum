#include "circbutton.hpp"
#include <filesystem>
#include <iostream>

enum TabMode {
  MANUAL,
  AUTO,
  GROUPINGS,
  IGNORELST
};

// Tab functions like a button but is not actually one...
// Tab class will deal with all the tab switching completely EXCEPT for 
// the left and right horizontal lines governing the tabs
// That will be done externally in scene.cpp
class Tab {
  public:

    Tab (TabMode m);

    // this will get called from scene.cpp - more explicit this way
    // will also set xmlFilename variable in this function
    
    // hardcoded for now...
    int loadConfig(std::string xmlFilename, std::string monitorDir, sf::Font f);

    // this will be called in scene.getMode(float x, float y);
    bool checkPressed(float x, float y);

    // checking the individual buttons in the vectors for updates
    void update(float x, float y);

    // basically calls draw for all the buttons and texts
    // the decision to draw or not will be decided in scene.cpp
    void draw(sf::RenderWindow &window);

    // basically calls writeChanges for all the buttons 
    void writeChanges(void);

    /* Public variables */
    float left, right;

  private:
    TabMode mode; // 0, 1, 2, 3 - identifies which mode this tab is assigned to
    float topLeftX, topLeftY, width, height;
    sf::RectangleShape leftTabLine, rightTabLine;

    std::string monitorDir;

    // font
    sf::Font font;

    // array of circular buttons
    // array of text lines
    std::vector<CircButton> circButtonArray;
    std::vector<sf::Text> textArray;

    std::string xmlFilename;

    inline std::string dirNameOnly(std::string s) {
      int len = 0;
      for (int i = s.size() - 1; i >= 0; i--) {
        if (std::isspace(s[i])) continue;
        else if (s[i] == '/') {
          return s.substr(i+1, len+1);
        }
        len++;
      }
      return "";
    }
};
