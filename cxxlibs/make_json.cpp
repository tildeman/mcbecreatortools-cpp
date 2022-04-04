#include <iostream>
#include <string>
#include <map>
#include "make_json.hpp"

using namespace std;

int main(){
	// json_value output(map<string,json_value>{ {"format_version", json_value(2)} , {"header", json_value(map<string,json_value>{})} });
	// cout << output.get_repr();
	json_object<int> o=vector<pair<string,int>>({{"a",1},{"c",2}});
	o["c"]=3;
	o["b"]=9;
	int l=o.object_pair.size();
	for (int i=0;i<l;i++) cout << o.object_pair[i].first << " " << o.object_pair[i].second << endl;
	return 0;
}