#include "tab.hpp"  // ignore dumb arse warning for now

class Scene {
  public:
    void redrawAll(void);
    void updateManTab(float x, float y);
    void updateAutoTab(float x, float y);
    void updateGrpTab(float x, float y);
    void updateIgnTab(float x, float y);

    void getMode(int &mode);

  private:
    // init to be 0
    int mode; // restricted to 0 for manual, 1 for auto, ...

    // don't need an array for this, just check all cases. A bit more tedious,
    // but it will be clearer
    Tab manualTab, autoTab, grpTab, ignTab;

};
