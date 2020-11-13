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

ShapeList::ShapeList(){
  head = nullptr;
}

ShapeList::~ShapeList(){
  ShapeNode* ptr = head,temp = null;
  while(ptr!=NULL){
    temp = ptr->next;
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
  ShapeNode* ptr = head,temp = NULL;
  if(ptr == NULL) return;
  while(ptr!=NULL){
    if((ptr->myShape).getName()==name){
      return ptr;
    }
    ptr = ptr->next;
  }
  return nullptr;
}

void ShapeList::insert(ShapeNode* s){
  if(head==NULL){
    head = s;
    s->next = NULL;
  }else{
    ShapeNode* ptr = head;
    while(ptr->next!=NULL){
      ptr=ptr->next;
    }
    ptr->next = s;
    s->next = NULL;
  }
}

ShapeNode* ShapeList::remove(string name){
  ShapeNode* ptr = head,temp = NULL;
  if(ptr == NULL) return;
  while(ptr!=NULL){
    if((ptr->myShape).getName()==name){
      break;
    }
    temp = ptr;
    ptr = ptr->next;
  }
  if(ptr==head){
    head=head->next;
    delete ptr;
    return nullptr;
  }
  temp->next = ptr->next;
  return ptr;
}

void ShapeList::print() const{
  listNode* ptr = head;
  while(ptr!=NULL){
    ptr->print();
    ptr=ptr->next;
  }
}
