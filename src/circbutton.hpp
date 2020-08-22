#include "SFML-2.5.1-macos-clang/include/SFML/Graphics.hpp"
#include "tinyxml2/tinyxml2.h"
#include <cmath>

/* The CircButton class is the commonly seen circular checkboxes used in 
 * other interfaces. The user will be able to toggle between "yes", which is
 * represented by a smaller, lighter circle inside the larger circle, and "no", 
 * which is just the larger circle by itself.
 */
class CircButton {
  public:

    CircButton(float x, float y, float inrad, float outrad,
        sf::Color inCol, sf::Color outCol, std::string name, bool on);

    /* Given coordinates, the function checks if it is within the range of the 
     * button or not.
     * Arguments: float x, float y, the coordinates of the click
     * Returns: a boolean whether it has been clicked or not
     */
    bool checkPressed(float x, float y);

    /* Draws the appropriate objects to the window, depending on whether the 
     * button has been pressed or not.
     * Arguments: sf::RenderWindow &window, a ref of the window that will be 
     *            drawn on
     */
    void draw(sf::RenderWindow &window);
    
    /* If a previously unpressed button has been pressed and vice versa, 
     * the function writes changes to the corresponding XML config file.
     * Arguments: tinyxml2::XMLNode *pRoot, a pointer to the corresponding XML 
     *            file
     */
    void writeChanges(tinyxml2::XMLNode *pRoot);

  private:

    std::string attrName; // crashes if I swap this to line 42 -- why?
    bool changed; // used to keep track of changes 
    bool pressed; // will be used to write changes at the end

    float innerRad, outerRad; 
    float topLeftX, topLeftY;
    float centreX, centreY;
    sf::Color innerCol, outerCol;
    sf::CircleShape innerButton, outerButton;

    void init(void);
};
