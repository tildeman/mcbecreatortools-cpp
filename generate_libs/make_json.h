#ifndef mkjson
#define mkjson

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <regex>
#include <cmath>

using namespace std;

// Placeholder type for the json_object class
template <typename jso> class json_object{
public:
	vector<pair<string,jso>> object_pair;
	json_object();
	json_object(vector<pair<string,jso>> a);
	jso& operator[](string s);
};

// Represents a value in JSON
class json_value{
private:
	string indent_json(string s);
	static string strip(string s);
	static int hex_to_int(string s);
	//Kept me up for a whole night
	static string unescapify(string s);
public:
	int val_type;
	int val_int;
	double val_float;
	string val_string;
	vector<json_value> val_list;
	json_object<json_value> val_object;
	// An integer with value 0
	json_value();
	// An integer with value "n"
	json_value(int n);
	// A string with value "s"
	json_value(string s);
	// A list "l" of values
	json_value(vector<json_value> l);
	// An object "o" of values
	json_value(json_object<json_value> o);
	// A boolean with value "n". Represents "null" when val_int is modified to -1
	json_value(bool n);
	// A float with value "d"
	json_value(double d);
	/*
	A JSON output mini-function made by neither JustAsh nor Zarkmend.
	Refer to RFC 7159 if you want to know more about what this is.
	I mean it runs terribly slow on large files but it gets the job done.
	(as long as Discord doesn't chuck in some impossibly long request)
	*/
	string get_repr();
	/*
	A JSON parsing mini-function made by neither JustAsh nor Zarkmend.
	Refer to RFC 7159 if you want to know more about what this is.
	I mean it doesn't work on huge numbers but it gets the job done.
	(as long as Discord doesn't chuck in some impossibly large number)
	*/
	static json_value parse(string s);
};

#endif