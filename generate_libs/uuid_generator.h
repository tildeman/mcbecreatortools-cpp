#ifndef uuidgen
#define uuidgen

#include <random>
#include <string>

using namespace std;

class uuid_generator{
public:
	/*
	Generates a random string of 32 alphanumeric characters and four hyphens
	This is not and never will be a valid UUID, of any version, in any variant.
	See implementation on https://tools.pixelpoly.co/assets/js/lib/uuid_generator_class.js.
	*/
	string generate_uuid();
};

#endif