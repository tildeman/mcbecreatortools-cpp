#include "obfuscator.hpp"
#include "file_management.hpp"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	obfuscator a;
	file json_file;
	json_file.read_file("obfuscator_test.json",0);
	string s=json_file.text_contents;
	cout << "Result:\n" << a.obfuscateMain(s,0) << "\nResult (minified): " << a.obfuscateMain(s,1) << "\n";
	return 0;
}
