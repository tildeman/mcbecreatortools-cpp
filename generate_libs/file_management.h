#ifndef fileman
#define fileman

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>
#include <fstream>
#include <regex>
using namespace std;


typedef basic_string<unsigned char> bstring;

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
	string truncate_slashes(string strink);
public:
	int filetype;
	bstring binary_contents;
	string text_contents;
	vector<file> directory_contents;
	string filename;
	file();
	file(string dirname,vector<file> contents);
	file(string filename,string contents);
	void read_file(string filename,bool is_binary);
	void write_file();
	string get_repr(int indent);
};

#endif