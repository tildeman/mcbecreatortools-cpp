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

template <typename jso> class json_object{
public:
	vector<pair<string,jso>> object_pair;
	json_object();
	json_object(vector<pair<string,jso>> a);
	jso& operator[](string s);
};

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
	json_value();
	json_value(int n);
	json_value(string s);
	json_value(vector<json_value> l);
	json_value(json_object<json_value> o);
	json_value(bool n);
	json_value(double d);
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