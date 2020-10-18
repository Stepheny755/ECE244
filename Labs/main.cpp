#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main(){

	stringstream lineStream("5 ");
	int a;
	lineStream >> a;


	cout << lineStream.fail() << endl;
	cout << lineStream.eof() << endl;

	stringstream ss(" ");
	ss >> a;

	cout << ss.fail() << endl;
	cout << ss.eof() << endl;

	return 0;
}
