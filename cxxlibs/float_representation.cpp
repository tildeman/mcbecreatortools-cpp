#include "make_json.hpp"

int main(){
	json_value n=json_value(json_object<json_value>{{{"test",json_value(11.44)},{"test2",json_value(string("car"))}}});
	cout << n.get_repr() << endl;
}