#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;
template <typename jso>

class json_object{
public:
	vector<pair<string,jso>> object_pair;
	json_object(){
		object_pair={};
	}
	json_object(vector<pair<string,jso>> a){
		object_pair=a;
	}
	jso& operator[](string s){
		int l=object_pair.size();
		for (int i=0;i<l;i++){
			if (object_pair[i].first==s) return object_pair[i].second;
		}
		object_pair.push_back({s,jso()});
		return object_pair[l].second;
	}
};

class json_value{
private:
	string indent_json(string s){
		string o="";
		int l=s.length(),i,j,indent_level=0;
		for (i=0;i<l;i++){
			if (s[i]=='\n'&&i<l-2) o+="\n  ";
			else o+=s[i];
		}
		return o;
	}
public:
	int val_type;
	int val_int;
	double val_float;
	string val_string;
	vector<json_value> val_list;
	json_object<json_value> val_object;
	json_value(){
		val_type=0;
		val_int=0;
	}
	json_value(int n){
		val_type=0;
		val_int=n;
	}
	json_value(string s){
		val_type=1;
		val_string=s;
	}
	json_value(vector<json_value> l){
		val_type=2;
		val_list=l;
	}
	json_value(json_object<json_value> o){
		val_type=3;
		val_object=o;
	}
	json_value(bool n){
		val_type=4;
		val_int=n;
	}
	json_value(double d){
		val_type=5;
		val_float=d;
	}
	string get_repr(){
		string output="";
		if (this->val_type==0) output=to_string(this->val_int);
		else if (this->val_type==1) {
			output="\"";
			int l=this->val_string.length(),i;
			char escape[7];
			for (i=0;i<l;i++){
				switch (this->val_string[i]){
					case '\b':
						output+="\\b";
						break;
					case '\f':
						output+="\\f";
						break;
					case '\n':
						output+="\\n";
						break;
					case '\r':
						output+="\\r";
						break;
					case '\t':
						output+="\\t";
						break;
					case '\v':
						output+="\\v";
						break;
					case '\"':
						output+="\\\"";
						break;
					case '\\':
						output+="\\\\";
						break;
					default:
						if (this->val_string[i]>0&&this->val_string[i]<32){
							sprintf(escape,"\\u%04x",this->val_string[i]);
							output+=escape;
						}
						else output+=this->val_string[i];
						break;
				}
			}
			output+="\"";
		}
		else if (this->val_type==2){
			int l=this->val_list.size(),i;
			output="[\n";
			for (i=0;i<l;i++){
				output+=this->val_list[i].get_repr();
				if (i<l-1) output+=",\n";
			}
			output+="\n]";
		}
		else if (this->val_type==3){
			int o=this->val_object.object_pair.size(),i=0;
			output="{\n";
			for (auto key:val_object.object_pair){
				output+=json_value(key.first).get_repr();
				output+=": ";
				output+=key.second.get_repr();
				if (i<o-1) output+=",\n";
				i++;
			}
			output+="\n}";
		}
		else if (this->val_type==4){
			if (val_int) output="true";
			else output="false";
		}
		else if (this->val_type==5){
			output=to_string(val_float);
		}
		output=indent_json(output);
		return output;
	}
};