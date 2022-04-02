#include "obfuscator.hpp"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	obfuscator a;
	FILE* json_file=fopen("obfuscator_test.json","rb");
	fseek(json_file,sizeof(char),SEEK_END);
	int l=ftell(json_file);
	char s[l];
	fseek(json_file,sizeof(char)*0L,SEEK_SET);
	fread(s,sizeof *s,l-1,json_file);
	s[l-1]=0;
	cout << "Result:\n" << a.obfuscateMain(s,0) << "\nResult (minified): " << a.obfuscateMain(s,1) << "\n";
	return 0;
}
