#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H
#include <string>
#include <fstream>
using std::string;

class bigint{
private:
  string value;
  int size;

public:
  bigint();
  bigint(string s);
  bigint(int d);

  void set_int(string s);
  void set_int(int s);

  ostream& operator<<(ostream& os,const bigint & x);

};

#endif
