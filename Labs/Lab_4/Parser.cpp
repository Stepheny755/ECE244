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

int get_int(string s,int& var);

int create_new_shape(string name,string type,int locx,int locy,int sx,int sy);
int find_shape(string name);

void clear_ss(stringstream& sstream);
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
    make_shape();
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
  int locx,locy,sx,sy,valid=1;
  string name,type,slocx,slocy,ssx,ssy;

  sstream >> name >> type;
  sstream >> slocx >> slocy >> ssx >> ssy;
  //cout << name << " " << type << " " << slocx << " " << slocy << " " << ssx << " " << ssy <<  endl;
  //cout << sstream.fail() << endl;
  //cout << sstream.eof() << endl;

  if(get_int(slocx,locx)==-1){ valid = -1; return; }
  if(get_int(slocy,locy)==-1){ valid = -1; return; }
  if(get_int(ssx,sx)==-1){ valid = -1; return; }
  if(get_int(ssy,sy)==-1){ valid = -1; return; }
  if(get_int(slocx,locx)==0){ valid = 0; }
  if(get_int(slocy,locy)==0){ valid = 0; }
  if(get_int(ssx,sx)==0){ valid = 0; }
  if(get_int(ssy,sy)==0){ valid = 0; }

  if(is_shape(name)||is_command(name)){
    perr("invalid shape name");
    return;
  }

  if(find_shape(name)>=0){
    perr("shape "+name+" exists");
    return;
  }

  if(type!="" && !is_shape(type)){
    perr("invalid shape type");
    return;
  }

  //stringstream* temp = new stringstream(slocx)

  if(valid==1){
    if(type == "circle" && sx!=sy){
      perr("invalid value");
      return;
    }
    if(sx<0 || sy<0 || locx<0 || locy<0){
      perr("invalid value");
      return;
    }
  }

  if(!sstream.eof()){
    perr("too many arguments");
    clear_ss(sstream);
    return;
  }

  if(sstream.fail()){
    perr("too few arguments");
    clear_ss(sstream);
    return;
  }

  //cout << name << " " << type << " " << locx << " " << locy << " " << sx << " " << sy <<  endl;

  if(shapeCount>=max_shapes){
    perr("shape array is full");
    return;
  }

  int ind = create_new_shape(name,type,locx,locy,sx,sy);
  if(ind >= 0){
    cout << "Created ";
    shapesArray[ind]->draw();
  }
  return;
}

void draw_shape(){
  cout << "drawing: " << endl;
  gList()->print();

  return;
}

void delete_shape(stringstream& sstream){
  string cmd;
  sstream >> cmd;

  int shape_index = find_shape(cmd);
  if(cmd!="" && cmd!="all" && find_shape(cmd)<0){
    perr("shape "+cmd+" not found");
    return;
  }

  if(!sstream.eof()){
    perr("too many arguments");
    clear_ss(sstream);
    return;
  }

  if(sstream.fail()){
    perr("too few arguments");
    clear_ss(sstream);
    return;
  }

  if(cmd == "all"){
    cout << "Deleted: all shapes" << endl;
    for(int i = 0;i < max_shapes;i++){
      if(shapesArray[i]){
        delete shapesArray[i];
        shapesArray[i]=nullptr;
      }
    }
  }else{
    string name = shapesArray[shape_index]->getName();
    delete shapesArray[shape_index];
    shapesArray[shape_index]=nullptr;
    cout << "Deleted shape " << name << endl;
  }
  return;
}

void move_shape(stringstream& sstream){
  string cmd,slocx,slocy;
  int locx,locy,valid=1;
  sstream >> cmd >> slocx >> slocy;

  if(get_int(slocx,locx)==-1){ valid = -1; return; }
  if(get_int(slocy,locy)==-1){ valid = -1; return; }
  if(get_int(slocx,locx)==0){ valid = 0; }
  if(get_int(slocy,locy)==0){ valid = 0; }

  int shape_index = find_shape(cmd);
  if(cmd!="" && find_shape(cmd)<0){
    perr("shape "+cmd+" not found");
    return;
  }

  if(valid==1){
    if(locx<0||locy<0){
      perr("invalid value");
      return;
    }
  }

  if(!sstream.eof()){
    perr("too many arguments");
    clear_ss(sstream);
    return;
  }

  if(sstream.fail()){
    perr("too few arguments");
    clear_ss(sstream);
    return;
  }

  shapesArray[shape_index]->setXlocation(locx);
  shapesArray[shape_index]->setYlocation(locy);
  cout << "Moved " << cmd << " to " << locx << " " << locy << endl;
}

ShapeNode* create_new_shape(string name,string type,int locx,int locy,int sx,int sy){
  if(false){
    //TODO: check if shape already exists in shapesArray
    return NULL;
  }
  Shape* shape_ptr = new Shape(name,type,locx,locy,sx,sy);
  ShapeNode* shapenode_ptr = new ShapeNode();
  shapenode_ptr->setShape(shape_ptr);
  return shapenode_ptr;
}

bool find_name(string name){
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
  for(int i = 0;i < sizeof(reserved)/sizeof(keyWordsList[0]);i++){
    if(s == keyWordsList[i]){
      return true;
    }
  }
  return false;
}

bool is_shape(string s){
  for(int i = 0;i < sizeof(shapes)/sizeof(shapeTypesList[0]);i++){
    if(s == shapeTypesList[i]){
      return true;
    }
  }
  return false;
}

void perr(string s){
  cout << "Error: " << s << endl;
}
