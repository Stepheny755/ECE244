//
//  ShapeNode.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the ShapeNode class below

#include "ShapeNode.h"

ShapeNode::ShapeNode(){
  myShape = nullptr;
  next = nullptr;
}

ShapeNode::~ShapeNode(){
  delete myShape;
}

Shape* ShapeNode::getShape() const{
  return myShape;
}

void ShapeNode::setShape(Shape* ptr) const{
  mySHape = ptr;
}

ShapeNode* ShapeNode::getNext() const{
  return next;
}

void ShapeNext::setNext(ShapeNode* ptr){
  next = ptr;
}

void print() const{
  myShape->draw();
}
