function writeManifest() {
	var pack_type = document.getElementById("pack.type"),
		display_element = document.getElementById("dp.element"),
		display_pack_element = document.getElementById("pack.element"),
		pack_name = document.getElementById("pack.name"),
		pack_description = document.getElementById("pack.description"),
		pack_version = document.getElementById("pack.min_engine_version"),
		pack_use_metadata = document.getElementById("pack.metadata.checkbox"),
		pack_author_element = document.getElementById("pack.author.element"),
		pack_author_name = document.getElementById("pack.author.name"),
		pack_author_url = document.getElementById("pack.author.url"),
		pack_code = document.getElementById("pack.code"),
		pack_copy = document.getElementById("pack.copy"),
		pack_download = document.getElementById("pack.download"),
		resource_pack_enable_ui = document.getElementById("rp.enable.ui.checkbox"),
		behavior_pack_enable_scripts = document.getElementById("bp.enable.scripts.checkbox"),
		pack_gametest_enabled = document.getElementById("pack.gametest.checkbox"),
		pack_gametest_element = document.getElementById("pack.gametest.element"),
		pack_gametest_entry_file = document.getElementById("pack.gametest.file"),
		pack_icon_file = document.getElementById("pack.icon"),
		pack_download_all = document.getElementById("pack.downloadA"),
		jszip_object = new JSZip;
	pack_download_all.onclick = function () {
		jszip_object.generateAsync({
			type: "blob"
		}).then(function (file) {
			"dep" === pack_type.value ? saveAs(
				file, 
				document.getElementById("rp.dep.name").value + ".mcaddon"
			) : saveAs(
				file, 
				pack_name.value + ".mcpack"
			)
		})
	};
	"dep" === pack_type.value ? (
		pack_is_dependent = !0, 
		display_pack_element.style.display = "none"
	) : (
		pack_is_dependent = !1, 
		display_pack_element.style.display = "block"
	);
	"skin_pack" === pack_type.value ? (
		pack_description.disabled = !0, 
		pack_version.disabled = !0
	) : (
		pack_description.disabled = !1, 
		pack_version.disabled = !1
	);
	!1 === pack_is_dependent ? (
		display_element.style.display = "none", 
		uuidgen1 = new uuid_generator_class, 
		output = {
			format_version: 2,
			header: {}
		}, 
		"" !== pack_name.value && (output.header.name = pack_name.value), 
		"" !== pack_description.value && "skin_pack" !== pack_type.value && (output.header.description = pack_description.value), 
		output.header.uuid = uuidgen1.generate_uuid(), 
		output.header.version = [1, 0, 0], 
		output.modules = [], 
		output.modules[0] = {}, 
		output.modules[0].type = "scripts" == pack_type.value ? "data" : pack_type.value, 
		output.modules[0].uuid = uuidgen1.generate_uuid(), 
		output.modules[0].version = [1, 0, 0], 
		"scripts" === pack_type.value && (
			output.modules[1] = {}, 
			"" !== pack_description.value && (output.modules[1].description = pack_description.value), 
			output.modules[1].type = "client_data", 
			output.modules[1].uuid = uuidgen1.generate_uuid(), 
			output.modules[1].version = [1, 0, 0]
		), 
		"none" !== pack_version.value && "skin_pack" !== pack_type.value && (output.header.min_engine_version = JSON.parse(pack_version.value)), 
		pack_use_metadata.checked ? (
			output.metadata = {}, 
			pack_author_element.style.display = "block", 
			"" !== pack_author_name.value && (
				output.metadata.authors = [], 
				authors = pack_author_name.value, 
				output.metadata.authors = authors.split(",").map(function (to_trim) {
					return to_trim.trim()
				})
			), 
			"" !== pack_author_url.value && (output.metadata.url = pack_author_url.value)
		) : pack_author_element.style.display = "none", 
		"data" == pack_type.value 
			? pack_gametest_enabled.disabled = !1 
			: "scripts" == pack_type.value 
				? pack_gametest_enabled.disabled = !1 
				: (
					pack_gametest_enabled.disabled = !0, 
					pack_gametest_enabled.checked && (pack_gametest_enabled.checked = !1)
				), 
		pack_gametest_enabled.checked ? (
			pack_gametest_element.style.display = "block", 
			output.dependencies = [], 
			output.dependencies[0] = {}, 
			output.dependencies[0].description = "Minecraft module, required to use the Minecraft module", 
			output.dependencies[0].uuid = "b26a4d4c-afdf-4690-88f8-931846312678", 
			output.dependencies[0].version = [0, 1, 0], 
			output.dependencies[1] = {}, 
			output.dependencies[1].description = "GameTest module, required to use the GameTest module", 
			output.dependencies[1].uuid = "6f4b6893-1bb6-42fd-b458-7fa3d0c89616", 
			output.dependencies[1].version = [0, 1, 0], 
			"" !== pack_gametest_entry_file.value && (
				"scripts" == pack_type.value ? (
					output.modules[2] = {}, 
					output.modules[2].type = "javascript", 
					output.modules[2].uuid = uuidgen1.generate_uuid(), 
					output.modules[2].version = [1, 0, 0], 
					output.modules[2].entry = "scripts/" + pack_gametest_entry_file.value
				) : (
					output.modules[1] = {}, 
					output.modules[1].type = "javascript", 
					output.modules[1].uuid = uuidgen1.generate_uuid(), 
					output.modules[1].version = [1, 0, 0], 
					output.modules[1].entry = "scripts/" + pack_gametest_entry_file.value
				)
			)
		) : pack_gametest_element.style.display = "none", 
		pack_code.value = JSON.stringify(output, null, 2), 
		pack_copy.onclick = function () {
			pack_code.select();
			pack_code.setSelectionRange(0, pack_code.value.length);
			document.execCommand("copy")
		}, 
		pack_download.onclick = function () {
			var code_blob = new Blob([pack_code.value], {
				type: "text/plain"
			}),
			save_button = document.createElement("a");
			save_button.download = "manifest.json";
			save_button.innerHTML = "Save";
			null != window.webkitURL ? save_button.href = window.webkitURL.createObjectURL(code_blob) : (
				save_button.href = window.URL.createObjectURL(code_blob), 
				save_button.onclick = destroyClickedElement, 
				save_button.style.display = "none", 
				document.body.appendChild(save_button)
			);
			save_button.click()
		}
	) : (
		uuidgen2 = new uuid_generator_class, 
		display_element.style.display = "block", 
		behaviorpack = {
			format_version: 2,
			header: {},
			modules: [],
			dependencies: [{}]
		}, 
		"" !== document.getElementById("bp.dep.name").value && (behaviorpack.header.name = document.getElementById("bp.dep.name").value), 
		"" !== document.getElementById("bp.dep.description").value && (behaviorpack.header.description = document.getElementById("bp.dep.description").value), 
		behaviorpack.header.uuid = uuidgen2.generate_uuid(), 
		behaviorpack.header.version = [1, 0, 0], 
		"none" !== document.getElementById("bp.dep.min_engine_version").value && (behaviorpack.header.min_engine_version = JSON.parse(document.getElementById("bp.dep.min_engine_version").value)), 
		behaviorpack.modules[0] = {}, 
		behaviorpack.modules[0].type = "data", 
		behaviorpack.modules[0].uuid = uuidgen2.generate_uuid(), 
		behaviorpack.modules[0].version = [1, 0, 0], 
		behavior_pack_enable_scripts.checked ? (
			resource_pack_enable_ui.disabled = !1, 
			behaviorpack.modules[1] = {}, 
			behaviorpack.modules[1].type = "client_data", 
			behaviorpack.modules[1].uuid = uuidgen2.generate_uuid(), 
			behaviorpack.modules[1].version = [1, 0, 0]
		) : resource_pack_enable_ui.disabled = !0, 
		document.getElementById("bp.dep.metadata.checkbox").checked ? (
			behaviorpack.metadata = {}, 
			document.getElementById("bp.dep.author.element").style.display = "block", 
			"" !== document.getElementById("bp.dep.author.name").value && (
				behaviorpack.metadata.authors = [], 
				authors = document.getElementById("bp.dep.author.name").value, 
				behaviorpack.metadata.authors = authors.split(",").map(function (to_trim) {
					return to_trim.trim()
				})
			), 
			"" !== document.getElementById("bp.dep.author.url").value && (behaviorpack.metadata.url = document.getElementById("bp.dep.author.url").value)
		) : document.getElementById("bp.dep.author.element").style.display = "none", 
		document.getElementById("bp.dep.copy").onclick = function () {
			document.getElementById("bp.dep.code").select();
			document.getElementById("bp.dep.code").setSelectionRange(0, document.getElementById("bp.dep.code").value.length);
			document.execCommand("copy")
		}, 
		document.getElementById("bp.dep.download").onclick = function () {
			var out_code = document.getElementById("bp.dep.code").value;
			code_blob = new Blob([out_code], {
				type: "text/plain"
			});
			var save_button = document.createElement("a");
			save_button.download = "manifest.json";
			save_button.innerHTML = "Save";
			null != window.webkitURL ? save_button.href = window.webkitURL.createObjectURL(code_blob) : (
				save_button.href = window.URL.createObjectURL(code_blob), 
				save_button.onclick = destroyClickedElement, 
				save_button.style.display = "none", 
				document.body.appendChild(save_button)
			);
			save_button.click()
		}, 
		resourcepack = {
			format_version: 2,
			header: {},
			modules: [{}],
			dependencies: [{}]
		}, 
		"" !== document.getElementById("rp.dep.name").value && (resourcepack.header.name = document.getElementById("rp.dep.name").value), 
		"" !== document.getElementById("rp.dep.description").value && (resourcepack.header.description = document.getElementById("rp.dep.description").value), 
		resourcepack.header.uuid = uuidgen2.generate_uuid(), 
		resourcepack.header.version = [1, 0, 0], 
		"none" !== document.getElementById("rp.dep.min_engine_version").value && (resourcepack.header.min_engine_version = JSON.parse(document.getElementById("rp.dep.min_engine_version").value)), 
		resourcepack.modules[0].type = "resources", 
		resourcepack.modules[0].uuid = uuidgen2.generate_uuid(), 
		resourcepack.modules[0].version = [1, 0, 0], 
		document.getElementById("rp.dep.metadata.checkbox").checked ? (
			resourcepack.metadata = {}, 
			document.getElementById("rp.dep.author.element").style.display = "block", 
			"" !== document.getElementById("rp.dep.author.name").value && (
				resourcepack.metadata.authors = [], 
				authors = document.getElementById("rp.dep.author.name").value, 
				resourcepack.metadata.authors = authors.split(",").map(function (to_trim) {
					return to_trim.trim()
				})
			), 
			"" !== document.getElementById("rp.dep.author.url").value && (resourcepack.metadata.url = document.getElementById("rp.dep.author.url").value)
		) : document.getElementById("rp.dep.author.element").style.display = "none", 
		document.getElementById("rp.dep.copy").onclick = function () {
			document.getElementById("rp.dep.code").select();
			document.getElementById("rp.dep.code").setSelectionRange(0, document.getElementById("rp.dep.code").value.length);
			document.execCommand("copy")
		}, 
		document.getElementById("rp.dep.download").onclick = function () {
				var out_code = document.getElementById("rp.dep.code").value;
				code_blob = new Blob([out_code], {
					type: "text/plain"
				});
			var save_button = document.createElement("a");
			save_button.download = "manifest.json";
			save_button.innerHTML = "Save";
			null != window.webkitURL ? save_button.href = window.webkitURL.createObjectURL(code_blob) : (
				save_button.href = window.URL.createObjectURL(code_blob), 
				save_button.onclick = destroyClickedElement, 
				save_button.style.display = "none", 
				document.body.appendChild(save_button)
			);
			save_button.click()
		}, 
		behaviorpack.dependencies[0].uuid = resourcepack.header.uuid, 
		behaviorpack.dependencies[0].version = resourcepack.header.version, 
		resourcepack.dependencies[0].uuid = behaviorpack.header.uuid, 
		resourcepack.dependencies[0].version = resourcepack.header.version, 
		resource_pack_enable_ui.checked && behavior_pack_enable_scripts.checked && (
			resourcepack.capabilities = [], 
			resourcepack.capabilities[0] = "experimental_custom_ui"
		), 
		document.getElementById("bp.gametest.checkbox").checked ? (
			document.getElementById("bp.gametest.element").style.display = "block", 
			behaviorpack.dependencies[0] = {}, 
			behaviorpack.dependencies[0].description = "Minecraft module, required to use the Minecraft module", 
			behaviorpack.dependencies[0].uuid = "b26a4d4c-afdf-4690-88f8-931846312678", 
			behaviorpack.dependencies[0].version = [0, 1, 0], 
			behaviorpack.dependencies[1] = {}, 
			behaviorpack.dependencies[1].description = "GameTest module, required to use the GameTest module", 
			behaviorpack.dependencies[1].uuid = "6f4b6893-1bb6-42fd-b458-7fa3d0c89616", 
			behaviorpack.dependencies[1].version = [0, 1, 0], 
			behavior_pack_enable_scripts.checked ? (
				behaviorpack.modules[2] = {}, 
				behaviorpack.modules[2].type = "javascript", 
				behaviorpack.modules[2].uuid = uuidgen2.generate_uuid(), 
				behaviorpack.modules[2].version = [1, 0, 0], 
				behaviorpack.modules[2].entry = "scripts/" + document.getElementById("bp.gametest.file").value
			) : (
				behaviorpack.modules[1] = {}, 
				behaviorpack.modules[1].type = "javascript", 
				behaviorpack.modules[1].uuid = uuidgen2.generate_uuid(), 
				behaviorpack.modules[1].version = [1, 0, 0], 
				behaviorpack.modules[1].entry = "scripts/" + document.getElementById("bp.gametest.file").value
			)
		) : document.getElementById("bp.gametest.element").style.display = "none", 
		document.getElementById("bp.dep.code").value = JSON.stringify(behaviorpack, null, 2), 
		document.getElementById("rp.dep.code").value = JSON.stringify(resourcepack, null, 2)
	);
	"resources" === pack_type.value ? (
		0 < pack_icon_file.files.length && jszip_object.file(
			"rp/pack_icon.png", 
			pack_icon_file.files[0]
		), jszip_object.file("rp/manifest.json", pack_code.value)
	) : "data" === pack_type.value ? (
		0 < pack_icon_file.files.length && jszip_object.file(
			"bp/pack_icon.png", 
			pack_icon_file.files[0]
		), jszip_object.file("bp/manifest.json", pack_code.value)
	) : "skin_pack" === pack_type.value ? (
		0 < pack_icon_file.files.length && jszip_object.file(
			"rp/pack_icon.png", 
			pack_icon_file.files[0]
		), jszip_object.file("rp/manifest.json", pack_code.value)
	) : "scripts" === pack_type.value ? (
		0 < pack_icon_file.files.length && jszip_object.file(
			"rp/pack_icon.png", 
			pack_icon_file.files[0]
		), jszip_object.file("rp/manifest.json", pack_code.value)
	) : (
		0 < pack_icon_file.files.length && (
			jszip_object.file(
				"rp/pack_icon.png", 
				pack_icon_file.files[0]
			), 
			jszip_object.file(
				"bp/pack_icon.png", 
				pack_icon_file.files[0]
			)
		), 
		jszip_object.file("rp/manifest.json", document.getElementById("rp.dep.code").value), 
		jszip_object.file("bp/manifest.json", document.getElementById("bp.dep.code").value)
	)
}
writeManifest();