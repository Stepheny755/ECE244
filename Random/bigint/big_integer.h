#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class bigint{
private:
  string value;
  float size;

  string num_maxlen(float a,float b) const;
  string num_minlen(float a,float b) const;

  string add(string a,string b,float alen,float blen) const;
  string multiply(string a,string b,float alen,float blen) const;

public:
  bigint();
  bigint(string s);
  bigint(int d);
  bigint(bigint & src);

  void set_int(string s);
  void set_int(int s);

  bigint operator+(const bigint & rhs) const;
  bigint operator+(int rhs) const;
  bigint operator+(float rhs) const;
  friend bigint operator+(int lhs,const bigint & rhs);


  bigint operator*(const bigint & rhs) const;
  bigint operator*(int rhs) const;
  bigint operator*(float rhs) const;

  friend ostream& operator<<(ostream& os,const bigint & x);

};

#endif
