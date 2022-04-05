#include <string>
#include <vector>
#include <map>
#include "uuid_generator.hpp"
#include "make_json.hpp"

using namespace std;

class manifest{
public:
	string generate_nondependent(
		string pack_type="data",
		string pack_name="",
		string pack_description="",
		vector<json_value> pack_version={1,17,0},
		bool pack_use_metadata=0,
		vector<json_value> pack_authors={string("")},
		string pack_author_url="",
		bool pack_use_gametest=0,
		string pack_gametest_entry_file="modules/Main.js"
	){
		uuid_generator uuid_generator_obj;
		json_value output(
			json_object<json_value>{{
				{"format_version", json_value(2)},
				{"header", json_value(json_object<json_value>{})}
			}}
		);
		if (pack_name!=""){
			output.val_object["header"].val_object["name"]=json_value(pack_name);
		}
		if (pack_description!=""&&pack_type!="skin_pack"){
			output.val_object["header"].val_object["description"]=json_value(pack_description);
		}
		output.val_object["header"].val_object["uuid"]=uuid_generator_obj.generate_uuid();
		output.val_object["header"].val_object["version"]=json_value(vector<json_value>{1,0,0});
		output.val_object["modules"]=json_value(vector<json_value>{});
		output.val_object["modules"].val_list.push_back(json_value(json_object<json_value>{}));
		output.val_object["modules"].val_list[0].val_object["type"]=json_value(pack_type);
		if (pack_type=="scripts") output.val_object["modules"].val_list[0].val_object["type"]=json_value("data");
		output.val_object["modules"].val_list[0].val_object["uuid"]=uuid_generator_obj.generate_uuid();
		output.val_object["modules"].val_list[0].val_object["version"]=json_value(vector<json_value>{1,0,0});
		if (pack_type=="scripts"){
			output.val_object["modules"].val_list.push_back(json_value(json_object<json_value>{}));
			if (pack_description!="") output.val_object["modules"].val_list[1].val_object["description"]=json_value(pack_description);
			output.val_object["modules"].val_list[1].val_object["type"]= json_value("client_data");
			output.val_object["modules"].val_list[1].val_object["uuid"]=uuid_generator_obj.generate_uuid();
			output.val_object["modules"].val_list[1].val_object["version"]=json_value(vector<json_value>{1,0,0});
		}
		if (pack_version[0].val_int!=0&&pack_type!="skin_pack") output.val_object["header"].val_object["min_engine_version"]=pack_version;
		if (pack_use_metadata){
			output.val_object["metadata"]=json_value(json_object<json_value>{});
			if (!pack_authors.empty()) output.val_object["metadata"].val_object["authors"]=pack_authors;
			if (!pack_author_url.empty()) output.val_object["metadata"].val_object["url"]=pack_author_url;
		}
		if (pack_type!="data"&&pack_type!="scripts") pack_use_gametest=0;
		if (pack_use_gametest){
			output.val_object["dependencies"]=json_value(vector<json_value>{});
			output.val_object["dependencies"].val_list.push_back(json_value(json_object<json_value>{}));
			output.val_object["dependencies"].val_list[0].val_object["description"]=string("Minecraft module, required to use the Minecraft module");
			output.val_object["dependencies"].val_list[0].val_object["uuid"]=uuid_generator_obj.generate_uuid();
			output.val_object["dependencies"].val_list[0].val_object["version"]=vector<json_value>{0,1,0};
			output.val_object["dependencies"].val_list.push_back(json_value(json_object<json_value>{}));
			output.val_object["dependencies"].val_list[1].val_object["description"]=string("GameTest module, required to use the GameTest module");
			output.val_object["dependencies"].val_list[1].val_object["uuid"]=uuid_generator_obj.generate_uuid();
			output.val_object["dependencies"].val_list[1].val_object["version"]=vector<json_value>{0,1,0};
			if (pack_gametest_entry_file!=""){
				if (pack_type=="scripts"){
					output.val_object["modules"].val_list.push_back(json_value(json_object<json_value>{}));
					output.val_object["modules"].val_list[2].val_object["type"]=string("javascript");
					output.val_object["modules"].val_list[2].val_object["version"]=vector<json_value>{1,0,0};
					output.val_object["modules"].val_list[2].val_object["uuid"]=uuid_generator_obj.generate_uuid();
					output.val_object["modules"].val_list[2].val_object["entry"]=string("scripts/")+pack_gametest_entry_file;
				}
				else{
					output.val_object["modules"].val_list.push_back(json_value(json_object<json_value>{}));
					output.val_object["modules"].val_list[1].val_object["type"]=string("javascript");
					output.val_object["modules"].val_list[1].val_object["version"]=vector<json_value>{1,0,0};
					output.val_object["modules"].val_list[1].val_object["uuid"]=uuid_generator_obj.generate_uuid();
					output.val_object["modules"].val_list[1].val_object["entry"]=string("scripts/")+pack_gametest_entry_file;
				}
			}
		}
		return output.get_repr();
	}
	vector<string> generate_dependent(
		string bp_name="",
		string bp_description="",
		vector<json_value> bp_version={1,17,0},
		bool bp_use_scripts=0,
		bool bp_use_metadata=0,
		vector<json_value> bp_authors={string("")},
		string bp_author_url="",
		string rp_name="",
		string rp_description="",
		vector<json_value> rp_version={1,17,0},
		bool rp_use_metadata=0,
		vector<json_value> rp_authors={string("")},
		string rp_author_url="",
		bool rp_use_ui=0,
		bool bp_use_gametest=0,
		string bp_gametest_entry_file="modules/Main.js"
	){
		uuid_generator uuid_generator_obj;
		json_value behaviorpack(
			json_object<json_value>{{
				{"format_version", json_value(2)},
				{"header", json_value(json_object<json_value>{})},
				{"modules", json_value(vector<json_value>{})},
				{"dependencies", json_value(vector<json_value>{json_object<json_value>{{}}})}
			}}
		);
		if (bp_name!="") behaviorpack.val_object["header"].val_object["name"]=json_value(bp_name);
		if (bp_description!="") behaviorpack.val_object["header"].val_object["description"]=json_value(bp_description);
		behaviorpack.val_object["header"].val_object["uuid"]=json_value(uuid_generator_obj.generate_uuid());
		behaviorpack.val_object["header"].val_object["version"]=json_value(vector<json_value>{1,0,0});
		if (bp_version[0].val_int!=0) behaviorpack.val_object["header"].val_object["min_engine_version"]=bp_version;
		behaviorpack.val_object["modules"].val_list.push_back(json_value(json_object<json_value>{{}}));
		behaviorpack.val_object["modules"].val_list[0].val_object["type"]=string("data");
		behaviorpack.val_object["modules"].val_list[0].val_object["uuid"]=uuid_generator_obj.generate_uuid();
		behaviorpack.val_object["modules"].val_list[0].val_object["version"]=json_value(vector<json_value>{1,0,0});
		if (bp_use_scripts){
			behaviorpack.val_object["modules"].val_list.push_back(json_value(json_object<json_value>{{}}));
			behaviorpack.val_object["modules"].val_list[1].val_object["type"]=string("client_data");
			behaviorpack.val_object["modules"].val_list[1].val_object["uuid"]=uuid_generator_obj.generate_uuid();
			behaviorpack.val_object["modules"].val_list[1].val_object["version"]=json_value(vector<json_value>{1,0,0});
		}
		if(bp_use_metadata){
			behaviorpack.val_object["metadata"]=json_value(json_object<json_value>{});
			if (!bp_authors.empty()) behaviorpack.val_object["metadata"].val_object["authors"]=bp_authors;
			if (!bp_author_url.empty()) behaviorpack.val_object["metadata"].val_object["url"]=bp_author_url;
		}
		json_value resourcepack(
			json_object<json_value>{{
				{"format_version", json_value(2)},
				{"header", json_value(json_object<json_value>{{}})},
				{"modules", json_value(vector<json_value>{json_object<json_value>{{}}})},
				{"dependencies", json_value(vector<json_value>{json_object<json_value>{{}}})}
			}}
		);
		if (rp_name!="") resourcepack.val_object["header"].val_object["name"]=json_value(rp_name);
		if (rp_description!="") resourcepack.val_object["header"].val_object["description"]=json_value(rp_description);
		resourcepack.val_object["header"].val_object["uuid"]=json_value(uuid_generator_obj.generate_uuid());
		resourcepack.val_object["header"].val_object["version"]=json_value(vector<json_value>{1,0,0});
		if (rp_version[0].val_int!=0) resourcepack.val_object["header"].val_object["min_engine_version"]=rp_version;
		resourcepack.val_object["modules"].val_list[0].val_object["type"]=string("resources");
		resourcepack.val_object["modules"].val_list[0].val_object["uuid"]=uuid_generator_obj.generate_uuid();
		resourcepack.val_object["modules"].val_list[0].val_object["version"]=json_value(vector<json_value>{1,0,0});
		if(rp_use_metadata){
			resourcepack.val_object["metadata"]=json_value(json_object<json_value>{});
			if (!rp_authors.empty()) resourcepack.val_object["metadata"].val_object["authors"]=rp_authors;
			if (!rp_author_url.empty()) resourcepack.val_object["metadata"].val_object["url"]=rp_author_url;
		}

		behaviorpack.val_object["dependencies"].val_list[0].val_object["uuid"]=resourcepack.val_object["header"].val_object["uuid"];
		behaviorpack.val_object["dependencies"].val_list[0].val_object["version"]=resourcepack.val_object["header"].val_object["version"];
		resourcepack.val_object["dependencies"].val_list[0].val_object["uuid"]=behaviorpack.val_object["header"].val_object["uuid"];
		resourcepack.val_object["dependencies"].val_list[0].val_object["version"]=resourcepack.val_object["header"].val_object["version"];
		if (bp_use_scripts&&rp_use_ui){
			resourcepack.val_object["capabilities"]=json_value(vector<json_value>{});
			resourcepack.val_object["capabilities"].val_list.push_back(string("experimental_custom_ui"));
		}
		if (bp_use_gametest){
			behaviorpack.val_object["dependencies"].val_list[0].val_object["description"]=string("Minecraft module, required to use the Minecraft module");
			behaviorpack.val_object["dependencies"].val_list[0].val_object["uuid"]=uuid_generator_obj.generate_uuid();
			behaviorpack.val_object["dependencies"].val_list[0].val_object["version"]=json_value(vector<json_value>{0,1,0});
			behaviorpack.val_object["dependencies"].val_list.push_back(json_value(json_object<json_value>{}));
			behaviorpack.val_object["dependencies"].val_list[1].val_object["description"]=string("GameTest module, required to use the GameTest module");
			behaviorpack.val_object["dependencies"].val_list[1].val_object["uuid"]=uuid_generator_obj.generate_uuid();
			behaviorpack.val_object["dependencies"].val_list[1].val_object["version"]=json_value(vector<json_value>{0,1,0});
			if (bp_use_scripts){
				behaviorpack.val_object["modules"].val_list.push_back(json_value(json_object<json_value>{}));
				behaviorpack.val_object["modules"].val_list[2].val_object["type"]=string("javascript");
				behaviorpack.val_object["modules"].val_list[2].val_object["uuid"]=uuid_generator_obj.generate_uuid();
				behaviorpack.val_object["modules"].val_list[2].val_object["version"]=json_value(vector<json_value>{1,0,0});
				behaviorpack.val_object["modules"].val_list[2].val_object["entry"]=json_value(string("scripts/")+bp_gametest_entry_file);
			}
			else{
				behaviorpack.val_object["modules"].val_list.push_back(json_value(json_object<json_value>{}));
				behaviorpack.val_object["modules"].val_list[1].val_object["type"]=string("javascript");
				behaviorpack.val_object["modules"].val_list[1].val_object["uuid"]=uuid_generator_obj.generate_uuid();
				behaviorpack.val_object["modules"].val_list[1].val_object["version"]=json_value(vector<json_value>{1,0,0});
				behaviorpack.val_object["modules"].val_list[1].val_object["entry"]=json_value(string("scripts/")+bp_gametest_entry_file);
			}
		}
		return vector<string>{behaviorpack.get_repr(),resourcepack.get_repr()};
	}
};