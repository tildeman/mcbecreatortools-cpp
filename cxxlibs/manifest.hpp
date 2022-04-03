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
		uuid_generator uuidgen1;
		json_value output(
			map<string,json_value>{
				{"format_version", json_value(2)},
				{"header", json_value(map<string,json_value>{})}
			}
		);
		if (pack_name!=""){
			output.val_object["header"].val_object["name"]=json_value(pack_name);
		}
		if (pack_description!=""&&pack_type!="skin_pack"){
			output.val_object["header"].val_object["description"]=json_value(pack_description);
		}
		output.val_object["header"].val_object["uuid"]=uuidgen1.generate_uuid();
		output.val_object["header"].val_object["version"]=json_value(vector<json_value>{1,0,0});
		output.val_object["modules"]=json_value(vector<json_value>{});
		output.val_object["modules"].val_list.push_back(json_value(map<string,json_value>{}));
		output.val_object["modules"].val_list[0].val_object["type"]=json_value(pack_type);
		if (pack_type=="scripts") output.val_object["modules"].val_list[0].val_object["type"]=json_value("data");
		output.val_object["modules"].val_list[0].val_object["uuid"]=uuidgen1.generate_uuid();
		output.val_object["modules"].val_list[0].val_object["version"]=json_value(vector<json_value>{1,0,0});
		if (pack_type=="scripts"){
			output.val_object["modules"].val_list.push_back(json_value(map<string,json_value>{}));
			if (pack_description!="") output.val_object["modules"].val_list[1].val_object["description"]=json_value(pack_description);
			output.val_object["modules"].val_list[1].val_object["type"]= json_value("client_data");
			output.val_object["modules"].val_list[1].val_object["uuid"]=uuidgen1.generate_uuid();
			output.val_object["modules"].val_list[1].val_object["version"]=json_value(vector<json_value>{1,0,0});
		}
		if (pack_version[0].val_int!=0&&pack_type!="skin_pack") output.val_object["header"].val_object["min_engine_version"]=pack_version;
		if (pack_use_metadata){
			output.val_object["metadata"]=json_value(map<string,json_value>{});
			if (!pack_authors.empty()) output.val_object["metadata"].val_object["authors"]=pack_authors;
			if (!pack_author_url.empty()) output.val_object["metadata"].val_object["url"]=pack_author_url;
		}
		if (pack_type!="data"&&pack_type!="scripts") pack_use_gametest=0;
		if (pack_use_gametest){
			output.val_object["dependencies"]=json_value(vector<json_value>{});
			output.val_object["dependencies"].val_list.push_back(json_value(map<string,json_value>{}));
			output.val_object["dependencies"].val_list[0].val_object["description"]=string("Minecraft module, required to use the Minecraft module");
			output.val_object["dependencies"].val_list[0].val_object["uuid"]=uuidgen1.generate_uuid();
			output.val_object["dependencies"].val_list[0].val_object["version"]=vector<json_value>{0,1,0};
			output.val_object["dependencies"].val_list.push_back(json_value(map<string,json_value>{}));
			output.val_object["dependencies"].val_list[1].val_object["description"]=string("GameTest module, required to use the GameTest module");
			output.val_object["dependencies"].val_list[1].val_object["uuid"]=uuidgen1.generate_uuid();
			output.val_object["dependencies"].val_list[1].val_object["version"]=vector<json_value>{0,1,0};
			if (pack_gametest_entry_file!=""){
				if (pack_type=="scripts"){
					output.val_object["modules"].val_list.push_back(json_value(map<string,json_value>{}));
					output.val_object["modules"].val_list[2].val_object["type"]=string("javascript");
					output.val_object["modules"].val_list[2].val_object["version"]=vector<json_value>{1,0,0};
					output.val_object["modules"].val_list[2].val_object["uuid"]=uuidgen1.generate_uuid();
					output.val_object["modules"].val_list[2].val_object["entry"]=string("scripts/")+pack_gametest_entry_file;
				}
				else{
					output.val_object["modules"].val_list.push_back(json_value(map<string,json_value>{}));
					output.val_object["modules"].val_list[1].val_object["type"]=string("javascript");
					output.val_object["modules"].val_list[1].val_object["version"]=vector<json_value>{1,0,0};
					output.val_object["modules"].val_list[1].val_object["uuid"]=uuidgen1.generate_uuid();
					output.val_object["modules"].val_list[1].val_object["entry"]=string("scripts/")+pack_gametest_entry_file;
				}
			}
		}
		return output.get_repr();
	}
};