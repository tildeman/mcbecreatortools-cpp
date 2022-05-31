#include <generate_libs.cpp>

using namespace std;
using namespace generatelibs;

int main(){
	// test for entity.hpp
	entity entity_a;
	file entity_tf,entity_mf;
	entity_tf.read_file("resources/Ę.png",1);
	entity_mf.read_file("resources/obfuscator_test.json",0);
	file entity_b=entity_a.make("ss:aa",entity_tf,entity_mf,1,1,0,"#7b3d3d","#ffa8a8","entity_alphatest","","both");
	string entity_c=entity_b.get_repr();
	std::cout << entity_c << endl;
	// test for file_management.hpp
	file file_a("think",{
		file("ssss",vector<file>{
			file("a","moi"),
			file("fldr",vector<file>{
				file("sh","iet"),
				file("muzyka","aasasas")
			}),
			file("b","móc")
		}),
		file("must","fffff")
	});
	cout << file_a.get_repr() << endl;
	//test for item.hpp

	file tf;
	tf.read_file("/mnt/ltinh/młośpąc.png",1);
	item item_a;
	cout << item_a.writeItem(
		"1.17.0",
		"test:test1",
		"Equipment",
		false,
		"textures/items/test1",
		"Test #1",
		0,
		true,
		"eat",
		false,
		3.0,
		false,
		true,
		true,
		true,
		"itemGroup.name.crop",
		false,
		-1.0,
		"low",
		false,
		"",
		false,
		true,
		true,
		"slot.armor.head",
		12,
		false,
		"",
		-1.0,
		3,
		false,
		"",
		"",
		true,
		"d",
		vector<json_value>{string("a"),string("b"),string("c")},
		vector<json_value>{string("d"),string("e"),string("f")},
		false,
		"none",
		-1,
		true,
		2.0,
		true,
		false,
		true,
		false,
		"sss",
		false,
		true,
		-1,
		true,
		-1,
		true,
		true,
		true,
		false,
		"",
		-1.0,
		true,
		"magenta",
		false,
		false,
		-1.0,
		false,
		0.5,
		-1.0,
		true,
		"słuchać",
		1,
		4,
		file("",""),
		true
	).get_repr() << endl;
	cout << item_a.writeItem(
		"1.16.100",
		"test:test2",
		"Items",
		true,
		"textures/items/test2",
		"Test #2",
		16,
		false,
		"none",
		true,
		0.0,
		true,
		false,
		false,
		false,
		"none",
		true,
		2.43,
		"normal",
		false,
		"eater",
		true,
		false,
		false,
		"",
		-1,
		true,
		"sab",
		3.3,
		-1,
		true,
		"arb",
		true,
		false,
		"",
		vector<json_value>{},
		vector<json_value>{},
		true,
		"armor_legs",
		-2,
		false,
		0.0,
		false,
		false,
		false,
		false,
		"",
		false,
		false,
		2,
		false,
		3,
		false,
		false,
		false,
		true,
		"dd",
		5.3,
		false,
		"",
		true,
		true,
		2.0,
		true,
		-1.0,
		3.4,
		false,
		"",
		-1,
		-1,
		tf,
		false
	).get_repr() << endl;
	// tests for make_json.hpp
	json_value float_representation_n=json_value(json_object<json_value>{{{"test",json_value(11.44)},{"test2",json_value(string("car"))}}});
	cout << float_representation_n.get_repr() << endl;
	json_object<json_value> make_json_o=vector<pair<string,json_value>>({{"a",1},{"c",2}});
	make_json_o["c"]=3;
	make_json_o["b"]=9;
	json_value make_json_v=json_value(vector<json_value>{json_value(make_json_o),json_value(false),json_value(85.47)});
	cout << make_json_v.get_repr() << endl;
	return 0;
	// test for manifest.hpp
	manifest manifest_n;
	cout << "Non-dependent:\n" << manifest_n.generate_nondependent(
		"data",
		"abv",
		"sontdfdfdf",
		{1,17,0},
		true,
		{string("aa"),string("bb"),string("cc")},
		"http://localhost",
		1
	) << endl;
	vector<string> manifest_r=manifest_n.generate_dependent(
		"abv",
		"d🤩ixneuf",
		vector<json_value> {1,17,0},
		true,
		true,
		vector<json_value> {string("aiw"),string("aed"),string("ddd")},
		"http://localhost",
		"rpbv",
		"dikneuph",
		vector<json_value> {1,17,0},
		true,
		vector<json_value> {string("rpw"),string("ddd"),string("wwddd")},
		"http://192.168.32.1",
		true,
		true);
	cout << "Dependent: \n" << manifest_r[0] << endl << manifest_r[1] << endl;
	obfuscator obfuscator_a;
	file obfuscator_json_file;
	obfuscator_json_file.read_file("resources/obfuscator_test.json",0);
	string obfuscator_s=obfuscator_json_file.text_contents;
	cout << "Result:\n" << obfuscator_a.obfuscateMain(obfuscator_s,0) << "\nResult (minified): " << obfuscator_a.obfuscateMain(obfuscator_s,1) << "\n";
	// test for uuid_generator.hpp
	uuid_generator uuid_generator_a;
	cout << uuid_generator_a.generate_uuid() << endl;
	return 0;
}