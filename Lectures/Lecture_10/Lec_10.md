# Lecture 10 - C++ Input/Output (IO)
Nov.1/2020

## The Fail flag

One thing to note:

#### main.cpp
```c++
int main(){
  int x = 9;
  string y;
  cin >> x;
  ...
  cin >> y;
}
```
If the input stream is:

> 'T' 'e' 'n' ' ' '2'

`cin` will **fail** at `cin >> x;`
* Attempting to place `characters` into `int`

However, `cin >> y` will run and place 'ten' into y
* Buffer has not been cleared
* **Fail** flag is *still* set to true

## Checking for Valid Cin

#### main.cpp
```c++
#include <iostream>
using namespace std;
int main(){
  int anInteger;
  bool retry = true;
  while(retry){
    cin >> anInteger;
    if(cin.fail()){
      cout << "bad input" << endl;
    }else{
      cout << "read from cin~!" << endl;
    }
  }
  return 0;
}
```
If the input stream is:

> 'T' 'e' 'n' ' ' '2'

Notes:
* This is an *infinite loop*
  * On the first iteration of `while` loop:
    * `cin` attempts to place 'T' into variable `anInteger`
    * Fails to do so, and raises **Fail flag** because of type mismatch.
  * The `cin` stream is ***not modified*** between consecutive `cin` calls
    * The `cin` stream remains because the initial call raised the **Fail flag**
    * `cin.fail()` will always evaluate to true, since the stream ***has not changed***
  * `bool retry` never gets updated
* `anInteger` does not change if fail

So how do we deal with this issue?
* Flags are **persistent**
  * Flags remain until you reset them
  * No input until Flags are set

#### main.cpp
```c++
#include <iostream>
using namespace std;
int main(){
  int anInteger;
  bool retry = true;
  while(retry){
    cin >> anInteger;
    if(cin.fail()){
      cout << "bad input" << endl;
      cin.clear();
      cin.ignore(1000,'\n');
    }else{
      cout << "read from cin~!" << endl;
    }
  }
  return 0;
}
```
Notes:
* `cin.clear();`
  * This function *clears the flags*
    * Will turn off the **Fail flag**
  * Without calling `cin.clear();`, subsequent `cin` calls will not run
* `cin.ignore(1000,'\n');`
  * This function ignores characters in the stream
    * `cin.ignore();` takes two parameters. Either:
      1. Will *ignore 1000 characters*
        * 1000 is an arbitrary example, some systems have a limit of 256 characters per stream
      2. Will *ignore until '\n' is found*
* Handle errors in this order:
  * Clear flags with `cin.clear();`, ***and then*** ignore stream characters with `cin.ignore();`
    * The reverse order may not work, since `cin.ignore()` depends on flags

## cin.ignore

`cin.ignore` is used to discard part of the stream
* Compare:
  1. `cin.ignore(1000,'\n');`
  2. `cin.ignore(1000,' ');`
