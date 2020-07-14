#include <SFML/Graphics.hpp>
#include <cmath>

class Button {
  public:

    Button(float x, float y, float inrad, float outrad,
        sf::Color inCol, sf::Color outCol) {
      topLeftX = x;
      topLeftY = y;
      outerRad = outrad;
      outerCol = outCol;
      innerRad = inrad;
      innerCol = inCol;
      init();
    }

    void checkPressed(float x, float y);
    void draw(sf::RenderWindow &window);

  private:
    bool pressed;
    float innerRad, outerRad; 
    float topLeftX, topLeftY;
    float centreX, centreY;
    sf::Color innerCol, outerCol;
    sf::CircleShape innerButton, outerButton;

    void init(void);
};
