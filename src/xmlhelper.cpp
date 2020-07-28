#include "xmlhelper.hpp"

int loadXML(tinyxml2::XMLDocument &xmlDoc, std::string &name) {
  if (xmlDoc.LoadFile(name.c_str()) != tinyxml2::XML_SUCCESS) {
    std::cerr << "Error: XML file not found." << std::endl;
    return -1;
  }
  return 0;
}

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
