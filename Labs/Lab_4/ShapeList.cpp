//
//  ShapeList.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the ShapeList class below
#include "ShapeList.h"

ShapeList::ShapeList(){
  head = nullptr;
}

ShapeList::~ShapeList(){
  ShapeNode* ptr = head;
  ShapeNode* temp = NULL;
  while(ptr!=NULL){
    temp = ptr->getNext();
    delete ptr;
    ptr=temp;
  }
}

ShapeNode* ShapeList::getHead() const{
  return head;
}

void ShapeList::setHead(ShapeNode* ptr){
  head = ptr;
}

ShapeNode* ShapeList::find(string name) const{
  ShapeNode* ptr = head;
  ShapeNode* temp = NULL;
  if(ptr == NULL) return NULL;
  while(ptr!=NULL){
    if((ptr->getShape())->getName()==name){
      return ptr;
    }
    ptr = ptr->getNext();
  }
  return nullptr;
}

void ShapeList::insert(ShapeNode* s){
  if(head==NULL){
    head = s;
    s->setNext(NULL);
  }else{
    ShapeNode* ptr = head;
    while(ptr->getNext()!=NULL){
      ptr=ptr->getNext();
    }
    ptr->setNext(s);
    s->setNext(NULL);
  }
}

ShapeNode* ShapeList::remove(string name){
  ShapeNode* ptr = head;
  ShapeNode* temp = NULL;
  if(ptr == NULL) return NULL;
  while(ptr!=NULL){
    if((ptr->getShape())->getName()==name){
      break;
    }
    temp = ptr;
    ptr = ptr->getNext();
  }
  if(ptr==head){
    head=head->getNext();
    delete ptr;
    return NULL;
  }
  temp->setNext(ptr->getNext());
  return ptr;
}

void ShapeList::print() const{
  ShapeNode* ptr = head;
  while(ptr!=NULL){
    ptr->print();
    ptr=ptr->getNext();
  }
}
