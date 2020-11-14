//
//  parser.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.


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

// This is a pointer to the groups list
// The list itseld must be allocated
GroupList* gList;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here
void parse_commands(string s,stringstream& sstream);

void make_shape(stringstream& sstream);
void make_group(stringstream& sstream);
void draw();
void move_shape(stringstream& sstream);
void delete_thing(stringstream& sstream);

ShapeNode* create_new_shapenode(string name,string type,int locx,int locy,int sx,int sy);
ShapeNode* find_shapenode(string name);
GroupNode* find_groupnode(string name);

int get_int(string s,int& var);
void clear_ss(stringstream& sstream);
bool parse_valid_name(string name);
bool parse_valid_name_new(string name);
bool find_name_exists(string name);
bool is_shape(string s);
bool is_command(string s);
void perr(string s);

int main() {
    // Create the groups list
    gList = new GroupList();

    // Create the pool group and add it to the group list
    GroupNode* poolGroup = new GroupNode(keyWordsList[NUM_KEYWORDS-1]);
    gList->insert(poolGroup);

    string line;
    string command;

    cout << "> ";         // Prompt for input
    getline(cin, line);    // Get a line from standard input

    while ( !cin.eof () ) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream (line);

        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        parse_commands(command,lineStream);

        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);

    }  // End input loop until EOF.

    return 0;
}


void parse_commands(string s,stringstream& sstream){
  if(s == "shape"){
    make_shape(sstream);
  }else if(s == "group"){
    make_group(sstream);
  }else if(s == "draw"){
    draw();
  }else if(s == "move"){
    move_shape(sstream);
  }else if(s == "delete"){
    delete_thing(sstream);
  }else{
    perr("invalid command");
  }
  return;
}

void make_shape(stringstream& sstream){
  int locx,locy,sx,sy;
  string name,type,slocx,slocy,ssx,ssy;

  sstream >> name >> type;
  sstream >> slocx >> slocy >> ssx >> ssy;

  get_int(slocx,locx);
  get_int(slocy,locy);
  get_int(ssx,sx);
  get_int(ssy,sy);

  if(parse_valid_name_new(name)){
    ShapeNode* tmp = create_new_shapenode(name,type,locx,locy,sx,sy);
    tmp->getShape()->draw();
    GroupNode* pl = gList->getHead();
    pl->getShapeList()->insert(tmp);
  }
}

void make_group(stringstream& sstream){
  string name;
  sstream >> name;

  if(parse_valid_name_new(name)){
    GroupNode* temp = new GroupNode(name);
    gList->insert(temp);
    cout << name << ": group" << endl;
  }
}

void draw(){
  cout << "drawing: " << endl;
  gList->print();
  return;
}

void move_shape(stringstream& sstream){
  string name1,name2;
  sstream >> name1 >> name2;

  if(parse_valid_name(name1)&&parse_valid_name(name2)){
    ShapeNode* temp = find_shapenode(name1);
    GroupNode* temp = find_groupnode(name2);
    if(temp==NULL){
      perr("shape "+name1+" not found");
      return;
    }
  }
}
void delete_thing(stringstream& sstream){

}


ShapeNode* create_new_shapenode(string name,string type,int locx,int locy,int sx,int sy){
  Shape* shape_ptr = new Shape(name,type,locx,locy,sx,sy);
  ShapeNode* shapenode_ptr = new ShapeNode();
  shapenode_ptr->setShape(shape_ptr);
  return shapenode_ptr;
}

bool parse_valid_name(string name){
  if(is_command(name)||is_shape(name)){
    perr("invalid name");
    return false;
  }
  return true;
}

bool parse_valid_name_new(string name){
  if(is_command(name)||is_shape(name)){
    perr("invalid name");
    return false;
  }else if(find_name_exists(name)){
    perr("name "+name+" exists");
    return false;
  }
  return true;
}

bool find_name_exists(string name){
  streambuf* def_cout = cout.rdbuf();
  stringstream sstream;
  cout.rdbuf(sstream.rdbuf());
  gList->print();
  cout.rdbuf(def_cout);
  while(!sstream.eof()){
    string temp;
    sstream >> temp;
    if(temp.find(name)!=string::npos){
      return true;
    }
  }
  return false;
}

ShapeNode* find_shapenode(string name){
  GroupNode* ptr = gList->getHead();
  while(ptr!=NULL){
    ShapeNode* temp = ptr->getShapeList()->find(name);
    if(temp!=NULL){
      return temp;
    }
    ptr=ptr->getNext();
  }
  return NULL;
}

GroupNode* find_groupnode(string name){

  
}

int get_int(string s,int& var){
  int x;
  string temp;
  stringstream sstream(s);
  sstream >> x;
  if(!sstream.fail()){
    if(sstream.peek()!=' '&&!sstream.eof()){
      perr("invalid argument");
      return -1;
    }else{
      var = x;
      return 1;
    }
  }else if(sstream.eof()){
    return 0;
  }else{
    perr("invalid argument");
    return -1;
  }
  return 0;
}

void clear_ss(stringstream& sstream){
  sstream.clear();
  sstream.ignore(1000,'\n');
}

bool is_command(string s){
  for(int i = 0;i < sizeof(keyWordsList)/sizeof(keyWordsList[0]);i++){
    if(s == keyWordsList[i]){
      return true;
    }
  }
  return false;
}

bool is_shape(string s){
  for(int i = 0;i < sizeof(shapeTypesList)/sizeof(shapeTypesList[0]);i++){
    if(s == shapeTypesList[i]){
      return true;
    }
  }
  return false;
}

void perr(string s){
  cout << "Error: " << s << endl;
}
