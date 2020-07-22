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
  pElement->SetAttribute("r", 255); // all white anyway?
  pElement->SetAttribute("g", 255);
  pElement->SetAttribute("b", 255);
  pElement->SetAttribute("x", 69);
  pElement->SetAttribute("y", 2);
  pRoot->InsertEndChild(pElement);

  pElement = xmlDoc.NewElement("leftTabLine");
  pElement->SetAttribute("width", 0);
  pElement->SetAttribute("height", 0);
  pElement->SetAttribute("r", 255);
  pElement->SetAttribute("g", 255);
  pElement->SetAttribute("b", 255);
  pElement->SetAttribute("x", 0);
  pElement->SetAttribute("y", 0);
  pRoot->InsertEndChild(pElement);

  pElement = xmlDoc.NewElement("text1");
  pElement->SetAttribute("displayText", "Cleaning :");
  pElement->SetAttribute("size", 16);
  pElement->SetAttribute("r", 255);
  pElement->SetAttribute("g", 255);
  pElement->SetAttribute("b", 255);
  pElement->SetAttribute("x", 25);
  pElement->SetAttribute("y", 52);
  pRoot->InsertEndChild(pElement);

  pElement = xmlDoc.NewElement("maxCWDLen");
  pElement->SetText(55);
  pRoot->InsertEndChild(pElement);

  pElement = xmlDoc.NewElement("text2");
  // pElement->SetAttribute("displayText", "Cleaning :");
  pElement->SetAttribute("size", 16);
  pElement->SetAttribute("r", 255);
  pElement->SetAttribute("g", 255);
  pElement->SetAttribute("b", 255);
  pElement->SetAttribute("x", 97);
  pElement->SetAttribute("y", 52);
  pRoot->InsertEndChild(pElement);

  pElement = xmlDoc.NewElement("button1");
  pElement->SetAttribute("x", 25);
  pElement->SetAttribute("y", 93);
  pElement->SetAttribute("inrad", 3);
  pElement->SetAttribute("outrad", 6);
  pElement->SetAttribute("r0", 255);
  pElement->SetAttribute("g0", 255);
  pElement->SetAttribute("b0", 255);
  pElement->SetAttribute("r1", 100);
  pElement->SetAttribute("g1", 111);
  pElement->SetAttribute("b1", 124);
  pElement->SetAttribute("pressed", true);
  pRoot->InsertEndChild(pElement);

  pElement = xmlDoc.NewElement("text3");
  pElement->SetAttribute("displayText", "Ignore extensions not in groupings");
  pElement->SetAttribute("size", 16);
  pElement->SetAttribute("r", 255);
  pElement->SetAttribute("g", 255);
  pElement->SetAttribute("b", 255);
  pElement->SetAttribute("x", 55);
  pElement->SetAttribute("y", 88);
  pRoot->InsertEndChild(pElement);

  pElement = xmlDoc.NewElement("button2");
  pElement->SetAttribute("x", 25);
  pElement->SetAttribute("y", 129);
  pElement->SetAttribute("inrad", 3);
  pElement->SetAttribute("outrad", 6);
  pElement->SetAttribute("r0", 255);
  pElement->SetAttribute("g0", 255);
  pElement->SetAttribute("b0", 255);
  pElement->SetAttribute("r1", 100);
  pElement->SetAttribute("g1", 111);
  pElement->SetAttribute("b1", 124);
  pElement->SetAttribute("pressed", true);
  pRoot->InsertEndChild(pElement);

  pElement = xmlDoc.NewElement("text4");
  pElement->SetAttribute("displayText", "Use ignorelist");
  pElement->SetAttribute("size", 16);
  pElement->SetAttribute("r", 255);
  pElement->SetAttribute("g", 255);
  pElement->SetAttribute("b", 255);
  pElement->SetAttribute("x", 55);
  pElement->SetAttribute("y", 124);
  pRoot->InsertEndChild(pElement);

  xmlDoc.SaveFile("manualConfig.xml");

  return 0;
}
