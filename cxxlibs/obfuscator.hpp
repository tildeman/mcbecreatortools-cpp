#include <cstdio>
#include <string>
#include <regex>

using namespace std;

class obfuscator{
public:
	string unicodeEscape(string input_string){
		char escaped_character[7];
		string output_string;
		int string_length=input_string.length(),iterator;
		for (iterator=0;iterator<string_length;iterator++){
			sprintf(escaped_character,"\\u%04x",input_string[iterator]);
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