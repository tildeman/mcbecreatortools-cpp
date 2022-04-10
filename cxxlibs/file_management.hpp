#include <cstdio>
#include <cstdlib>
#include <cstring>

// * Lookup table for file types *
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
	const char* truncate_slashes(const char* strink){
		int l=strlen(strink),i;
		for (i=l-1;i>-1;i--){
			if (strink[i]=='/'||strink[i]=='\\') return strink+i+1;
		}
		return strink;
	}
public:
	int filetype;
	unsigned char* binary_contents;
	char* text_contents;
	file* directory_contents;
	const char* filename;
	int length;
	file(){
		this->filetype=1;
		this->filename="";
	}
	file(const char* dirname,file* contents,int length){
		this->filetype=2;
		this->filename=dirname;
		this->directory_contents=contents;
		this->length=length;
	}
	file(const char* filename,const char* contents){
		this->filename=filename;
		this->filetype=1;
		this->text_contents=(char*) contents;
		this->length=strlen(contents);
	}
	void read_file(const char* filename,bool is_binary){
		if (is_binary){
			this->filetype=0;
			FILE* f=fopen(filename,"rb");
			this->filename=this->truncate_slashes(filename);
			fseek(f,sizeof(unsigned char),SEEK_END);
			this->length=ftell(f)-1;
			fseek(f,sizeof(unsigned char)*0L,SEEK_SET);
			this->binary_contents=(unsigned char*) malloc(this->length*sizeof(unsigned char));
			fread(this->binary_contents,sizeof *this->binary_contents,this->length,f);
		}
		else{
			this->filetype=1;
			FILE* f=fopen(filename,"rb");
			this->filename=filename;
			fseek(f,sizeof(char),SEEK_END);
			this->length=ftell(f)-1;
			fseek(f,sizeof(char)*0L,SEEK_SET);
			this->text_contents=(char*) malloc(this->length*sizeof(char));
			fread(this->text_contents,sizeof *this->text_contents,this->length,f);
			this->text_contents[this->length]=0;
		}
	}
	void write_file(){
		FILE* w;
		if (this->filetype==0){
			w=fopen(this->filename,"wb");
			fwrite(this->binary_contents,sizeof *this->binary_contents,this->length,w);
		}
		else if (this->filetype==1){
			w=fopen(this->filename,"w");
			fwrite(this->text_contents,sizeof *this->text_contents,this->length,w);
		}
		fclose(w);
	}
	char* get_repr(int indent=0){
		int i;
		char* s=(char*) malloc(30000);
		s[0]=0;
		for (i=1;i<indent;i++) strcat(s,"| ");
		if (indent) strcat(s,"|-");
		strcat(s,this->filename);
		strcat(s,"\n");
		if (this->filetype==2){
			for (i=0;i<this->length;i++){
				strcat(s,this->directory_contents[i].get_repr(indent+1));
			}
		}
		return s;
	}
};