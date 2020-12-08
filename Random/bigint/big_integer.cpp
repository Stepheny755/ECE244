#include "big_integer.h"
#include <iostream>
#include <string>

using namespace std;

bigint::bigint(string s){
  this->value = s;
  this->size = (this->value).length();
}

bigint::bigint(int i){
  this->value = to_string(i);
  this->size = (this->value).length();
}

bigint::bigint(){
  this->value = "";
  this->size = 0;
}

bigint::bigint(bigint & src){
  this->value = src.value;
  this->size = src.size;
}

string bigint::add(string a,string b,float alen,float blen) const{
  float maxlen = 0;
  if(alen>=blen){
    maxlen=alen;
    b.insert(b.begin(),alen-blen,'0');
  }else{
    maxlen=blen;
    a.insert(a.begin(),blen-alen,'0');
  }
  string out = "";
  int carry = 0;
  for(int i = (int)maxlen-1;i >=0;i--){
    int ai = a[i] - '0';
    int bi = b[i] - '0';
    int s = ai+bi+carry;
    if(s>=10){
      s = s%10;
      carry = 1;
    }else{
      carry = 0;
    }
    out = to_string(s)+out;
    //cout << "out:  " << out << " ai: " << ai << " bi: " << bi << endl;
  }
  return out;
}

bigint bigint::operator+(const bigint & rhs) const{
  bigint tmp(add(this->value,rhs.value,this->size,rhs.size));
  return tmp;
}

bigint bigint::operator+(int rhs) const{
  bigint tmp(add(this->value,to_string(rhs),this->size,to_string(rhs).length()));
  return tmp;
}

bigint operator+(int lhs,const bigint & rhs){
  bigint tmp(rhs.add(rhs.value,to_string(lhs),rhs.size,to_string(lhs).length()));
  return tmp;
}

ostream& operator<<(ostream& os,const bigint & x){
  os << x.value << " " << x.size << endl;
  return os;
}
