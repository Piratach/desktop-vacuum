#include "circbutton.hpp"

class Tab {
  public:
    bool getMode(void);

  private:
    // array of circular buttons
    // array of text lines
    const std::vector<CircButton> &circButtonArray;
    const std::vector<sf::Text> &textArray;

};
