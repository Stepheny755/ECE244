#include "big_integer.h"
#include <iostream>
#include <string>

bigint::bigint(string s){
  this->value += s;
}
