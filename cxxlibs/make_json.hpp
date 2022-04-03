#include <string>
#include <vector>
#include <map>

using namespace std;

class json_value{
public:
	int val_type;
	int val_int;
	string val_string;
	vector<json_value> val_list;
	map<string,json_value> val_object;
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
	json_value(map<string,json_value> o){
		val_type=3;
		val_object=o;
	}
	string get_repr(){
		if (this->val_type==0) return to_string(this->val_int);
		else if (this->val_type==1) {
			string output="\"";
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
						if (this->val_string[i]<32){
							sprintf(escape,"\\u%04x",this->val_string[i]);
							output+=escape;
						}
						else output+=this->val_string[i];
						break;
				}
			}
			output+="\"";
			return output;
		}
		else if (this->val_type==2){
			int l=this->val_list.size(),i;
			string list_repr="[\n";
			for (i=0;i<l;i++){
				list_repr+=this->val_list[i].get_repr();
				if (i<l-1) list_repr+=",\n";
			}
			list_repr+="\n]";
			return list_repr;
		}
		else if (this->val_type==3){
			int o=this->val_object.size(),i=0;
			string object_repr="{\n";
			for (const auto &[key,valu] : this->val_object){
				object_repr+=json_value(key).get_repr();
				object_repr+=": ";
				object_repr+=this->val_object[key].get_repr();
				if (i<o-1) object_repr+=",\n";
				i++;
			}
			object_repr+="\n}";
			return object_repr;
		}
		return "";
	}
};