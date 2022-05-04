#include "make_json.hpp"
#include "uuid_generator.hpp"
#include "file_management.hpp"
#include <regex>


class item{
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
	string to_lower(string a){
		int l=a.length();
		string b;
		for (int i=0;i<l;i++){
			if (a[i]>64&&a[i]<91) b+=a[i]-32;
			else b+=a[i];
		}
		return b;
	}
	string get_iname(string identifier){
		regex regex_string("([^!@#$%^&*()+\\-=\\[\\]{};'\"\\\\|,<>\\/?.:][^!@#$%^&*()+\\-=\\[\\]{};'\"\\\\|,<>\\/?]*):([^!@#$%^&*()+\\-=\\[\\]{}:;'\"\\\\|,<>\\/?]+)");
		smatch match_string;
		bool a=regex_match(identifier,match_string,regex_string);
		if (a){
			return match_string[2];
		}
		return "";
	}
	json_value genManifest(){
		uuid_generator uuid;
		json_value bp=json_value(json_object<json_value>{});
		json_value rp=json_value(json_object<json_value>{});
		bp.val_object["format_version"]=2;
		rp.val_object["format_version"]=2;
		bp.val_object["header"]=json_value(json_object<json_value>{});
		rp.val_object["header"]=json_value(json_object<json_value>{});
		bp.val_object["header"].val_object["name"]=string("Item behaviorpack");
		rp.val_object["header"].val_object["name"]=string("Item resourcepack");
		bp.val_object["header"].val_object["description"]=string("Behavior pack required for the item to work, generated not using https://tools.pixelpoly.co/item-generator");
		rp.val_object["header"].val_object["description"]=string("Resource pack required for the item to work, generated not using https://tools.pixelpoly.co/item-generator");
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
		bp.val_object["dependencies"]=json_value(vector<json_value>{json_object<json_value>{}});
		rp.val_object["dependencies"]=json_value(vector<json_value>{json_object<json_value>{}});
		bp.val_object["dependencies"].val_list[0].val_object["uuid"]=rp.val_object["header"].val_object["uuid"];
		rp.val_object["dependencies"].val_list[0].val_object["uuid"]=bp.val_object["header"].val_object["uuid"];
		bp.val_object["dependencies"].val_list[0].val_object["version"]=rp.val_object["header"].val_object["version"];
		rp.val_object["dependencies"].val_list[0].val_object["version"]=rp.val_object["header"].val_object["version"];
		return json_value(json_object<json_value>{{{"rp",rp},{"bp",bp}}});
	}
	string truncate_slashes(string strink){
		regex regex_string(".*[\\\\\\/](.+)");
		smatch match_string;
		bool a=regex_match(strink,match_string,regex_string);
		if (a){
			return match_string[1];
		}
		return strink;
	}
public:
	file writeItem(
		string formatVersion="1.16.100",
		string identifier="custom:item",
		string category="Items",
		bool isExp=0,
		string icon="textures/items/my_item",
		string displayName="",
		int maxStackSize=0,
		bool useAnimCheckbox=0,
		string useAnim="none",
		bool foil=0,
		double useDuration=32,
		bool stackedData=0,
		bool handEquipped=0,
		bool destroyInC=1,
		bool ccategoryCheckbox=0,
		string ccategory="none",
		bool foodCheckbox=0,
		double foodNutr=-1,
		string foodSatu="low",
		bool foodCanA=0,
		string foodConvert="",
		bool isexplod=1,
		bool allowOffHand=1,
		bool wearableCheckbox=0,
		string wearableSlot="none",
		int armorProtection=-1,
		bool cooldownCheckbox=0,
		string cooldownCategory="",
		double cooldownDuration=-1,
		int damage=-1,
		bool blockPlacerCheckbox=0,
		string blockPlacerBlock="",
		bool blockPlacerDes=0,
		bool entityPlacerCheckbox=0,
		string entityPlacerEntity="",
		vector<json_value> entityPlacerUseon={},
		vector<json_value> entityPlacerDison={},
		bool enchantableCheckbox=0,
		string enchantableSlot="none",
		int enchantableValue=-1,
		bool shooterCheckbox=0,
		double shooterMaxDraw=0,
		bool shooterCharge=0,
		bool shooterScale=0,
		bool shooterAmmoCheckbox=0,
		bool shooterAmmoInven=0,
		string shooterAmmoItem="",
		bool shooterAmmoHand=0,
		bool shooterAmmoCreative=0,
		int fertilizer=-1,
		bool ignPerms=0,
		int miningSpeed=-1,
		bool liquidClipped=0,
		bool shouldDespawn=1,
		bool mirroredArt=0,
		bool projectileCheckbox=0,
		string projectileEntity="",
		double projectilePower=-1,
		bool dyeCheckbox=0,
		string dyePowder="silver",
		bool throwableCheckbox=0,
		bool throwableSwing=0,
		double throwableDraw=-1,
		bool throwablePower=0,
		double knockbackResis=-1,
		double fuel=-1,
		bool recordCheckbox=0,
		string recordSound="",
		int recordDuration=-1,
		int recordSignal=-1,
		file itemIcon=file("",""),
		bool enable_itematlas=0
	){
		json_value item=json_value(json_object<json_value>{});
		item.val_object["format_version"]=formatVersion;
		item.val_object["minecraft:item"]=json_value(json_object<json_value>{});
		item.val_object["minecraft:item"].val_object["description"]=json_value(json_object<json_value>{});
		if (this->verifyIdentifier(identifier)){
			item.val_object["minecraft:item"].val_object["description"].val_object["identifier"]=to_lower(identifier);
		}
		item.val_object["minecraft:item"].val_object["description"].val_object["category"]=category;
		if (isExp){
			item.val_object["minecraft:item"].val_object["description"].val_object["is_experimental"]=isExp;
		}
		item.val_object["minecraft:item"].val_object["components"]=json_value(json_object<json_value>{});
		if (icon!=""&&verifyIdentifier(identifier)){
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:icon"]=json_value(json_object<json_value>{});
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:icon"].val_object["texture"]=to_lower(get_iname(identifier)+".texture");
		}
		json_value itemAtlas=json_value(json_object<json_value>{});
		if (enable_itematlas&&icon!=""){
			itemAtlas.val_object["resource_pack_name"]=string("vanilla");
			itemAtlas.val_object["texture_name"]=string("atlas.items");
			itemAtlas.val_object["texture_data"]=json_value(json_object<json_value>{});
			if (this->verifyIdentifier(identifier)){
				itemAtlas.val_object["texture_data"].val_object[get_iname(identifier)+".texture"]=json_value(json_object<json_value>{});
				itemAtlas.val_object["texture_data"].val_object[get_iname(identifier)+".texture"].val_object["textures"]=icon;
			}
		}
		if (displayName!=""){
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:display_name"]=json_value(json_object<json_value>{});
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:display_name"].val_object["value"]=displayName;
		}
		if (maxStackSize>=1 && maxStackSize<=64){
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:max_stack_size"]=maxStackSize;
		}
		if (foil){
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:foil"]=foil;
		}
		if (useAnimCheckbox&&useAnim!="none"){
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:use_animation"]=useAnim;
		}
		if (useDuration){
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:use_duration"]=useDuration;
		}
		if (stackedData){
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:stacked_by_data"]=stackedData;
		}
		if (handEquipped){
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:hand_equipped"]=handEquipped;
		}
		if (!destroyInC){
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:can_destroy_in_creative"]=destroyInC;
		}
		if (ccategoryCheckbox){
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:creative_category"]=json_value(json_object<json_value>{});
			if (ccategory!="none"){
				item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:creative_category"].val_object["parent"]=ccategory;
			}
		}
		if (foodCheckbox){
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:food"]=json_value(json_object<json_value>{});
			if (foodNutr>=0)item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:food"].val_object["nutrition"]=foodNutr;
			if (foodSatu!="") item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:food"].val_object["saturation_modifier"]=foodSatu;
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:food"].val_object["can_always_eat"]=foodCanA;
			if (foodConvert!="") item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:food"].val_object["using_converts_to"]=foodConvert;
		}
		if (!isexplod){
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:explodable"]=isexplod;
		}
		if (!allowOffHand){
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:allow_off_hand"]=allowOffHand;
		}
		if (wearableCheckbox){
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:wearable"]=json_value(json_object<json_value>{});
			if (wearableSlot!="")item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:wearable"].val_object["slot"]=wearableSlot;
		}
		if (armorProtection>=0&&armorProtection<=20){
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:armor"]=json_value(json_object<json_value>{});
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:armor"].val_object["protection"]=armorProtection;
		}
		if (cooldownCheckbox){
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:cooldown"]=json_value(json_object<json_value>{});
			if (cooldownCategory!="") item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:cooldown"].val_object["category"]=cooldownCategory;
			if (cooldownDuration>=0) item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:cooldown"].val_object["duration"]=cooldownDuration;
		}
		if (damage>=0) item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:damage"]=damage;
		if (blockPlacerCheckbox){
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:block_placer"]=json_value(json_object<json_value>{});
			if (blockPlacerBlock!="") item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:block_placer"].val_object["block"]=blockPlacerBlock;
			if (blockPlacerDes) item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:block_placer"].val_object["use_block_description"]=blockPlacerDes;
		}
		if (entityPlacerCheckbox){
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:entity_placer"]=json_value(json_object<json_value>{});
			if (entityPlacerEntity!="") item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:entity_placer"].val_object["entity"]=entityPlacerEntity;
			if (!entityPlacerUseon.empty()) item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:entity_placer"].val_object["use_on"]=entityPlacerUseon;
			if (!entityPlacerDison.empty()) item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:entity_placer"].val_object["dispense_on"]=entityPlacerDison;
		}
		if (shooterCheckbox){
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:shooter"]=json_value(json_object<json_value>{});
			if (shooterMaxDraw>=1) item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:shooter"].val_object["max_draw_duration"]=shooterMaxDraw;
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:shooter"].val_object["charge_on_draw"]=shooterCharge;
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:shooter"].val_object["scale_power_by_draw_duration"]=shooterScale;
			if (shooterAmmoCheckbox){
				item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:shooter"].val_object["ammunition"]=json_value(vector<json_value>{json_object<json_value>{}});
				item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:shooter"].val_object["ammunition"].val_list[0].val_object["search_inventory"]=shooterAmmoInven;
				if (shooterAmmoItem!="") item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:shooter"].val_object["ammunition"].val_list[0].val_object["item"]=shooterAmmoItem;
				item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:shooter"].val_object["ammunition"].val_list[0].val_object["use_offhand"]=shooterAmmoHand;
				item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:shooter"].val_object["ammunition"].val_list[0].val_object["use_in_creative"]=shooterAmmoCreative;
			}
		}
		if (fertilizer>=0){
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:fertilizer"]=json_value(json_object<json_value>{});
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:fertilizer"].val_object["duration"]=fertilizer;
		}
		if (ignPerms){
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:ignores_permission"]=ignPerms;
		}
		if (miningSpeed>=0) item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:mining_speed"]=miningSpeed;
		if (liquidClipped) item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:liquid_clipped"]=liquidClipped;
		if (!shouldDespawn) item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:should_despawn"]=shouldDespawn;
		if (mirroredArt) item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:mirrored_art"]=mirroredArt;
		if (projectileCheckbox){
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:projectile"]=json_value(json_object<json_value>{});
			if (projectileEntity!="") item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:projectile"].val_object["projectile_entity"]=projectileEntity;
			if (projectilePower>=0) item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:projectile"].val_object["minimum_critical_power"]=projectilePower;
		}
		if (dyeCheckbox){
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:dye_powder"]=json_value(json_object<json_value>{});
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:dye_powder"].val_object["color"]=dyePowder;
		}
		if (throwableCheckbox){
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:throwable"]=json_value(json_object<json_value>{});
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:throwable"].val_object["do_swing_animation"]=throwableSwing;
			if (throwableDraw>=0) item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:throwable"].val_object["max_draw_duration"]=throwableDraw;
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:throwable"].val_object["scale_power_by_draw_duration"]=throwablePower;
		}
		if (knockbackResis>=0&&knockbackResis<=1){
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:knockback_resistance"]=json_value(json_object<json_value>{});
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:knockback_resistance"].val_object["protection"]=knockbackResis;
		}
		if (fuel>=0){
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:fuel"]=json_value(json_object<json_value>{});
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:fuel"].val_object["duration"]=fuel;
		}
		if (recordCheckbox){
			item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:record"]=json_value(json_object<json_value>{});
			if (recordSound!="") item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:record"].val_object["sound_event"]=recordSound;
			if (recordDuration>=0) item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:record"].val_object["duration"]=recordDuration;
			if (recordSignal>=0&&recordSignal<=15) item.val_object["minecraft:item"].val_object["components"].val_object["minecraft:record"].val_object["comparator_signal"]=recordSignal;
		}
		string name;
		if (identifier!="") name=get_iname(identifier)+".mcaddon";
		else name="item.mcaddon";
		json_value p=genManifest();
		if (itemIcon.filename!=""){
			itemIcon.filename=truncate_slashes(to_lower(icon)+".png");
			file zip(name,vector<file>{
				file("resource",vector<file>{
					file("manifest.json",p.val_object["rp"].get_repr()),
					file("textures",vector<file>{
						file("item_texture.json",itemAtlas.get_repr())
					}),
					itemIcon
				}),
				file("behavior",vector<file>{
					file("manifest.json",p.val_object["bp"].get_repr()),
					file("items",vector<file>{
						file(get_iname(identifier)+".item.json",item.get_repr())
					})
				})
			});
			return zip;
		}
		else{
			file zip(name,vector<file>{
				file("resource",vector<file>{
					file("manifest.json",p.val_object["rp"].get_repr())
				}),
				file("behavior",vector<file>{
					file("manifest.json",p.val_object["bp"].get_repr()),
					file("items",vector<file>{
						file(get_iname(identifier)+".item.json",item.get_repr())
					})
				})
			});
			return zip;
		}
	}
};