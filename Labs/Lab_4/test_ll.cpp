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

int main(){

  GroupList* gList = new GroupList();

  // Create the pool group and add it to the group list
  GroupNode* poolGroup = new GroupNode(keyWordsList[NUM_KEYWORDS-1]);
  gList->insert(poolGroup);
  gList->print();
  gList->insert(new GroupNode("g1"));
  gList->insert(new GroupNode("g2"));
  gList->print();
}
