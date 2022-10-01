#include "file_management.h"

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


// Parse filenames in zip using UTF-8 with this string
const unsigned char exfl[]={
	// Tag
	0x75, 0x78,
	// Length
	0x0B, 0x00,
	// Fixed string with unknown properties
	0x01, 0x04, 0xE8, 0x03, 0x00, 0x00, 0x04, 0xE8, 0x03, 0x00, 0x00
};


string file::truncate_slashes(string strink){
	regex regex_string(".*[\\\\\\/](.+)");
	smatch match_string;
	bool a=regex_match(strink,match_string,regex_string);
	if (a){
		return match_string[1];
	}
	return strink;
}
file::file(){
	this->filetype=1;
	this->filename="";
}
file::file(string dirname,vector<file> contents){
	this->filetype=2;
	this->filename=dirname;
	this->directory_contents=contents;
}
file::file(string filename,string contents){
	this->filename=filename;
	this->filetype=1;
	this->text_contents=contents;
}
void file::initialize_zfi(){
	time_t unixtime=time(NULL);
	struct tm* current_time=localtime(&unixtime);

	this->zip_fi.dosDate=0;
	this->zip_fi.external_fa=0;
	this->zip_fi.internal_fa=0;
	this->zip_fi.tmz_date.tm_sec=current_time->tm_sec;
	this->zip_fi.tmz_date.tm_min=current_time->tm_min;
	this->zip_fi.tmz_date.tm_hour=current_time->tm_hour;
	this->zip_fi.tmz_date.tm_mday=current_time->tm_mday;
	this->zip_fi.tmz_date.tm_mon=current_time->tm_mon;
	this->zip_fi.tmz_date.tm_year=current_time->tm_year;
}
void file::read_file(string filename,bool is_binary){
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
void file::write_file(){
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

void file::add_files_to_zip(string subdirectory,zipFile* zfptr){
	switch (this->filetype){
		case 0:
			zipOpenNewFileInZip4_64(*zfptr,subdirectory.c_str(),&(this->zip_fi),exfl,15,exfl,15,NULL,0,Z_DEFAULT_COMPRESSION,0,-MAX_WBITS,DEF_MEM_LEVEL,Z_DEFAULT_STRATEGY,NULL,0,798,2048u,1);
			zipWriteInFileInZip(*zfptr,this->binary_contents.c_str(),this->binary_contents.length());
			zipCloseFileInZip(*zfptr);
		case 1:
			zipOpenNewFileInZip4_64(*zfptr,subdirectory.c_str(),&(this->zip_fi),exfl,15,exfl,15,NULL,0,Z_DEFAULT_COMPRESSION,0,-MAX_WBITS,DEF_MEM_LEVEL,Z_DEFAULT_STRATEGY,NULL,0,798,2048u,1);
			zipWriteInFileInZip(*zfptr,this->text_contents.c_str(),this->text_contents.length());
			zipCloseFileInZip(*zfptr);
		case 2:
			for (file i:this->directory_contents){
				const char* dl="/";
				i.add_files_to_zip(subdirectory+(dl+(subdirectory.length()==0))+i.filename,zfptr);
			}
		default:
			break;
	}
}

string file::make_zip(){
	zip_fileinfo zfi;
	uuid_generator u;
	this->initialize_zfi();
	filename=string("tmp/")+u.generate_uuid()+".zip";
	zipFile zfp=zipOpen64(filename.c_str(),0);
	add_files_to_zip("",&zfp);
	zipClose(zfp,NULL);
	return filename;
}
string file::get_repr(int indent){
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