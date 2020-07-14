#include <SFML/Graphics.hpp>

// this class will be used directly in main.cpp because the things it 
// does are so important

class RectButton {
  public:

    RectButton(float x, float y, float w, float h, sf::Color fillCol,
        sf::Color outlineCol, std::string idletext, std::string runtext,
        sf::Font f, float textsize) {
      topLeftX = x;
      topLeftY = y;
      width = w;
      height = h;
      colour = fillCol;
      borderCol = outlineCol;
      rawIdText = idletext;
      rawRunText = runtext;
      font = f;
      textSize = textsize;

      init();
    }

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
