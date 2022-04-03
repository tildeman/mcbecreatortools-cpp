#include <iostream>
#include <string>
#include <vector>
#include "make_json.hpp"

using namespace std;

int main(){
	json_value output(map<string,json_value>{ {"format_version", json_value(2)} , {"header", json_value(map<string,json_value>{})} });
	cout << output.get_repr();
	return 0;
}