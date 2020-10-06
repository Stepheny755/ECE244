# Lecture 11 - C++ Input/Output (IO)
Nov.6/2020

## The getline Function

Last lecture an interesting property of strings and **delimiters** was brought up:
* Trying to `cin` "hi there" will only place "hi" into the variable, as the " " character is a **delimiter**

The `getline` function
* Possible to get the entire line, *spaces included*, into a string
* Takes the ***entire*** input stream and places it into the string argument

#### main.cpp
```c++
#include <string>
int main(){
  string fullName;
  getline(cin,fullName); //or cin.getline(fullName,256)
  cout << fullName;
}
```
Notes:
1. You need to `#include <string>` to use `getline`
    * `getline` defined in string header
2. `getline(cin,fullName);`
    * Notice that we pass `cin` to `getline`
3. `cin.getline(fullName,256);`
    * Another way to call getline is `cin.getline(fullName,256)`
      * Equivalent to point 2
      * Reads 256 characters

## User-Created Streams

The notion of streams in c++ is incredibly powerful, so what if we want to create our own input streams?
* **String Streams**
  * Read in and out of a string
* **File Streams**
  * Read in and out of a file on the hard drive

## String Streams

#### main.cpp
```c++
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main(){
  int anInteger;
  string inputLine;
  inputLine="204 113";

  stringstream myOwnStream (inputLine);
  myOwnStream >> anInteger;
  myOwnStream >> anInteger;

  return 0;
}
```
Notes:
1. Must include `<sstream>` header to use **string stream**
    * **String stream** defined in `<sstream>` header
2. `stringstream myOwnStream(inputLine);`
    * Creates a new **stream** called "myOwnStream"
    * Initializes this stream with `string` "inputLine"
3. `myOwnStream >> anInteger;`
    * Reads an integer from stream "myOwnStream" into "anInteger"
    * *Exactly* the same functionality as `cin`
      * General functionality: read from input stream into variable
        * `sstream` reads from **string stream** into variable
        * `cin` reads from **input stream** into variable
