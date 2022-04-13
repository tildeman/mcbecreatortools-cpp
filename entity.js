// var $jscomp = $jscomp || {};
// $jscomp.scope = {};
// $jscomp.createTemplateTagFirstArg = function (a) {
// 	return a.raw = a
// };
// $jscomp.createTemplateTagFirstArgWithRaw = function (a, b) {
// 	a.raw = b;
// 	return a
// };
var identifier = document.getElementById("entity.identifier"),
	textureFile = document.getElementById("entity.texture_file"),
	modelFile = document.getElementById("entity.model_file"),
	isSpawnable = document.getElementById("entity.is_spawnable"),
	isSummonable = document.getElementById("entity.is_summonable"),
	isExperimental = document.getElementById("entity.is_experimental"),
	spawnEggPanel = document.getElementById("entity.spawn_egg.panel"),
	spawnEggOverlay = document.getElementById("entity.spawn_egg.overlay_color"),
	spawnEggBase = document.getElementById("entity.spawn_egg.base_color"),
	material = document.getElementById("entity.material"),
	baseBeh = document.getElementById("entity.basic_behaviors"),
	genButton = document.getElementById("entity.generate"),
	clearButton = document.getElementById("entity.clear"),
	spawnEggShow = document.getElementById("entity.spawn_egg.show_panel"),
	client = document.getElementsByClassName("client"),
	server = document.getElementsByClassName("server"),
	customBeh = document.getElementById("entity.custom_behaviors"),
	geoID = "",
	select = document.getElementById("pack.type"),
	reader = new FileReader,
	health = document.getElementById("behavior.health"),
	scale = document.getElementById("behavior.scale"),
	collisionH = document.getElementById("behavior.collision_box.height"),
	collisionW = document.getElementById("behavior.collision_box.width"),
	typeFamily = document.getElementById("behavior.type_family"),
	isImmune = document.getElementById("behavior.is_immune");
select.onchange = function () {
	"res" == select.value && "both" != select.value ? ($(".client").show(), $(".server").hide()) : ($(".client").hide(), $(".server").show());
	spawnEggShow.style.display = "none";
	"both" == select.value && ($(".client").show(), $(".server").show(), spawnEggShow.style.display = "block")
};

function main() {
	identifier.value 
		? (
			$("#entity").find("input, select, button").removeAttr("disabled"), 
			spawnEggPanel.style.display = isSpawnable.checked ? "block" : "none"
		) 
		: (
			$("#entity").find("input, select, button").not("[name=identifier]").attr("disabled", "disabled"), 
			spawnEggPanel.style.display = "none"
		);
}
main();

