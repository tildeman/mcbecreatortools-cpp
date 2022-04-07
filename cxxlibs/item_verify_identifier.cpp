#include "item.hpp"
#include <cassert>

int main(){
	item a;
	bool test_one=a.verifyIdentifier("custom:item");
	assert(test_one);
	bool test_two=a.verifyIdentifier(".shit:just");
	assert(!test_two);
	bool test_three=a.verifyIdentifier("happened-and:this");
	assert(!test_three);
	bool test_four=a.verifyIdentifier("is.what:i:call");
	assert(test_four);
	bool test_five=a.verifyIdentifier(":ok");
	assert(!test_five);
}