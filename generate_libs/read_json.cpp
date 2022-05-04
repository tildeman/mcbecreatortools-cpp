#include "make_json.hpp"
#include "file_management.hpp"
using namespace std;

int main(){
	file f;
	f.read_file("obfuscator_test.json",0);
	json_value v=json_value::parse(f.text_contents);
	return 0;
}