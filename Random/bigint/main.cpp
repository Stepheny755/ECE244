#include <iostream>
#include <string>
#include "big_integer.h"

using namespace std;

int main(){

  bigint a("52344000000000000000000000000000000000000000000000");
  bigint b("5678");
  bigint c(10000000);

  cout << a << endl;
  cout << a+b << endl;
  cout << c+1234 << endl;
  cout << 6969+c << endl;
  return 0;
}
