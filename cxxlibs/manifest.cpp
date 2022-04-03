#include <iostream>
#include "manifest.hpp"

using namespace std;

int main(){
	manifest n;
	cout << n.generate_nondependent("data","abv","sontdfdfdf",{1,17,0},true,{string("aa"),string("bb"),string("cc")},"http://localhost",1) << endl;
	return 0;
}