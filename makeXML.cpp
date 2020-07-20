#include <tinyxml2.h>

using namespace tinyxml2;

int main() {
  XMLDocument xmlDoc;
  XMLNode *pRoot = xmlDoc.NewElement("Root");
  xmlDoc.InsertFirstChild(pRoot);

  XMLElement *pElement = xmlDoc.NewElement("topLeftX");
  pElement->SetText(0);
  pRoot->InsertEndChild(pElement);
  pElement = xmlDoc.NewElement("topLeftY");
  pElement->SetText(0);
  pRoot->InsertEndChild(pElement);

  pElement = xmlDoc.NewElement("width");
  pElement->SetText(69);
  pRoot->InsertEndChild(pElement);
  pElement = xmlDoc.NewElement("height");
  pElement->SetText(32);
  pRoot->InsertEndChild(pElement);

  pElement = xmlDoc.NewElement("rightTabLine");
  pElement->SetAttribute("width", 30);
  pElement->SetAttribute("height", 1);
  // pElement->SetAttribute("r", 255); // all white anyway?
  // pElement->SetAttribute("g", 255);
  // pElement->SetAttribute("b", 255);
  pElement->SetAttribute("x", 69);
  pElement->SetAttribute("y", 2);
  pRoot->InsertEndChild(pElement);

  pElement = xmlDoc.NewElement("leftTabLine");
  pElement->SetAttribute("width", 0);
  pElement->SetAttribute("height", 0);
  // pElement->SetAttribute("r", 255);
  // pElement->SetAttribute("g", 255);
  // pElement->SetAttribute("b", 255);
  pElement->SetAttribute("x", 0);
  pElement->SetAttribute("y", 0);
  pRoot->InsertEndChild(pElement);

  xmlDoc.SaveFile("manualConfig.xml");

  return 0;
}
