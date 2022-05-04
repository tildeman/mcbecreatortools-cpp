#include "entity.hpp"

int main(){
	entity a;
	file tf,mf;
	tf.read_file("/mnt/ltinh/grumpykenyan.png",1);
	mf.read_file("obfuscator_test.json",0);
	file b=a.make("ss:aa",tf,mf,1,1,0,"#7b3d3d","#ffa8a8","entity_alphatest","","both");
	string c=b.get_repr();
	cout << c;
}