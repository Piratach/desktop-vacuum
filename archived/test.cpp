#include "ext/tinyxml2/tinyxml2.h"
#include <iostream>

int main() {

  // loading XML
  tinyxml2::XMLDocument xmlDoc;
  xmlDoc.LoadFile("manualConfig.xml");
  if (xmlDoc.LoadFile("manualConfig.xml") != tinyxml2::XML_SUCCESS) {
    std::cerr << "Error: XML file not found." << std::endl;
    return -1;
  }

  // error checking?
  tinyxml2::XMLNode *pRoot = xmlDoc.FirstChild();
  tinyxml2::XMLElement *pElement;
  bool b;
  pElement = pRoot->FirstChildElement("button1");
  pElement->SetAttribute("pressed", false);
  // pElement->QueryBoolAttribute("pressed", &b);
  xmlDoc.SaveFile("manualConfig.xml");
  // pRoot->InsertEndChild(pElement);
  // std::cout << b << std::endl;
  return 0;
}
