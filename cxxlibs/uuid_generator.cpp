#include "uuid_generator.hpp"
#include <iostream>

using namespace std;

int main(){
	uuid_generator a;
	cout << a.generate_uuid() << endl;
	return 0;
}