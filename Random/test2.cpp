#include <iostream>

using namespace std;

class test{
private:
  int* a;
public:
  test(){ a = new int; *a = 0;}
  test(int* i){a = i;}
  //test(){ cout << "here" << endl; }

};

void process(test a){
  test b;
  test c;
}

int main(){

  int j = 10;
  int* i[2] = {&j,&j};
  cout << *(i[0]) << endl;
  j = 5;
  cout << *(i[1]) << endl;


  int* a;
  a = new int();

  if(true){
    test* temp = new test();
  }

  process(*(new test()));

  return 0;
}
