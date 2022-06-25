#ifndef uuidgen
#define uuidgen

#include <random>
#include <string>

using namespace std;

class uuid_generator{
public:
	string generate_uuid();
};

#endif