// function getGeo() {
// 	0 < modelFile.files.length && (reader.addEventListener("load", function () {
// 		geoID = JSON.parse(reader.result)["minecraft:geometry"][0].description.identifier
// 	}), reader.readAsText(modelFile.files[0]))
// }
genButton.onclick = function () {
	if (is_valid_identifier(identifier.value)) {
		var uuidobj = new uuid_generator_class,
			jszobject = new JSZip;
		genManifest(uuidobj);
		var manifest = genManifest(uuidobj);
		respack = manifest.rp;
		behpack = manifest.bp;
		var cliententity = {
			format_version: "1.10.0",
			"minecraft:client_entity": {}
		};
		cliententity["minecraft:client_entity"].description = {};
		cliententity["minecraft:client_entity"].description.identifier = identifier.value;
		isSpawnable.checked && (
			cliententity["minecraft:client_entity"].description.spawn_egg = {}, 
			cliententity["minecraft:client_entity"].description.spawn_egg.overlay_color = spawnEggOverlay.value, 
			cliententity["minecraft:client_entity"].description.spawn_egg.base_color = spawnEggBase.value
		);
		var e = textureFile.files;
		for (i = 0; i < e.length; i++) {
			var f = e[i].name.replace(".png", "");
			cliententity["minecraft:client_entity"].description.textures = {};
			cliententity["minecraft:client_entity"].description.textures["default"] = "textures/entity/" + f.toLowerCase();
			"res" !== select.value && "both" !== select.value || jszobject.file(
				"resource_pack/textures/entity/" + (f.toLowerCase() + ".png"), 
				e[i]
			)
		}
		cliententity["minecraft:client_entity"].description.materials = {};
		cliententity["minecraft:client_entity"].description.materials["default"] = material.value;
		0 < modelFile.files.length && (
			cliententity["minecraft:client_entity"].description.geometry = {}, 
			"res" !== select.value && "both" !== select.value || jszobject.file(
				"resource_pack/models/entity/" + modelFile.files[0].name, 
				modelFile.files[0]
			), 
			cliententity["minecraft:client_entity"].description.geometry["default"] = geoID.toLowerCase()
		);
		cliententity["minecraft:client_entity"].description.render_controllers = [];
		cliententity["minecraft:client_entity"].description.render_controllers[0] = "controller.render." + identifier.value.split(":")[1];
		rendercontr = {};
		"beh" !== select.value && (0 < modelFile.files.length && 0 < textureFile.files.length 
			? genRenderControllers(rendercontr) 
			: window.alert('Can\'t generate render controllers, missing either "geometry" or "texture"!'));
		beh = {};
		baseBeh.checked ? genBehBasic(beh) : genBehCustom(beh);
		"res" !== select.value && "both" !== select.value || "beh" === select.value || (
			jszobject.file(
				"resource_pack/manifest.json", 
				JSON.stringify(respack, null, 2)
			), 
			jszobject.file(
				"resource_pack/texts/en_US.lang", 
				"entity." + identifier.value + ".name=" + identifier.value.split(":")[1]
			), 
			jszobject.file(
				"resource_pack/entity/" + identifier.value.split(":")[1] + ".client.json", 
				JSON.stringify(cliententity, null, 2)
			), 
			jszobject.file(
				"resource_pack/render_controllers/" + identifier.value.split(":")[1] + ".render_controllers.json", 
				JSON.stringify(rendercontr, null, 2)
			)
		);
		"beh" !== select.value && "both" !== select.value || "res" === select.value || (
			jszobject.file(
				"behavior_pack/manifest.json", 
				JSON.stringify(behpack, null, 2)
			), 
			jszobject.file(
				"behavior_pack/entities/" + identifier.value.split(":")[1] + ".json", 
				JSON.stringify(beh, null, 2)
			)
		);
		jszobject.generateAsync({
			type: "blob"
		}).then(function (g) {
			"beh" === select.value || "res" === select.value 
				? "res" === select.value 
					? saveAs(g, identifier.value.split(":")[1] + ".rp.mcpack") 
					: saveAs(g, identifier.value.split(":")[1] + ".bp.mcpack") 
				: "both" === select.value && saveAs(g, identifier.value.split(":")[1] + ".mcaddon")
		}, function (g) {
			console.log(g)
		})
	} else window.alert("Invalid Identifier!")
};

function genBehBasic(entityobj) {
	entityobj.format_version = "1.16.0";
	entityobj["minecraft:entity"] = {};
	entityobj["minecraft:entity"].description = {};
	entityobj["minecraft:entity"].description.identifier = identifier.value;
	entityobj["minecraft:entity"].description.is_spawnable = isSpawnable.checked;
	entityobj["minecraft:entity"].description.is_summonable = isSummonable.checked;
	entityobj["minecraft:entity"].description.is_experimental = isExperimental.checked;
	entityobj["minecraft:entity"].components = {};
	entityobj["minecraft:entity"].components["minecraft:health"] = {};
	entityobj["minecraft:entity"].components["minecraft:health"].value = 20;
	entityobj["minecraft:entity"].components["minecraft:physics"] = {}
}

