#include "xmlhelper.hpp"

int getTextAttr(tinyxml2::XMLElement *pElement, std::string &s,
    int &size, int &x, int &y) {
  s = pElement->Attribute("displayText");
  pElement->QueryIntAttribute("size", &size);
  pElement->QueryIntAttribute("x", &x);
  pElement->QueryIntAttribute("y", &y);
  return 0;
}

int getTextAttr(tinyxml2::XMLElement *pElement, int &size, int &x, int &y) {
  pElement->QueryIntAttribute("size", &size);
  pElement->QueryIntAttribute("x", &x);
  pElement->QueryIntAttribute("y", &y);
  return 0;
}

int getButtonAttr(tinyxml2::XMLElement *pElement, int &x, int &y, 
    int &r1, int &r2, bool &p) {
  pElement->QueryIntAttribute("x", &x);
  pElement->QueryIntAttribute("y", &y);
  pElement->QueryIntAttribute("inrad", &r1);
  pElement->QueryIntAttribute("outrad", &r2);
  pElement->QueryBoolAttribute("pressed", &p);
  return 0;
}

int getTabLineAttr(tinyxml2::XMLElement *pElement, int &w, int &h, int &x,
    int &y) {
  pElement->QueryIntAttribute("width", &w);
  pElement->QueryIntAttribute("height", &h);
  pElement->QueryIntAttribute("x", &x);
  pElement->QueryIntAttribute("y", &y);
  return 0;
}
