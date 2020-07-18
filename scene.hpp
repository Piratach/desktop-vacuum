#include "tab.hpp" // no rect button
#include "rectbutton.hpp" 

enum TabMode {
  MANUAL,
  AUTO,
  GROUPINGS,
  IGNORELST
};

class Scene {
  public:
    void redrawAll(sf::RenderWindow &window);
    void updateManTab(float x, float y);
    void updateAutoTab(float x, float y);
    void updateGrpTab(float x, float y);
    void updateIgnTab(float x, float y);

    void getMode(int &mode);

  private:
    // init to be 0
    TabMode mode; // restricted to 0 for manual, 1 for auto, ...

    // don't need an array for this, just check all cases. A bit more tedious,
    // but it will be clearer
    Tab manualTab, autoTab, grpTab, ignTab;

    // for all the "function buttons"
    RectButton manualButton, revertButton, autoButton;

};
