#include "circbutton.hpp"

#include "xmlhelper.hpp"
#include <filesystem>
#include <iostream>
#include <fstream>

enum TabMode {
  MANUAL,
  AUTO,
  GROUPINGS,
  IGNORELST
};

/* Tab functions like a button but is not actually one. The Tab class will deal 
 * with all the tab switching completely EXCEPT for the tab lines below the 
 * tab names. That will be done externally in scene.cpp */
class Tab {
  public:

    Tab (TabMode m);

    // this will get called from scene.cpp - more explicit this way
    // will also set xmlFilename variable in this function
    
    // loads configuration from xml conf files
    int loadConfig(std::string xmlFilename, std::string monitorDir, sf::Font f,
        sf::Color defaultC, sf::Color button2Col);

    // this will be called in scene.getMode(float x, float y);
    bool checkPressed(float x, float y);

    // checking the individual buttons in the vectors for updates
    void update(float x, float y);

    // calls draw for all the buttons and texts
    // the decision to draw or not will be decided in scene.cpp
    void draw(sf::RenderWindow &window);

    // calls writeChanges for all the buttons 
    int writeChanges(void);

    // groupings mode function
    int loadGroupings(int x1, int x2, int y, int space);

    // ignoreLst mode function
    int loadIgnoreLst(int x, int y, int space);

    /* Public variables */
    float left, right;

  private:
    TabMode mode; // 0, 1, 2, 3 - identifies which mode this tab is assigned to
    int topLeftX, topLeftY, width, height;
    sf::RectangleShape leftTabLine, rightTabLine;

    std::string monitorDir;

    // font
    sf::Font font;

    // array of circular buttons
    std::vector<CircButton> circButtonArray;

    // array of text
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
