#include <cstdio>
#include <cstdlib>
#include <cstring>

struct binfile{
	const char* filename;
	int length;
	unsigned char* contents;
};

binfile read_file(const char* filename){
	FILE* f=fopen(filename,"rb");
	binfile b;
	fseek(f,sizeof(unsigned char),SEEK_END);
	b.length=ftell(f)-1;
	fseek(f,sizeof(unsigned char)*0L,SEEK_SET);
	b.contents=(unsigned char*) malloc(b.length*sizeof(unsigned char));
	fread(b.contents,sizeof *b.contents,b.length,f);
	return b;
}
void write_file(binfile b){
	FILE* w=fopen(b.filename,"wb");
	fwrite(b.contents,sizeof *b.contents,b.length,w);
	fclose(w);
}

class file{
public:
	bool is_binary;
	unsigned char* binary_contents;
	char* text_contents;
	const char* filename;
	int length;
	file(){}
	file(const char* filename,const char* contents){
		this->filename=filename;
		this->is_binary=0;
		this->text_contents=(char*) contents;
		this->length=strlen(contents);
	}
	void read_file(const char* filename,bool is_binary){
		this->is_binary=is_binary;
		if (is_binary){
			FILE* f=fopen(filename,"rb");
			this->filename=filename;
			fseek(f,sizeof(unsigned char),SEEK_END);
			this->length=ftell(f)-1;
			fseek(f,sizeof(unsigned char)*0L,SEEK_SET);
			this->binary_contents=(unsigned char*) malloc(this->length*sizeof(unsigned char));
			fread(this->binary_contents,sizeof *this->binary_contents,this->length,f);
		}
		else{
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
		if (this->is_binary){
			w=fopen(this->filename,"wb");
			fwrite(this->binary_contents,sizeof *this->binary_contents,this->length,w);
		}
		else{
			w=fopen(this->filename,"w");
			fwrite(this->text_contents,sizeof *this->text_contents,this->length,w);
		}
		fclose(w);
	}
};

// **********************
// * TO DO: Directories *
// **********************