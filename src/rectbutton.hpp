// #include <SFML/Graphics.hpp>
#include "SFML-2.5.1-macos-clang/include/SFML/Graphics.hpp"

/* The RectButton class are rectangular buttons. In this programme, it will be
 * used for the different cleanup functions. This is why the class will be used
 * directly in scene.cpp.
 */
class RectButton {
  public:

    /* This constructor is used to initialise the different buttons in
     * the Scene class constructor */
    RectButton();

    /* Currently unused */
    RectButton(float x, float y, float w, float h, sf::Color fillCol,
        sf::Color outlineCol, std::string idletext, std::string runtext,
        sf::Font f, float textsize);

    /* Initialises all the class variables for the button 
     * Arguments: float x, y - top left and top right point for the button
     *            idleText - text to display when not being run
     *            All other arguments should be self-explanatory
     * Returns: void
     */
    void setAttr(float x, float y, float w, float h, sf::Color fillCol,
        sf::Color outlineCol, std::string idletext, std::string runtext,
        sf::Font f, float textsize);

    /* Checks if button is pressed
     * Arguments: float x, float y - coordinates of user's click
     * Returns: true - if user has clicked the button
     *          false - otherwise
     */
    bool checkPressed(float x, float y);

    /* Draws the button to the window specified */
    void draw(sf::RenderWindow &window);

    /* To be called after programme has finished running. The button will 
     * revert back to the idle text and change its colours */
    void finish(void);

  private:
    bool pressed;
    float topLeftX, topLeftY;
    float width, height;
    float textSize;
    std::string rawIdText, rawRunText;

    sf::Font font;
    sf::Color colour, borderCol;
    sf::Text idleText, runText;
    sf::RectangleShape rect;

    void init(void);
};
