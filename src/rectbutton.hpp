// #include <SFML/Graphics.hpp>
#include "SFML-2.5.1-macos-clang/include/SFML/Graphics.hpp"

/* The RectButton class are rectangular buttons. In this programme, it will be
 * used for the different cleanup functions. This is why the class will be used
 * directly in scene.cpp.
 */
class RectButton {
  public:

    RectButton();

    RectButton(float x, float y, float w, float h, sf::Color fillCol,
        sf::Color outlineCol, std::string idletext, std::string runtext,
        sf::Font f, float textsize);

    void setAttr(float x, float y, float w, float h, sf::Color fillCol,
        sf::Color outlineCol, std::string idletext, std::string runtext,
        sf::Font f, float textsize);

    bool checkPressed(float x, float y);

    void draw(sf::RenderWindow &window);
    void finish(void); // used for after running

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
