# Assorted Notes

## Passing Pointers by Reference

Passing pointers by reference allows functions to change the *value of the argument* (e.g. change the address of the pointer)

```c++
#include <iostream>

void foo(int* & ptr){
  ptr = nullptr;
}
```
Notes:
1. Pointer passed into `ptr` will have it's value changed to `nullptr`

However, passing by *reference* will remove modification protection
* Use `const` keyword if need modification protection

Use pass by *reference* when you need
1. The function to modify the argument
  * When you need the function to affect what the pointer is *pointing to*

### Copy Constructor

Must pass by *reference* for the copy constructor
* Otherwise you end up with recursive loop
  * To pass by value, you call the copy constructor, which has pass by value, which calls copy constructor

## Returning Data from a Function

It is not *safe* to return data from a function by reference **if**
* The data goes out of scope
  * e.g. The data being returned is local to the function

## Class Constructor

Contructors **don't need** to be public
* Can have private (internal) constructors

# Shallow vs Deep

For pointers:

Shallow copies copy very little
* Creates new pointer
* Sets pointer value to be the **same** value as the pointer being copied
  * This results in *two* pointers to the same object

Deep copies
* Creates new pointer
* Creates new data pointed to by pointer with the same value as the pointer being copied
  * Separate objects

# Binary Tree Deletion

Delete a Binary tree in *postorder* traversal

# Pointers as Class Data Members

A class with a *dynamically* allocated pointer will likely have
1. Copy Constructor
2. Destructor
3. Overloaded Assignment Operator

# Virtual Function

Destructors should be defined virtually

```c++
Base *ptr = new Base();
Base *ptr1 = new D1(); //D1 inherits publicly from base
delete ptr;
delete ptr1;
```
Note: In this case, if the destructor is *not* defined virtually, `delete ptr1` ***only*** calls the destructor for the type of `ptr1` which is `Base*`
* `~D1();` is ***not*** called

# Const Functions

```c++
int a() const{}
```

**constant member functions** *cannot* call class mutator functions
