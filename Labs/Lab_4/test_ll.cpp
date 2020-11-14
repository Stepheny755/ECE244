#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "Shape.h"
#include "ShapeNode.h"
#include "GroupNode.h"
#include "ShapeList.h"
#include "GroupList.h"

void nl(){ cout << "\n"; }
void p(string s){ cout << s << endl; }

int main(){

  GroupList* gList = new GroupList();

  // Create the pool group and add it to the group list
  GroupNode* poolGroup = new GroupNode(keyWordsList[NUM_KEYWORDS-1]);
  gList->insert(poolGroup);
  gList->print();

  nl();

  gList->insert(new GroupNode("g1"));
  gList->insert(new GroupNode("g2"));
  gList->print();

  p("place 1");

  delete gList->remove("g2");
  gList->print();

  p("place 1.1");
  delete gList->remove("g1");
  gList->print();

  p("place 1.2");
  gList->remove("g0");
  gList->print();

  p("place 1.3");
  delete gList->remove("pool");
  gList->print();

  gList->insert(new GroupNode("pool"));
  gList->insert(new GroupNode("g1"));
  gList->insert(new GroupNode("g2"));

  p("place 2");

  Shape* s1 = new Shape("disk","circle",0,0,10,10);
  ShapeNode* sn1 = new ShapeNode();
  sn1->setShape(s1);

  cout << gList->getHead()->getShapeList()->getHead() << endl;
  gList->getHead()->getShapeList()->insert(sn1);
  gList->print();

  p("place 3");

  Shape* s2 = new Shape("rect","rectangle",0,0,5,5);
  ShapeNode* sn2 = new ShapeNode();
  sn2->setShape(s2);
  gList->getHead()->getShapeList()->insert(sn2);
  gList->print();

  p("place 4");

  Shape* s3 = new Shape("ab","ellipse",0,0,20,20);
  ShapeNode* sn3 = new ShapeNode();
  sn3->setShape(s3);
  gList->getHead()->getShapeList()->insert(sn3);
  gList->print();

  p("place 5");

  delete gList->getHead()->getShapeList()->remove("rect");
  gList->print();


  p("Place 7");
  delete gList->remove("pool");
  gList->print();

  gList->remove("g1");
  gList->remove("g2");
  gList->print();

  p("Place 8");

  gList->insert(new GroupNode("pool"));
  gList->print();

  //delete s1,s2,s3;
  //delete sn1,sn2,sn3;
  delete gList;
}
