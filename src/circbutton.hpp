#include <SFML/Graphics.hpp>
#include <cmath>

class CircButton {
  public:

    // ctor
    CircButton(float x, float y, float inrad, float outrad,
        sf::Color inCol, sf::Color outCol, bool on);

    // seriously only checks whether it is pressed or not
    bool checkPressed(float x, float y);

    // logic for changes in drawing here
    void draw(sf::RenderWindow &window);
    
    // write new preference/settings when window is closed
    // make sure to check for changes to save computational power
    void writeChanges(std::string xmlFilename);

  private:

    // to identify the corresponding field in the xml file
    // used for writes
    std::string buttonID; // CURRENTLY UNUSED
    bool changed; // used to keep track of changes -- UNUSED
    bool pressed; // will be used to write changes at the end

    float innerRad, outerRad; 
    float topLeftX, topLeftY;
    float centreX, centreY;
    sf::Color innerCol, outerCol;
    sf::CircleShape innerButton, outerButton;

    void init(void);
};
