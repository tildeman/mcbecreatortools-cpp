#include "file_management.hpp"
#include <iostream>
using namespace std;

int main(){
	file a("think",{
		file("ssss",vector<file>{
			file("a","moi"),
			file("fldr",vector<file>{
				file("sh","iet"),
				file("muzyka","aasasas")
			}),
			file("b","moje")
		}),
		file("must","fffff")
	});
	cout << a.get_repr();

	file b;
	b.read_file("/mnt/creatortools/entity.js",0);
	b.write_file();
	cout << b.filename << '\n';
}