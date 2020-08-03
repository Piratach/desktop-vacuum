#include "tinyxml2/tinyxml2.h"
#include <string>
#include <iostream>

int loadXML(tinyxml2::XMLDocument &xmlDoc, std::string &name);

int getTextAttr(tinyxml2::XMLElement *pElement, std::string &s,
    int &size, int &x, int &y);

int getTextAttr(tinyxml2::XMLElement *pElement, int &size, int &x, int &y);

int getButtonAttr(tinyxml2::XMLElement *pElement, int &inrad, int &outrad,
    int &x, int &y, bool &p);

int getButtonAttr(tinyxml2::XMLElement *pElement, int &x, int &y, int &w, 
    int &h, std::string &s1, std::string &s2, int &fontSize);

int getTabLineAttr(tinyxml2::XMLElement *pElement, int &w, int &h, int &x,
    int &y);

int getColour(tinyxml2::XMLElement *pElement, int &r, int &g, int &b);

int getColour(tinyxml2::XMLElement *pElement, unsigned char &r, 
    unsigned char &g, unsigned char &b);
