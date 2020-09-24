# Lecture 7 - Classes and Objects

## Notes

### Access Control

**Access Control** works by class, not by object.
If we define another **member function** called AddOne:

```c++
void DayOfYear::AddOne(){
  DayOfYear temp;
  temp.day = 1;
  temp.month = 1;
  day = day + temp.day;
  month = month + temp.month;
}
```

This member function can access any private member of any object of the same type
* In this case, the type is `DayOfYear`
* temp.day and temp.month are related to the object declared in `AddOne`, which is temp
* day and month are related to the object that `AddOne` is called on

For example, in main:
```c++
DayOfYear birthday;
birthday.setDay(18);
birthday.setMonth(6);
birthday.AddOne();
```
The day and month fields noted above are related to the object birthday.

### Code Organization (Header Files)

Good practice and convention is to place class definitions in **header files** and to place member function implementations in **.cpp files**.

Organizing our `DayOfYear` class into separate `.h` and `.cpp` files:

#### DayOfYear.h
```c++
#ifndef _dayofyear_h //1
#define _dayofyear_h //2

class DayOfYear{
  private:
    int day;
    int month;
  public:
    int getDay(); //3
    int getMonth(); //3
    void setDay(int d); //4
    void setMonth(int m); //4
    void print();
};
#endif
```
Notes:
1. #ifndef checks if the given **preprocessor directive** is not defined
2. #define defines the given **preprocessor directive**
3. `getDay()` and `getMonth()` functions are considered **accessor**, or **getter** methods
  * they return/output some data (usually private) from the object
4. `setDay()` and `setMonth()` functions are considered **mutator**, or **setter** methods
  * they change some data (usually private) inside the object

#### DayOfYear.cpp
```c++
#include "DayOfYear.h" //1
#include <iostream>

int DayOfYear::getDay(){
  return day;
}
int DayOfYear::getMonth(){
  return month;
}
void DayOfYear::setDay(int d){
  day = d;
}
void DayOfYear::setMonth(int m){
  month = m;
}
void DayOfYear::print(){
  cout << day << "/" << month << endl;
}
```
Notes:
1. Need to include `DayOfYear.h` **header file**
  * The **member function** declarations are located inside `DayOfYear.h`
  * Will throw a **compile time error** if the header is not included

### Compiling

Compiling code with class definitions in .cc files is the same as normal cpp compiling:

compiling main.o
> g++ -c main.cc

compiling DayOfYear.o
> g++ -c DayOfYear.cc

linking all (main.o and DayOfYear.o)
> g++ main.o DayOfYear.o -o myprog.exe

### Need for Initialization - Constructors

Sometimes we would like to create variables and assign them initial values. For example, `int x = 0;`
* But how do we do that for objects?

**Constructors** are functions that you write and are automatically called upon creation of an object
* The **constructor** is used to initialize objects easily
  * You can pass in initial parameters to the argument with the **constructor**
* Constructors ***must*** have the same name as the class
* C++ 2011 standard has a natural mechanism that allows for **default member initializers**
  * This simplifies initialization



## Code

#### DayOfYear.h
```c++
class DayOfYear{
  private:
    int day;
    int month;
  public:
    void setDay(int d);
    void setMonth(int m);
    void print();
};
```

#### main.cpp
```c++
int main(){
  DayOfYear FirstOfJuly;
  DayOfYear Christmas;

  FirstOfJuly.day = 1;
  FirstOfJuly.month = 7;
}
```

#### DayOfYear.cpp
```c++
#include <iostream>

void DayOfYear::setDay(int d){
  day = d;
}

void DayOfYear::setMonth(int m){
  month = m;
}

void DayOfYear::print(){
  cout << day << "/" << month << endl;
}
```
