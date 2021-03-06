#include "make_json.h"
#include "uuid_generator.h"
#include "file_management.h"

namespace generatelibs{

class obfuscator{
public:
	int decode_utf8(string embestring){
		// Assume whatever string this function processes is valid UTF8
		int l=embestring.length(),i=0;
		unsigned char ccc;
		ccc=embestring[0];
		if (ccc>>5==6){
			i=((unsigned char)(embestring[0])%32)*64+((unsigned char)(embestring[1])%64);
		}
		else if (ccc>>4==14){
			i=((unsigned char)(embestring[0])%16)*4096+((unsigned char)(embestring[1])%64)*64+((unsigned char)(embestring[2])%64);
		}
		else if (ccc>>3==30){
			i=((unsigned char)(embestring[0])%8)*262144+((unsigned char)(embestring[1])%64)*4096+((unsigned char)(embestring[2])%64)*64+((unsigned char)(embestring[3])%64);
		}
		else{
			i=embestring[0];
		}
		return i;
	}
	string unicodeEscape(string input_string){
		char escaped_character[10];
		string output_string;
		int string_length=input_string.length(),iterator,cc;
		for (iterator=0;iterator<string_length;iterator++){
			if (((unsigned char)input_string[iterator])>>5==6){
				cc=decode_utf8(input_string.substr(iterator,2));
				iterator+=1;
			}
			else if (((unsigned char)input_string[iterator])>>4==14){
				cc=decode_utf8(input_string.substr(iterator,3));
				iterator+=2;
			}
			else if (((unsigned char)input_string[iterator])>>3==30){
				cc=decode_utf8(input_string.substr(iterator,4));
				iterator+=3;
			}
			else{
				cc=decode_utf8(input_string.substr(iterator,1));
			}
			sprintf(escaped_character,"\\u%04x",cc);
			output_string+=escaped_character;
		}
		return output_string;
	}
	string minify(string input_string){
		string output_string;
		char current_char;
		int iterator=0,input_length=input_string.length(),old_pos;
		while (iterator<input_length){
			current_char=input_string[iterator];
			switch (current_char){
				case '\t':
				case '\r':
				case '\n':
				case ' ':
					iterator++;
					break;
				case '"':
					old_pos=iterator;
					while (iterator<input_length){
						current_char=input_string[++iterator];
						if (current_char=='\\') iterator++;
						else if (current_char=='"') break;
					}
					if (input_string[iterator]=='"'){
						output_string+=input_string.substr(old_pos,++iterator-old_pos);
						break;
					}
					throw "Unterminated string.";
				default:
					output_string+=current_char;
					iterator++;
			}
		}
		return output_string;
	}
	string obfuscateMain(string input_string, bool do_minify){
		regex regex_string ("\"([^\"]*)\"");
		string output_string="";
		smatch match_string;
		while (regex_search(input_string,match_string,regex_string)){
			output_string+=match_string.prefix();
			output_string+="\"";
			output_string+=this->unicodeEscape(match_string[1]);
			output_string+="\"";
			input_string=match_string.suffix();
		}
		output_string+=input_string;
		if (do_minify) output_string=this->minify(output_string);
		return output_string;
	}
};

}