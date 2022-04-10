#include "file_management.hpp"

int main(){
	file r[]={file("sh","iet"),file("muzyka","aasasas")};
	file s[]={file("a","moi"),file("fldr",r,2),file("b","moje")};
	file t[]={file("ssss",s,3),file("must","fffff")};
	file a("think",t,2);
	printf("%s",a.get_repr());

	file b;
	b.read_file("manifest",1);
	printf("%s\n",b.filename);
}