#include <iostream>
#include <string>
#include <map>
#include "make_json.hpp"

using namespace std;

int main(){
	// json_value output(map<string,json_value>{ {"format_version", json_value(2)} , {"header", json_value(map<string,json_value>{})} });
	// cout << output.get_repr();
	json_object<json_value> o=vector<pair<string,json_value>>({{"a",1},{"c",2}});
	o["c"]=3;
	o["b"]=9;
	int l=o.object_pair.size();
	json_value v=json_value(vector<json_value>{json_value(o),json_value(false),json_value(85.47)});
	cout << v.get_repr() << endl;
	return 0;
}