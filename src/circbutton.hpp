#include "SFML-2.5.1-macos-clang/include/SFML/Graphics.hpp"
#include "tinyxml2/tinyxml2.h"
#include <cmath>

class CircButton {
  public:

    // ctor
    CircButton(float x, float y, float inrad, float outrad,
        sf::Color inCol, sf::Color outCol, std::string name, bool on);

    // seriously only checks whether it is pressed or not
    bool checkPressed(float x, float y);

    // logic for changes in drawing here
    void draw(sf::RenderWindow &window);
    
    // write new preference/settings when window is closed
    // make sure to check for changes to save computational power
    void writeChanges(tinyxml2::XMLNode *pRoot);

  private:

    // to identify the corresponding field in the xml file
    // used for writes
    std::string attrName; // 
    bool changed; // used to keep track of changes 
    bool pressed; // will be used to write changes at the end

    float innerRad, outerRad; 
    float topLeftX, topLeftY;
    float centreX, centreY;
    sf::Color innerCol, outerCol;
    sf::CircleShape innerButton, outerButton;

    void init(void);
};
