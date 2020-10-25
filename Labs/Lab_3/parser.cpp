//
//  parser.cpp
//  lab3
//
//  Modified by Tarek Abdelrahman on 2020-10-04.
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018-2020 Tarek Abdelrahman.
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

// This is the shape array, to be dynamically allocated
Shape** shapesArray;

// The number of shapes in the database, to be incremented
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

string shapes[] = {"ellipse","circle","rectangle","triangle"};
string reserved[] = {"maxShapes","create","move","rotate","draw","delete","all"};

// ECE244 Student: you may want to add the prototype of
// helper functions you write here
void parse_commands(string s,stringstream& sstream);

void create_db(stringstream& sstream);
void create_shape(stringstream& sstream);
void draw_shape(stringstream& sstream);
void delete_shape(stringstream& sstream);
void move_shape(stringstream& sstream);
void rotate_shape(stringstream& sstream);

int get_int(string s,int& var);

int create_new_shape(string name,string type,int locx,int locy,int sx,int sy);
int find_shape(string name);

void clear_ss(stringstream& sstream);
bool is_shape(string s);
bool is_command(string s);
void perr(string s);

int main() {

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
  if(s == "maxShapes"){
    create_db(sstream);
  }else if(s == "create"){
    create_shape(sstream);
  }else if(s == "move"){
    move_shape(sstream);
  }else if(s == "rotate"){
    rotate_shape(sstream);
  }else if(s == "draw"){
    draw_shape(sstream);
  }else if(s == "delete"){
    delete_shape(sstream);
  }else{
    perr("invalid command");
  }
  return;
}

void create_db(stringstream& sstream){
  //TODO: remove dangling pointers upon shapesArray deletion

  string smax;
  sstream >> smax;

  if(get_int(smax,max_shapes)>=0){
    if(max_shapes<0){
      perr("invalid value");
      return;
    }
    if(!sstream.eof()){
      perr("too many arguments");
      return;
    }
    if(sstream.fail()){
      perr("too few arguments");
      return;
    }


    for(int i = 0;i < shapeCount;i++){
      if(shapesArray[i]){
        delete shapesArray[i];
        shapesArray[i]=nullptr;
      }
    }
    delete shapesArray;
    shapesArray = nullptr;

    shapeCount = 0;

    shapesArray = new Shape*[max_shapes];
    cout << "New database: max shapes is " << max_shapes << endl;
  }
  return;
}

void create_shape(stringstream& sstream){
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

void draw_shape(stringstream& sstream){
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
    cout << "Drew all shapes" << endl;
    for(int i = 0;i < shapeCount;i++){
      if(shapesArray[i]){
        shapesArray[i]->draw();
      }
    }
  }else{
    cout << "Drew ";
    shapesArray[shape_index]->draw();
  }
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

void rotate_shape(stringstream& sstream){
  string cmd,sangle;
  int angle,valid=1;
  sstream >> cmd >> sangle;

  if(get_int(sangle,angle)==-1){ valid = -1; return; }
  if(get_int(sangle,angle)==0){ valid = 0; }

  int shape_index = find_shape(cmd);
  if(cmd!="" && find_shape(cmd)<0){
    perr("shape "+cmd+" not found");
    return;
  }

  if(valid==1){
    if(angle<0 || angle>360){
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

  shapesArray[shape_index]->setRotate(angle);
  cout << "Rotated " << cmd << " by " << angle << " degrees" << endl;
}

int create_new_shape(string name,string type,int locx,int locy,int sx,int sy){
  if(false){
    //TODO: check if shape already exists in shapesArray
    return -1;
  }

  shapesArray[shapeCount] = new Shape(name,type,locx,sx,locy,sy);
  return shapeCount++;
}

int find_shape(string name){
  for(int i = 0;i < shapeCount;i++){
    if(shapesArray[i] && shapesArray[i]->getName()==name){
      return i;
    }
  }
  return -1;
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
  for(int i = 0;i < sizeof(reserved)/sizeof(reserved[0]);i++){
    if(s == reserved[i]){
      return true;
    }
  }
  return false;
}

bool is_shape(string s){
  for(int i = 0;i < sizeof(shapes)/sizeof(shapes[0]);i++){
    if(s == shapes[i]){
      return true;
    }
  }
  return false;
}

void perr(string s){
  cout << "Error: " << s << endl;
}
