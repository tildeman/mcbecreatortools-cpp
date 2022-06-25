#include "uuid_generator.h"

string uuid_generator::generate_uuid(){
	string generated_uuid;
	int uuid_v4_pattern[] = {8, 4, 4, 4, 12};
	char uuid[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
	random_device rd;
	mt19937 generator(rd());
	uniform_int_distribution<> pick_hex(0,15);
	for (int index=0;index<5;index++){
		for (int counter=1;counter<=uuid_v4_pattern[index];counter++){
			generated_uuid+=uuid[pick_hex(generator)];
		}
		if (index<4) generated_uuid+='-';
	}
	return generated_uuid;
}