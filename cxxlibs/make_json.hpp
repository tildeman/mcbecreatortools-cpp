#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <regex>
#include <cmath>

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
	static string strip(string s){
		int begin,end;
		for (begin=0;begin<s.length();begin++){
			if (!(s[begin]==' '||s[begin]=='\t'||s[begin]=='\n'||s[begin]=='\r')) break;
		}
		for (end=s.length()-1;end>-1;end--){
			if (!(s[end]==' '||s[end]=='\t'||s[end]=='\n'||s[end]=='\r')) break;
		}
		if (begin>end) return "";
		string r=s.substr(begin,end-begin+1);
		return r;
	}
	static int hex_to_int(string s){
		int l=s.length(),i;
		int c=-1,r=0;
		string lookup="0123456789ABCDEF";
		string lookup_lc="0123456789abcdef";
		for (i=l-1;i>-1;i--){
			c=lookup.find(s[i]);
			if (c==string::npos) c=lookup_lc.find(s[i]);
			r*=16;
			r+=c;
		}
		return r;
	}
	//Kept me up for a whole night
	static string unescapify(string s){
		int i,l=s.length();
		string r;
		for (i=0;i<l;i++){
			int p1=0,p2=0;
			if (s[i]=='\\'){
				switch (s[i+1]){
				case '"':
					r+='"';
					break;
				case '\\':
					r+='\\';
					break;
				case '/':
					r+='/';
					break;
				case 'b':
					r+='\b';
					break;
				case 'f':
					r+='\f';
					break;
				case 'n':
					r+='\n';
					break;
				case 'r':
					r+='\r';
					break;
				case 't':
					r+='\t';
					break;
				case 'u':
					p1=json_value::hex_to_int(s.substr(i+2,4));
					if (p1>>10==54){
						r+=(char)((p1%1024)*1024+(json_value::hex_to_int(s.substr(i+8,4))%1024));
					}
					break;
				default:
					r+=s[i];
					break;
				}
				i++;
			}
			else r+=s[i];
		}
		return r;
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
			switch(val_int){
				case -1:
					output="null";
					break;
				case 0:
					output="false";
					break;
				case 1:
					output="true";
			}
		}
		else if (this->val_type==5){
			ostringstream scc;
			scc << val_float;
			output=scc.str();
		}
		output=indent_json(output);
		return output;
	}
	/*
	A JSON parsing mini-function made by neither JustAsh nor Zarkmend.
	Refer to RFC 7159 if you want to know more about what this is.
	I mean it doesn't work on huge numbers but it gets the job done.
	(as long as Discord doesn't chuck in some impossibly large number)*/
	static json_value parse(string s){
		json_value obj=json_value();
		string to_parse;
		bool is_parsing;
		s=json_value::strip(s);
		int i,l=s.length(),in_list=0,in_object=0;
		bool in_string=0;
		if (s[0]=='{'){
			string name_parse;
			bool is_parsing_name=1;
			obj.val_type=3;
			obj.val_object=json_object<json_value>{};
			for (i=1;i<l-1;i++){
				if (s[i]=='"') in_string=!in_string; // Double quotes identify a string
				if (s[i]=='\\'){ // Escape character, skip a character
					if (is_parsing_name) name_parse+='\\';
					else to_parse+='\\';
					i++;
				}
				if (s[i]=='{') in_object++;
				if (s[i]=='}') in_object--;
				if (s[i]=='[') in_list++;
				if (s[i]==']') in_list--;
				if (s[i]==':'&&in_object==0){
					is_parsing_name=0;
					continue;
				}
				if (s[i]==','&&in_object==0&&in_list==0){
					obj.val_object[json_value::parse(name_parse).val_string]=json_value::parse(to_parse);
					name_parse="";
					to_parse="";
					is_parsing_name=1;
					continue;
				}
				if (is_parsing_name) name_parse+=s[i];
				else to_parse+=s[i];
			}
			obj.val_object[json_value::parse(name_parse).val_string]=json_value::parse(to_parse);
		}
		if (s[0]=='['){
			obj.val_type=2;
			obj.val_list=vector<json_value>{};
			for (i=1;i<l-1;i++){
				if (s[i]=='"') in_string=!in_string; // Double quotes identify a string
				if (s[i]=='\\'){ // Escape character, skip a character
					to_parse+='\\';
					i++;
				}
				if (s[i]=='{') in_object++;
				if (s[i]=='}') in_object--;
				if (s[i]=='[') in_list++;
				if (s[i]==']') in_list--;
				if (s[i]==','&&in_object==0&&in_list==0){
					obj.val_list.push_back(json_value::parse(to_parse));
					to_parse="";
					continue;
				}
				to_parse+=s[i];
			}
			obj.val_list.push_back(json_value::parse(to_parse));
		}
		if (s[0]=='\"'){
			obj.val_type=1;
			obj.val_string=json_value::unescapify(s.substr(1,s.length()-2));
		}
		regex pac_int("(-)?(0|[1-9][0-9]*)(\\.[0-9]+)?([eE][-+]?[0-9]+)?");
		smatch res_pac;
		if (regex_match(s,res_pac,pac_int)){
			if (res_pac[3].matched||res_pac[4].matched){
				obj.val_type=5;
				obj.val_float=stod(s);
			}
			else{
				obj.val_type=0;
				obj.val_int=stoi(s);
			}
		}
		if (s=="null"){
			obj.val_type=4;
			obj.val_int=-1;
		}
		if (s=="true"){
			obj.val_type=4;
			obj.val_int=1;
		}
		if (s=="false"){
			obj.val_type=4;
			obj.val_int=0;
		}
		return obj;
	}
};