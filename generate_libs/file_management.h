#ifndef fileman
#define fileman

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>
#include <regex>
#include <minizip/zip.h>
#include "uuid_generator.h"
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
	//Strips and reduces forward slashes
	string truncate_slashes(string strink);
	// Recursively add files to a minizip zipFile of the "zfptr" pointer
	void add_files_to_zip(string subdirectory,zipFile* zfptr);
	// Sets the date of of the instance object zip_fi
	void initialize_zfi();
public:
	int filetype;
	bstring binary_contents;
	string text_contents;
	vector<file> directory_contents;
	string filename;
	zip_fileinfo zip_fi;
	// Creates an empty file
	file();
	// Creates a folder with a table of contents
	file(string dirname,vector<file> contents);
	// Creates a file with predefined contents
	file(string filename,string contents);
	// Reads a file, whether text or binary
	void read_file(string filename,bool is_binary);
	// Writes a file to the path given by the instance variable "filename"
	void write_file();
	// Creates a .zip file and returns the corresponding filename
	string make_zip();
	string get_repr(int indent);
};

#endif