function genBehCustom(entityobj) {
	entityobj.format_version = "1.16.0";
	entityobj["minecraft:entity"] = {};
	entityobj["minecraft:entity"].description = {};
	entityobj["minecraft:entity"].description.identifier = identifier.value;
	entityobj["minecraft:entity"].description.is_spawnable = isSpawnable.checked;
	entityobj["minecraft:entity"].description.is_summonable = isSummonable.checked;
	entityobj["minecraft:entity"].description.is_experimental = isExperimental.checked;
	entityobj["minecraft:entity"].components = {};
	health.value && !isImmune.checked && (
		entityobj["minecraft:entity"].components["minecraft:health"] = {}, 
		entityobj["minecraft:entity"].components["minecraft:health"].value = parseFloat(health.value)
	);
	scale.value && (
		entityobj["minecraft:entity"].components["minecraft:scale"] = {}, 
		entityobj["minecraft:entity"].components["minecraft:scale"].value = parseFloat(scale.value)
	);
	typeFamily.value && (
		entityobj["minecraft:entity"].components["minecraft:type_family"] = {}, 
		entityobj["minecraft:entity"].components["minecraft:type_family"].family = [], 
		entityobj["minecraft:entity"].components["minecraft:type_family"].family = typeFamily.value.split(",")
	);
	isImmune.checked && (
		entityobj["minecraft:entity"].components["minecraft:damage_sensor"] = {}, 
		entityobj["minecraft:entity"].components["minecraft:damage_sensor"].triggers = {}, 
		entityobj["minecraft:entity"].components["minecraft:damage_sensor"].triggers.cause = "all", 
		entityobj["minecraft:entity"].components["minecraft:damage_sensor"].triggers.deals_damage = "false");
	collisionH.value && collisionW.value && (
		entityobj["minecraft:entity"].components["minecraft:collision_box"] = {}, 
		entityobj["minecraft:entity"].components["minecraft:collision_box"].height = parseFloat(collisionH.value), 
		entityobj["minecraft:entity"].components["minecraft:collision_box"].width = parseFloat(collisionW.value)
	)
}

function genRenderControllers(rcobject) {
	rcobject.format_version = "1.10.0";
	rcobject.render_controllers = {};
	rcobject.render_controllers["controller.render." + identifier.value.split(":")[1]] = {};
	rcobject.render_controllers["controller.render." + identifier.value.split(":")[1]].geometry = "geometry.default";
	rcobject.render_controllers["controller.render." + identifier.value.split(":")[1]].materials = [{}];
	rcobject.render_controllers["controller.render." + identifier.value.split(":")[1]].materials[0]["*"] = "material.default";
	rcobject.render_controllers["controller.render." + identifier.value.split(":")[1]].textures = [];
	rcobject.render_controllers["controller.render." + identifier.value.split(":")[1]].textures[0] = "texture.default"
}

function genManifest(uuidobj) {
	var behaviorpack = {},
		resourcepack = {};
	behaviorpack.format_version = 2;
	resourcepack.format_version = 2;
	behaviorpack.header = {};
	resourcepack.header = {};
	behaviorpack.header.name = "BP";
	resourcepack.header.name = "RP";
	behaviorpack.header.description = "BP Description";
	resourcepack.header.description = "RP Description";
	behaviorpack.header.uuid = uuidobj.generate_uuid();
	resourcepack.header.uuid = uuidobj.generate_uuid();
	behaviorpack.header.version = [0, 0, 1];
	resourcepack.header.version = [0, 0, 1];
	behaviorpack.header.min_engine_version = [1, 16, 0];
	resourcepack.header.min_engine_version = [1, 16, 0];
	behaviorpack.modules = [{}];
	resourcepack.modules = [{}];
	behaviorpack.modules[0].type = "data";
	resourcepack.modules[0].type = "resources";
	behaviorpack.modules[0].uuid = uuidobj.generate_uuid();
	resourcepack.modules[0].uuid = uuidobj.generate_uuid();
	behaviorpack.modules[0].version = [0, 0, 1];
	resourcepack.modules[0].version = [0, 0, 1];
	"both" === select.value && (
		behaviorpack.dependencies = [{}], 
		resourcepack.dependencies = [{}], 
		behaviorpack.dependencies[0].uuid = resourcepack.header.uuid, 
		resourcepack.dependencies[0].uuid = behaviorpack.header.uuid, 
		behaviorpack.dependencies[0].version = resourcepack.header.version, 
		resourcepack.dependencies[0].version = behaviorpack.header.version
	);
	return {
		rp: resourcepack,
		bp: behaviorpack
	}
}
var is_valid_identifier = verifyIdentifier();

function verifyIdentifier() {
	return function (a, b) {
		b = void 0 === b ? !1 : b;
		return a.match(":") 
			? (a.startsWith("minecraft") || a.startsWith("minecon")) && !1 === b 
				? !1 
				: /[!@#$%^&*()+\-=\[\]{};'"\\|,<>\/?]+/.test(a) 
					? !1 
					: a.startsWith(":") || a.startsWith(".") 
						? !1 
						: !0 
			: !1
	}
};