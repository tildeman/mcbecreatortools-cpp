#include "make_json.h"
#include "uuid_generator.h"
#include "file_management.h"

// ***********************************
// * Note to self: don't get lost :) *
// ***********************************
namespace generatelibs{

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
	string get_ename(string identifier){
		regex regex_string("([^!@#$%^&*()+\\-=\\[\\]{};'\"\\\\|,<>\\/?.:][^!@#$%^&*()+\\-=\\[\\]{};'\"\\\\|,<>\\/?]*):([^!@#$%^&*()+\\-=\\[\\]{}:;'\"\\\\|,<>\\/?]+)");
		smatch match_string;
		bool a=regex_match(identifier,match_string,regex_string);
		if (a){
			return match_string[2];
		}
		return "";
	}
	string strippng(string filename){
		regex regex_string("(.*)\\.png");
		smatch match_string;
		bool a=regex_match(filename,match_string,regex_string);
		if (a){
			return match_string[1].str();
		}
		return "";
	}
	string to_lower(string a){
		int l=a.length();
		string b;
		for (int i=0;i<l;i++){
			if (a[i]>64&&a[i]<91) b+=a[i]+32;
			else b+=a[i];
		}
		return b;
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
	json_value genRenderControllers(string idv1){
		json_value rcobject=json_value(json_object<json_value>{});
		rcobject.val_object["format_version"]=string("1.10.0");
		rcobject.val_object["render_controllers"]=json_value(json_object<json_value>{});
		rcobject.val_object["render_controllers"].val_object[string("controller.render.")+idv1]=json_value(json_object<json_value>{});
		rcobject.val_object["render_controllers"].val_object[string("controller.render.")+idv1].val_object["geometry"]=string("geometry.default");
		rcobject.val_object["render_controllers"].val_object[string("controller.render.")+idv1].val_object["materials"]=json_value(vector<json_value>{json_object<json_value>{}});
		rcobject.val_object["render_controllers"].val_object[string("controller.render.")+idv1].val_object["materials"].val_list[0].val_object["*"]=string("material.default");
		rcobject.val_object["render_controllers"].val_object[string("controller.render.")+idv1].val_object["textures"]=json_value(vector<json_value>{});
		rcobject.val_object["render_controllers"].val_object[string("controller.render.")+idv1].val_object["textures"].val_list.push_back(string("texture.default"));
		return rcobject;
	}
	json_value genBehBasic(string identifier,bool isSpawnable,bool isSummonable,bool isExperimental){
		json_value entityobj=json_value(json_object<json_value>{});
		entityobj.val_object["minecraft:entity"]=json_value(json_object<json_value>{});
		entityobj.val_object["minecraft:entity"].val_object["description"]=json_value(json_object<json_value>{});
		entityobj.val_object["minecraft:entity"].val_object["description"].val_object["identifier"]=identifier;
		entityobj.val_object["minecraft:entity"].val_object["description"].val_object["is_spawnable"]=isSpawnable;
		entityobj.val_object["minecraft:entity"].val_object["description"].val_object["is_summonable"]=isSummonable;
		entityobj.val_object["minecraft:entity"].val_object["description"].val_object["is_experimental"]=isExperimental;
		entityobj.val_object["minecraft:entity"].val_object["components"]=json_value(json_object<json_value>{});
		entityobj.val_object["minecraft:entity"].val_object["components"].val_object["minecraft:health"]=json_value(json_object<json_value>{});
		entityobj.val_object["minecraft:entity"].val_object["components"].val_object["minecraft:health"].val_object["value"]=20;
		entityobj.val_object["minecraft:entity"].val_object["components"].val_object["minecraft:physics"]=json_value(json_object<json_value>{});
		return entityobj;
	}
public:
	file make(
		string identifier,
		file textureFile,
		file modelFile,
		bool isSpawnable,
		bool isSummonable,
		bool isExperimental,
		string spawnEggOverlay,
		string spawnEggBase,
		string material,
		string geoID,
		string select
	){
		file jszobject=file("",vector<file>{}); // It's not JS but whatever //
		string fn;
		if (verifyIdentifier(identifier)){
			if (select=="beh") jszobject.directory_contents.push_back(file("behavior_pack",vector<file>{}));
			else jszobject.directory_contents.push_back(file("resource_pack",vector<file>{}));
			if (select=="both") jszobject.directory_contents.push_back(file("behavior_pack",vector<file>{}));
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
			if (string(textureFile.filename)!=""){
				string f=strippng(textureFile.filename);
				cliententity.val_object["minecraft:client_entity"].val_object["description"].val_object["textures"]=json_value(json_object<json_value>{});
				cliententity.val_object["minecraft:client_entity"].val_object["description"].val_object["textures"].val_object["default"]="textures/entity/"+f;
				if (select!="beh") jszobject.directory_contents[0].directory_contents.push_back(file("textures",vector<file>{file("entity",vector<file>{textureFile})}));
			}
			cliententity.val_object["minecraft:client_entity"].val_object["description"].val_object["materials"]=json_value(json_object<json_value>{});
			cliententity.val_object["minecraft:client_entity"].val_object["description"].val_object["materials"].val_object["default"]=material;
			if (string(modelFile.filename)!=""){
				cliententity.val_object["minecraft:client_entity"].val_object["description"].val_object["geometry"]=json_value(json_object<json_value>{});
				cliententity.val_object["minecraft:client_entity"].val_object["description"].val_object["geometry"].val_object["default"]=to_lower(geoID);
				if (select!="beh") jszobject.directory_contents[0].directory_contents.push_back(file("models",vector<file>{file("entity",vector<file>{modelFile})}));
			}
			cliententity.val_object["minecraft:client_entity"].val_object["description"].val_object["render_controllers"]=json_value(vector<json_value>{});
			cliententity.val_object["minecraft:client_entity"].val_object["description"].val_object["render_controllers"].val_list.push_back(string("controller.render.")+get_ename(identifier));
			json_value rendercontr=json_value(json_object<json_value>{});
			if (select!="beh"&&string(modelFile.filename)!=""&&string(textureFile.filename)!=""){
				rendercontr=genRenderControllers(get_ename(identifier));
			}
			// **********************************************
			// * NOTE (for JustAsh): I'm a lazy bum, so     *
			// * I'm not bothering to fix your broken code. *
			// **********************************************
			json_value beh=genBehBasic(identifier,isSpawnable,isSummonable,isExperimental);
			if (select!="beh"){
				jszobject.directory_contents[0].directory_contents.push_back(file("manifest.json",respack.get_repr()));
				jszobject.directory_contents[0].directory_contents.push_back(file("texts",vector<file>{file("en_US.lang",string("entity")+identifier+".name="+get_ename(identifier))}));
				jszobject.directory_contents[0].directory_contents.push_back(file("entity",vector<file>{file(get_ename(identifier)+".client.json",cliententity.get_repr())}));
				jszobject.directory_contents[0].directory_contents.push_back(file("render_controllers",vector<file>{file(get_ename(identifier)+".render_controllers.json",rendercontr.get_repr())}));
			}
			if (select!="res"){
				jszobject.directory_contents[(select=="both")].directory_contents.push_back(file("manifest.json",behpack.get_repr()));
				jszobject.directory_contents[(select=="both")].directory_contents.push_back(file("entities",vector<file>{file(get_ename(identifier)+".json",beh.get_repr())}));
			}
			cout <<jszobject.filename << endl;
			if (select=="beh") fn=(get_ename(identifier)+".bp.mcpack");
			else if (select=="res") fn=(get_ename(identifier)+".rp.mcpack");
			else if (select=="both") fn=(get_ename(identifier)+".mcaddon");
		}
		jszobject.filename=fn;
		return jszobject;
	}
};

}