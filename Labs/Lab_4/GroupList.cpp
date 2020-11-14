//
//  GroupList.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the GroupList class below
#include "GroupList.h"
#include <iostream>

GroupList::GroupList(){
  head = nullptr;
}

GroupList::~GroupList(){
  GroupNode* ptr = head;
  GroupNode* temp = NULL;
  while(ptr!=NULL){
    temp = ptr->getNext();
    delete ptr;
    ptr = temp;
  }
}

GroupNode* GroupList::getHead() const{
  return head;
}

void GroupList::setHead(GroupNode* ptr){
  head = ptr;
}

void GroupList::insert(GroupNode* s){
  if(head==NULL){
    head = s;
    s->setNext(NULL);
  }else{
    GroupNode* ptr = head;
    while(ptr->getNext()!=NULL){
      ptr=ptr->getNext();
    }
    ptr->setNext(s);
    s->setNext(NULL);
  }
}

GroupNode* GroupList::remove(string name){
  GroupNode* ptr = head;
  GroupNode* temp = NULL;
  if(ptr == NULL) return NULL;
  while(ptr!=NULL){
    if(ptr->getName()==name){
      break;
    }
    temp = ptr;
    ptr = ptr->getNext();
  }
  if(ptr==head){
    head=head->getNext();
    delete ptr;
    return nullptr;
  }
  temp->setNext(ptr->getNext());
  return ptr;
}

void GroupList::print() const{
  GroupNode* ptr = head;
  while(ptr!=NULL){
    //std::cout << "here" << std::endl;
    ptr->print();
    ptr=ptr->getNext();
  }
}
