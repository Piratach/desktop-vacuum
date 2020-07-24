#include "tinyxml2/tinyxml2.h"
#include <string>

int getTextAttr(tinyxml2::XMLElement *pElement, std::string &s,
    int &size, int &x, int &y);

int getTextAttr(tinyxml2::XMLElement *pElement, int &size, int &x, int &y);

int getButtonAttr(tinyxml2::XMLElement *pElement, int &inrad, int &outrad,
    int &x, int &y, bool &p);

int getTabLineAttr(tinyxml2::XMLElement *pElement, int &w, int &h, int &x,
    int &y);