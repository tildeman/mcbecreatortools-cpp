#include "make_json.hpp"
#include "uuid_generator.hpp"
#include "file_management.hpp"
#include <regex>

class entity{
private:
	bool verifyIdentifier(string identifier){
		regex regex_string("([^!@#$%^&*()+\\-=\\[\\]{};'\"\\\\|,<>\\/?.:][^!@#$%^&*()+\\-=\\[\\]{};'\"\\\\|,<>\\/?]*):([^!@#$%^&*()+\\-=\\[\\]{}:;'\"\\\\|,<>\\/?]+)");
		smatch match_string;
		bool a=regex_match(identifier,match_string,regex_string);
		if (a){
			return (match_string[1].str()!="minecraft"&&match_string[1].str()!="minecon");
		}
		return false;
	}
	json_value genManifest(bool select_both){
		uuid_generator uuid;
		json_value bp=json_value(json_object<json_value>{});
		json_value rp=json_value(json_object<json_value>{});
		bp.val_object["format_version"]=2;
		rp.val_object["format_version"]=2;
		bp.val_object["header"]=json_value(json_object<json_value>{});
		rp.val_object["header"]=json_value(json_object<json_value>{});
		bp.val_object["header"].val_object["name"]=string("BP");
		rp.val_object["header"].val_object["name"]=string("RP");
		bp.val_object["header"].val_object["description"]=string("BP Description");
		rp.val_object["header"].val_object["description"]=string("RP Description");
		bp.val_object["header"].val_object["uuid"]=uuid.generate_uuid();
		rp.val_object["header"].val_object["uuid"]=uuid.generate_uuid();
		bp.val_object["header"].val_object["version"]=json_value(vector<json_value>{0,0,1});
		rp.val_object["header"].val_object["version"]=json_value(vector<json_value>{0,0,1});
		bp.val_object["header"].val_object["min_engine_version"]=json_value(vector<json_value>{1,16,0});
		rp.val_object["header"].val_object["min_engine_version"]=json_value(vector<json_value>{1,16,0});
		bp.val_object["modules"]=json_value(vector<json_value>{json_object<json_value>{}});
		rp.val_object["modules"]=json_value(vector<json_value>{json_object<json_value>{}});
		bp.val_object["modules"].val_list[0].val_object["type"]=string("data");
		rp.val_object["modules"].val_list[0].val_object["type"]=string("resources");
		bp.val_object["modules"].val_list[0].val_object["uuid"]=uuid.generate_uuid();
		rp.val_object["modules"].val_list[0].val_object["uuid"]=uuid.generate_uuid();
		bp.val_object["modules"].val_list[0].val_object["version"]=json_value(vector<json_value>{0,0,1});
		rp.val_object["modules"].val_list[0].val_object["version"]=json_value(vector<json_value>{0,0,1});
		if (select_both){
			bp.val_object["dependencies"]=json_value(vector<json_value>{json_object<json_value>{}});
			rp.val_object["dependencies"]=json_value(vector<json_value>{json_object<json_value>{}});
			bp.val_object["dependencies"].val_list[0].val_object["uuid"]=rp.val_object["header"].val_object["uuid"];
			rp.val_object["dependencies"].val_list[0].val_object["uuid"]=bp.val_object["header"].val_object["uuid"];
			bp.val_object["dependencies"].val_list[0].val_object["version"]=rp.val_object["header"].val_object["version"];
			rp.val_object["dependencies"].val_list[0].val_object["version"]=rp.val_object["header"].val_object["version"];
		}
		return json_value(json_object<json_value>{{{"rp",rp},{"bp",bp}}});
	}
public:
	json_value make(
		string identifier,
		bool isSpawnable,
		bool isSummonable,
		bool isExperimental,
		string spawnEggOverlay,
		string spawnEggBase,
		string material,
		string geoID,
		string select,
		bool baseBeh,
		string health,
		string scale,
		string collisionH,
		string collisionW,
		string typeFamily,
		bool isImmune
	){
		if (verifyIdentifier(identifier)){
			json_value manifest=genManifest(select=="both");
			json_value respack=manifest.val_object["rp"];
			json_value behpack=manifest.val_object["bp"];
			json_value cliententity=json_value(json_object<json_value>{{
				{"format_version",string("1.10.0")},
				{"minecraft:client_entity",json_value(json_object<json_value>{})}
			}});
			cliententity.val_object["minecraft:client_entity"].val_object["description"]=json_value(json_object<json_value>{});
			cliententity.val_object["minecraft:client_entity"].val_object["description"].val_object["identifier"]=identifier;
			if (isSpawnable){
				cliententity.val_object["minecraft:client_entity"].val_object["description"].val_object["spawn_egg"]=json_value(json_object<json_value>{});
				cliententity.val_object["minecraft:client_entity"].val_object["description"].val_object["spawn_egg"].val_object["overlay_color"]=spawnEggOverlay;
				cliententity.val_object["minecraft:client_entity"].val_object["description"].val_object["spawn_egg"].val_object["base_color"]=spawnEggBase;
			}
			// ***************************
			// * TO DO: Texture filename *
			// ***************************
		}
		else{
			return json_value(json_object<json_value>{});
		}
	}
};