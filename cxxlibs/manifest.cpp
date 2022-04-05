#include <iostream>
#include "manifest.hpp"

using namespace std;

int main(){
	manifest n;
	cout << "Non-dependent:\n" << n.generate_nondependent(
		"data",
		"abv",
		"sontdfdfdf",
		{1,17,0},
		true,
		{string("aa"),string("bb"),string("cc")},
		"http://localhost",
		1
	) << endl;
	vector<string> r=n.generate_dependent(
		"abv",
		"dixneuf",
		vector<json_value> {1,17,0},
		true,
		true,
		vector<json_value> {string("aiw"),string("aed"),string("ddd")},
		"http://localhost",
		"rpbv",
		"dikneuph",
		vector<json_value> {1,17,0},
		true,
		vector<json_value> {string("rpw"),string("ddd"),string("wwddd")},
		"http://192.168.32.1",
		true,
		true);
	cout << "Dependent: \n" << r[0] << endl << r[1] << endl;
	return 0;
}