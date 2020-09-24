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
* temp.day and temp.month are related to the object declared in AddOne, which is temp
* day and month are related to the object that AddOne is called on

For example, in main:
```c++
DayOfYear birthday;
birthday.setDay(18);
birthday.setMonth(6);
birthday.AddOne();
```
The day and month fields noted above are related to the object birthday.

### Code Organization (Header Files)

**Header files** must be included in


## Code

### DayOfYear.h
```c++
class DayOfYear{
  private:
    int day;
    int month;
  public:
    void setDay(int d);
    void setMonth(int m);
    void print();
}
```

### main.cpp
```c++
int main(){
  DayOfYear FirstOfJuly;
  DayOfYear Christmas;

  FirstOfJuly.day = 1;
  FirstOfJuly.month = 7;
}
```

### DayOfYear.cpp
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
