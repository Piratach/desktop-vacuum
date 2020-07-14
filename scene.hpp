class Scene {
  public:
    void redrawAll(void);
    void updateManTab(float x, float y);
    void updateAutoTab(float x, float y);
    void updateGrpTab(float x, float y);
    void updateIgnTab(float x, float y);

  private:
    int mode; // restricted to 0 for manual, 1 for auto, ...
    //Tab manualTab, autoTab, grpTab, ignTab;
};
