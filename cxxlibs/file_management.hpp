#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>
#include <fstream>
#include <regex>
using namespace std;
typedef basic_string<unsigned char> bstring;
typedef basic_fstream<unsigned char> bfstream;

// ***************************************
// * Note to self: use the std namespace *
// ***************************************

// *******************************
// * Lookup table for file types *
// *******************************
// +-------------+------------+
// | Filetype ID |  Used for  |
// +-------------+------------+
// |      0      |   Binary   |
// +-------------+------------+
// |      1      |    Text    |
// +-------------+------------+
// |      2      |  Directory |
// +-------------+------------+

class file{
private:
	string truncate_slashes(string strink){
		regex regex_string(".*[\\\\\\/](.+)");
		smatch match_string;
		bool a=regex_match(strink,match_string,regex_string);
		if (a){
			return match_string[1];
		}
		return strink;
	}
public:
	int filetype;
	bstring binary_contents;
	string text_contents;
	vector<file> directory_contents;
	string filename;
	file(){
		this->filetype=1;
		this->filename="";
	}
	file(string dirname,vector<file> contents){
		this->filetype=2;
		this->filename=dirname;
		this->directory_contents=contents;
	}
	file(string filename,string contents){
		this->filename=filename;
		this->filetype=1;
		this->text_contents=contents;
	}
	void read_file(string filename,bool is_binary){
		if (is_binary){
			ifstream f(filename,ios::binary);
			this->filetype=0;
			this->filename=truncate_slashes(filename);
			f.seekg(0,ios::end);
			streampos length=f.tellg();
			f.seekg(0,ios::beg);
			this->binary_contents=bstring(length,0);
			f.read((char*)&(this->binary_contents)[0],length);
		}
		else{
			fstream f(filename,ios::in|ios::ate);
			this->filetype=1;
			this->filename=truncate_slashes(filename);
			f.seekg(0,ios::end);
			streampos length=f.tellg();
			f.seekg(0,ios::beg);
			this->text_contents=string(length,'\0');
			f.read(&(this->text_contents)[0],length);
		}
	}
	void write_file(){
		if (this->filetype==0){
			ofstream w(filename,ios::binary);
			w.write((char*)&(this->binary_contents)[0],this->binary_contents.length());
			w.close();
		}
		else if (this->filetype==1){
			ofstream w(filename);
			w << this->text_contents;
			w.close();
		}
	}
	string get_repr(int indent=0){
		int i;
		string s;
		for (i=1;i<indent;i++) s+="| ";
		if (indent) s+="|-";
		s+=this->filename;
		s+="\n";
		if (this->filetype==2){
			for (i=0;i<this->directory_contents.size();i++){
				s+=this->directory_contents[i].get_repr(indent+1);
			}
		}
		return s;
	}
};