#include <iostream>
#include <string>

using namespace std;

class Root{
private:
  int val;
public:
  Root();
};

Root::Root(){
  val = 0;
}

class Leaf{
public:
  Root* n;
  string c;
  Leaf();
  Leaf(const Leaf& other);
  ~Leaf();
  Leaf& operator=(const Leaf& rhs);
};

Leaf::Leaf(){
  n = new Root();
}

Leaf::~Leaf(){
  delete n;
}

Leaf::Leaf(const Leaf& other){
  //this->n = other.n;
  //this->c = other.c;
}

Leaf& Leaf::operator=(const Leaf& rhs){
  //this->n = rhs.n;
  //this->c = rhs.c;
  return (*this);
}

void set_color(Leaf x,string color){
  Leaf a;
  a.c = color;
  x = a;
}

int main(){
  Leaf newleaf;
  string color = "red";
  set_color(newleaf,color);
  return 0;
}
