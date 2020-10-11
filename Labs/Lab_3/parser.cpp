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

// ECE244 Student: you may want to add the prototype of
// helper functions you write here
void parse_commands(string s,stringstream& sstream);

void create_db(stringstream& sstream);
void create_shape(stringstream& sstream);

bool get_int(stringstream& sstream,int& var);
bool get_str(stringstream& sstream,string& var);
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
        //init_db(10);



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
  }else{
    perr("invalid command.");
  }
  return;
}

void create_db(stringstream& sstream){
  delete shapesArray;
  shapesArray = nullptr;

  if(get_int(sstream,max_shapes)){
    shapesArray = new Shape*[max_shapes];
    cout << "New database: max shapes is " << max_shapes << endl;
  }else{ return; }
  return;
}

void create_shape(stringstream& sstream){
  int locx,locy,sx,sy;
  string name,type;

  if(get_str(sstream,name)){
    cout << name << endl;
  }else{ return; }
  /*
  sstream >> locx;
  sstream >> locy;
  sstream >> sx;
  sstream >> sy;
  */
}

bool get_str(stringstream& sstream,string& var){
  string x;
  sstream >> x;
  if(!sstream.fail()){
    var = x;
    return true;
  }else if(sstream.eof()){
    perr("too few arguments");
  }else{
    perr("invalid argument");
  }
  sstream.clear();
  sstream.ignore(1000,'\n');
  return true;
}

bool get_int(stringstream& sstream,int& var){
  int x;
  sstream >> x;
  if(!sstream.fail()){
    if(sstream.peek()=='.'){
      perr("invalid argument");
    }else{
      var = x;
      return true;
    }
  }else if(sstream.eof()){
    perr("too few arguments");
  }else{
    perr("invalid argument");
  }
  sstream.clear();
  sstream.ignore(1000,'\n');
  return false;
}

void perr(string s){
  cout << "Error: " << s << endl;
}
