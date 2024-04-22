/******/ (() => { // webpackBootstrap
/******/ 	"use strict";
/******/ 	var __webpack_modules__ = ({

/***/ "./src/types.ts":
/*!**********************!*\
  !*** ./src/types.ts ***!
  \**********************/
/***/ ((__unused_webpack_module, __webpack_exports__, __webpack_require__) => {

__webpack_require__.r(__webpack_exports__);
/* harmony export */ __webpack_require__.d(__webpack_exports__, {
/* harmony export */   ACTION: () => (/* binding */ ACTION)
/* harmony export */ });
var ACTION;
(function (ACTION) {
    ACTION[ACTION["ADAPTERS"] = 0] = "ADAPTERS";
    ACTION[ACTION["ADDHOUR"] = 1] = "ADDHOUR";
    ACTION[ACTION["ADDHOUR2"] = 2] = "ADDHOUR2";
    ACTION[ACTION["CLEAN_NOTMASTER"] = 3] = "CLEAN_NOTMASTER";
    ACTION[ACTION["CLEAN_TESTS"] = 4] = "CLEAN_TESTS";
    ACTION[ACTION["CLEAN_WARNS"] = 5] = "CLEAN_WARNS";
    ACTION[ACTION["CLEAR_FILTER"] = 6] = "CLEAR_FILTER";
    ACTION[ACTION["DEL_SECTION_NOTES"] = 7] = "DEL_SECTION_NOTES";
    ACTION[ACTION["MAX_SV"] = 8] = "MAX_SV";
    ACTION[ACTION["FILTER_BY_CHANNEL"] = 9] = "FILTER_BY_CHANNEL";
    ACTION[ACTION["FILTER_BY_LABEL"] = 10] = "FILTER_BY_LABEL";
    ACTION[ACTION["FILTER_BY_NOTE"] = 11] = "FILTER_BY_NOTE";
    ACTION[ACTION["FILTER_BY_PARAM"] = 12] = "FILTER_BY_PARAM";
    ACTION[ACTION["FILTER_BY_RANGE"] = 13] = "FILTER_BY_RANGE";
    ACTION[ACTION["GET_MOUSE"] = 14] = "GET_MOUSE";
    ACTION[ACTION["GOTOOPT"] = 15] = "GOTOOPT";
    ACTION[ACTION["PAGE_CHANGED"] = 16] = "PAGE_CHANGED";
    ACTION[ACTION["PLAY"] = 17] = "PLAY";
    ACTION[ACTION["SELECT_ADAPTER"] = 18] = "SELECT_ADAPTER";
    ACTION[ACTION["SET_VM"] = 19] = "SET_VM";
    ACTION[ACTION["SET_VM_OLD"] = 20] = "SET_VM_OLD";
    ACTION[ACTION["SUBHOUR"] = 21] = "SUBHOUR";
    ACTION[ACTION["SUBHOUR2"] = 22] = "SUBHOUR2";
})(ACTION || (ACTION = {}));


/***/ })

/******/ 	});
/************************************************************************/
/******/ 	// The module cache
/******/ 	var __webpack_module_cache__ = {};
/******/ 	
/******/ 	// The require function
/******/ 	function __webpack_require__(moduleId) {
/******/ 		// Check if module is in cache
/******/ 		var cachedModule = __webpack_module_cache__[moduleId];
/******/ 		if (cachedModule !== undefined) {
/******/ 			return cachedModule.exports;
/******/ 		}
/******/ 		// Create a new module (and put it into the cache)
/******/ 		var module = __webpack_module_cache__[moduleId] = {
/******/ 			// no module.id needed
/******/ 			// no module.loaded needed
/******/ 			exports: {}
/******/ 		};
/******/ 	
/******/ 		// Execute the module function
/******/ 		__webpack_modules__[moduleId](module, module.exports, __webpack_require__);
/******/ 	
/******/ 		// Return the exports of the module
/******/ 		return module.exports;
/******/ 	}
/******/ 	
/************************************************************************/
/******/ 	/* webpack/runtime/define property getters */
/******/ 	(() => {
/******/ 		// define getter functions for harmony exports
/******/ 		__webpack_require__.d = (exports, definition) => {
/******/ 			for(var key in definition) {
/******/ 				if(__webpack_require__.o(definition, key) && !__webpack_require__.o(exports, key)) {
/******/ 					Object.defineProperty(exports, key, { enumerable: true, get: definition[key] });
/******/ 				}
/******/ 			}
/******/ 		};
/******/ 	})();
/******/ 	
/******/ 	/* webpack/runtime/hasOwnProperty shorthand */
/******/ 	(() => {
/******/ 		__webpack_require__.o = (obj, prop) => (Object.prototype.hasOwnProperty.call(obj, prop))
/******/ 	})();
/******/ 	
/******/ 	/* webpack/runtime/make namespace object */
/******/ 	(() => {
/******/ 		// define __esModule on exports
/******/ 		__webpack_require__.r = (exports) => {
/******/ 			if(typeof Symbol !== 'undefined' && Symbol.toStringTag) {
/******/ 				Object.defineProperty(exports, Symbol.toStringTag, { value: 'Module' });
/******/ 			}
/******/ 			Object.defineProperty(exports, '__esModule', { value: true });
/******/ 		};
/******/ 	})();
/******/ 	
/************************************************************************/
var __webpack_exports__ = {};
// This entry need to be wrapped in an IIFE because it need to be isolated against other modules in the chunk.
(() => {
/*!************************!*\
  !*** ./src/content.ts ***!
  \************************/
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var _types__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./types */ "./src/types.ts");

const config_vm_optics = {
    SMOKE_COMMENT: "xl mode axini[mbt]",
    PROJECT_BUILD_XML_PATH: "\\\\ach-ha-server\\HoldingArea\\ProjectBuildsFDT\\TEM\\TEM_ISO\\tem_platform_iso\\product\\project.build.xml",
    MAIN_COMPONENT: "TEM_ISO",
    PRODUCT: "Titan",
    TARGET: "debug",
    CPU: "x86",
    CONFIGS: "Juelich_TOMO",
    PLATFORM: "win10",
    CLEAN_VM: "No",
    EXPORT_VM: "No",
    FINAL_EXPORT_FOLDER: "\\\\ach-smoketests\\SmokeTest-TEM\\ExportedVMs",
    USE_TEST_EXECUTOR: "No",
};
const config_vm_optics_old = {
    SMOKE_COMMENT: "xl mode axini[mbt] 7.17.x",
    PROJECT_BUILD_XML_PATH: "\\\\ach-ha-server\\HoldingArea\\ProjectBuildsFDT\\TEM\\TEM_ISO\\tem_7.17.x_iso\\product\\project.build.xml",
    MAIN_COMPONENT: "TEM_ISO",
    PRODUCT: "Titan",
    TARGET: "debug",
    CPU: "x86",
    CONFIGS: "Juelich_TOMO",
    PLATFORM: "win10",
    CLEAN_VM: "No",
    EXPORT_VM: "No",
    FINAL_EXPORT_FOLDER: "\\\\ach-smoketests\\SmokeTest-TEM\\ExportedVMs",
    USE_TEST_EXECUTOR: "No",
};
const GetInputs = () => {
    return document.querySelectorAll(".input-group");
};
const SetLogHour = (offset_minutes) => {
    // get all timestamp elements
    const elements = document.querySelectorAll("#test-case-table td");
    const patt = /^\d+:\d+:[\d.]+$/;
    elements.forEach((el) => {
        const t = el.innerHTML.split("\n").join("");
        if (t.match(patt)) {
            const _time = new Date(`1970-01-01T${t}Z`);
            _time.setMinutes(_time.getMinutes() + offset_minutes);
            const updatedTime = _time.toISOString().match(/\d+:\d+:[\d.]+/)[0];
            el.innerHTML = `\n${updatedTime}\n`;
        }
    });
};
const CleanTestSets = () => {
    document.querySelectorAll(".text-struckthrough").forEach((el) => el.remove());
};
const CleanTestNotMaster = () => {
    document.querySelectorAll(".table tbody tr").forEach((e) => {
        if (!e.children[0].innerText.includes("master"))
            e.remove();
    });
};
const CleanDangerMessages = () => {
    const formDanger = document.querySelectorAll(".form-text.text-danger");
    if (formDanger)
        formDanger.forEach((el) => (el.innerHTML = ""));
    const alertDanger = document.querySelectorAll(".alert.alert-danger");
    if (alertDanger)
        alertDanger.forEach((el) => el.remove());
};
const CleanMonitor = () => {
    console.log("[in] clean monitor");
    const el = document.querySelectorAll(".form-text.text-danger");
    const url = document.URL;
    if (!url.includes("configure_channel_mapping")) {
        return false;
    }
    if (el.length > 0) {
        CleanDangerMessages();
        return true;
    }
    setTimeout(() => {
        CleanMonitor();
    }, 10);
};
function GetAvailableAdapters() {
    console.log("GetAvailableAdapters");
    // finding section with adapter names
    const selects = document.querySelectorAll("select");
    // getting elements in `bold`
    let listAdapters = [];
    selects[0].querySelectorAll("option").forEach((o) => {
        listAdapters.push(o.textContent.replace(/\(compatible\)$/, ""));
    });
    console.log(listAdapters);
    return listAdapters;
}
chrome.runtime.onMessage.addListener((request, _sender, _response) => {
    const fun_Adapters = () => {
        const adapters = GetAvailableAdapters();
        chrome.runtime.sendMessage({ action: _types__WEBPACK_IMPORTED_MODULE_0__.ACTION.ADAPTERS, adapters: adapters });
    };
    const fun_Clean_tests = () => {
        CleanTestSets();
    };
    const fun_Select_adapter = () => {
        // cleanning danger messages
        CleanTestSets();
        SetAdapter(request.adapterName);
    };
    const fun_Page_changed = () => {
        // console.log('page changed')
    };
    const fun_Play = () => {
        console.log("[in] play");
    };
    const _filter = (elements, value) => {
        // getting elements that are a match with the regex and are not hidden
        const re = new RegExp(value);
        const listOK = [];
        for (let index = 0; index < elements.length; index++) {
            const el = elements[index];
            const parent = el.closest(".step-row");
            if (el.innerText.match(re) && !parent.classList.contains("hidden")) {
                listOK.push(parent);
            }
        }
        // add hidden to all elements
        document
            .querySelectorAll("tbody .step-row")
            .forEach((e) => e.classList.add("hidden"));
        // display only selected elements
        for (let index = 0; index < listOK.length; index++) {
            const element = listOK[index];
            element.classList.remove("hidden");
        }
    };
    const fun_FilterByChannel = (channel) => {
        console.log(`FilterByChannel: \`/${channel}/\``);
        _filter(document.querySelectorAll("tbody .channel"), channel);
    };
    const fun_FilterByNote = (note) => {
        console.log(`FilterByNote: \`/${note}/\``);
        _filter(document.querySelectorAll("tbody .note"), note);
    };
    const fun_FilterByLabel = (label) => {
        console.log(`FilterByLabel: \`/${label}/\``);
        _filter(document.querySelectorAll("tbody .label"), label);
    };
    const fun_FilterByParam = (param) => {
        if (!param) {
            return false;
        }
        const name = param["name"];
        const value = param["value"];
        console.log(`FilterByParam: \`/${name}/\` : \`/${value}/\``);
        /* CUSTOM _FILTER FOR PARAM TO MATCH BOTH NAME AND VALUE OF THE ELEMENT */
        const elements = document.querySelectorAll("tbody .parameter");
        // getting elements that are a match with the regex and are not hidden
        const re_name = new RegExp(name);
        const re_value = new RegExp(value);
        const listOK = [];
        for (let index = 0; index < elements.length; index++) {
            const el_name = elements[index].querySelector(".name");
            const el_value = el_name.parentElement.querySelector(".value");
            const parent = el_name.closest(".step-row");
            if (el_name.innerText.match(re_name) &&
                el_value.innerText.match(re_value) &&
                !parent.classList.contains("hidden")) {
                listOK.push(parent);
            }
        }
        // add hidden to all elements
        document
            .querySelectorAll("tbody .step-row")
            .forEach((e) => e.classList.add("hidden"));
        // display only selected elements
        for (let index = 0; index < listOK.length; index++) {
            const element = listOK[index];
            element.classList.remove("hidden");
        }
    };
    const fun_FilterByRange = (param) => {
        if (!param) {
            return false;
        }
        const ini = parseInt(param["ini"]) || 1;
        const end = parseInt(param["end"]) || 999999;
        console.log(`FilterByRange: ${ini} :: ${end}`);
        /* CUSTOM _FILTER FOR PARAM TO MATCH BOTH NAME AND VALUE OF THE ELEMENT */
        const elements = document.querySelectorAll("tbody .step");
        // getting elements that are a match with the regex and are not hidden
        const listOK = [];
        for (let index = 0; index < elements.length; index++) {
            const el = elements[index];
            const line_idx = parseInt(el.innerText);
            const parent = el.closest(".step-row");
            if (line_idx >= ini &&
                line_idx <= end &&
                !parent.classList.contains("hidden")) {
                listOK.push(parent);
            }
        }
        // add hidden to all elements
        document
            .querySelectorAll("tbody .step-row")
            .forEach((e) => e.classList.add("hidden"));
        // display only selected elements
        for (let index = 0; index < listOK.length; index++) {
            const element = listOK[index];
            element.classList.remove("hidden");
        }
    };
    const fun_ClearFilter = () => {
        console.log("ClearFilter");
        document
            .querySelectorAll("tbody .step-row")
            .forEach((e) => e.classList.remove("hidden"));
    };
    const fun_DelNotesButton = () => {
        const notes_button = document.getElementById("show-notes-button");
        if (notes_button) {
            notes_button.remove();
        }
        const notes = document.getElementById("notes");
        if (notes) {
            notes.remove();
        }
    };
    const fun_MinMaxSV = () => {
        const sv = document.querySelectorAll(".step-row .state_vectors");
        let r = [];
        sv.forEach((e) => {
            const ei = parseInt(e.innerText);
            if (!isNaN(ei)) {
                r.push(ei);
            }
        });
        r = r.filter((e) => !isNaN(e));
        const max = Math.max.apply(null, r);
        console.log(`max sv: ${max}`);
        chrome.runtime.sendMessage({ action: _types__WEBPACK_IMPORTED_MODULE_0__.ACTION.MAX_SV, max: max });
    };
    const funmap = {
        [_types__WEBPACK_IMPORTED_MODULE_0__.ACTION.ADAPTERS]: fun_Adapters,
        [_types__WEBPACK_IMPORTED_MODULE_0__.ACTION.CLEAN_TESTS]: fun_Clean_tests,
        [_types__WEBPACK_IMPORTED_MODULE_0__.ACTION.SELECT_ADAPTER]: fun_Select_adapter,
        [_types__WEBPACK_IMPORTED_MODULE_0__.ACTION.PAGE_CHANGED]: fun_Page_changed,
        // [ACTION.GET_MOUSE]: fun_Get_mouse,
        [_types__WEBPACK_IMPORTED_MODULE_0__.ACTION.SET_VM]: () => SetVM(config_vm_optics),
        [_types__WEBPACK_IMPORTED_MODULE_0__.ACTION.SET_VM_OLD]: () => SetVM(config_vm_optics_old),
        [_types__WEBPACK_IMPORTED_MODULE_0__.ACTION.ADDHOUR]: () => SetLogHour(60),
        [_types__WEBPACK_IMPORTED_MODULE_0__.ACTION.SUBHOUR]: () => SetLogHour(-60),
        [_types__WEBPACK_IMPORTED_MODULE_0__.ACTION.ADDHOUR2]: () => SetLogHour(120),
        [_types__WEBPACK_IMPORTED_MODULE_0__.ACTION.SUBHOUR2]: () => SetLogHour(-120),
        [_types__WEBPACK_IMPORTED_MODULE_0__.ACTION.CLEAN_WARNS]: () => CleanDangerMessages(),
        [_types__WEBPACK_IMPORTED_MODULE_0__.ACTION.CLEAN_NOTMASTER]: () => CleanTestNotMaster(),
        [_types__WEBPACK_IMPORTED_MODULE_0__.ACTION.PLAY]: fun_Play,
        [_types__WEBPACK_IMPORTED_MODULE_0__.ACTION.FILTER_BY_CHANNEL]: () => fun_FilterByChannel(request.channel),
        [_types__WEBPACK_IMPORTED_MODULE_0__.ACTION.FILTER_BY_LABEL]: () => fun_FilterByLabel(request.label),
        [_types__WEBPACK_IMPORTED_MODULE_0__.ACTION.FILTER_BY_NOTE]: () => fun_FilterByNote(request.note),
        [_types__WEBPACK_IMPORTED_MODULE_0__.ACTION.FILTER_BY_PARAM]: () => fun_FilterByParam(request.param),
        [_types__WEBPACK_IMPORTED_MODULE_0__.ACTION.FILTER_BY_RANGE]: fun_FilterByRange(request.range),
        [_types__WEBPACK_IMPORTED_MODULE_0__.ACTION.DEL_SECTION_NOTES]: fun_DelNotesButton,
        [_types__WEBPACK_IMPORTED_MODULE_0__.ACTION.CLEAR_FILTER]: fun_ClearFilter,
        [_types__WEBPACK_IMPORTED_MODULE_0__.ACTION.MAX_SV]: fun_MinMaxSV,
    };
    try {
        funmap[request.action]();
    }
    catch (e) {
        console.log(e);
        console.log("COULD NOT UNDERSTAND THIS ACTION");
        console.log(request);
    }
});
chrome.storage.sync.get(["checkCleanValue"], (results) => {
    if (results.checkCleanValue) {
        CleanMonitor();
    }
});
function SetVM(config_vm_optics) {
    console.log(config_vm_optics);
    const divs = document
        .querySelector("table.parameters")
        .querySelectorAll("div");
    for (const key in config_vm_optics) {
        console.log(`set ${key} to: "${config_vm_optics[key]}"`);
        for (const d of divs) {
            const inputs = d.querySelectorAll("input");
            const select = d.querySelectorAll("select");
            if (inputs[0].value == key) {
                if (select.length > 0) {
                    for (let o of select[0].querySelectorAll("option")) {
                        if (o.value === config_vm_optics[key]) {
                            o.selected = true;
                        }
                    }
                }
                else {
                    inputs[1].value = config_vm_optics[key];
                }
            }
        }
    }
}
function SetAdapter(adapterName) {
    const curProj = document
        .querySelector("#current-project")
        .textContent.toLowerCase();
    // uhv specific
    if (adapterName.includes("TFS@UHVLoader") &&
        curProj.includes("tfs_uhvloader")) {
        const _name = adapterName.match(/TFS@UHVLoader.*/)[0];
        SetUHVLoader(_name);
        return false;
    }
    else if (adapterName.toLowerCase().includes("biprism") &&
        curProj.includes("tfs_optics")) {
        SetOptics(adapterName);
        return false;
    }
    // other projects
    const inputs = GetInputs();
    inputs.forEach((i) => {
        let options = i.querySelectorAll("option");
        options.forEach((o) => {
            if (o.textContent.replace(" (compatible)", "") === adapterName) {
                o.selected = true;
                return true;
            }
        });
    });
}
function SetUHVLoader(adapterName) {
    console.log(`[uhvloader] set adapter to ${adapterName}`);
    const adapterSufix = adapterName.split("@").pop();
    const provided = [
        "ILoaderControl_V2",
        "IInitialize",
        "IRecovery",
        "ITransfer",
        "IUninitialize",
        "IControl",
        "IAction",
    ];
    const requiredMotion = [
        "IMotionFirmwareBase",
        "IMotionFirmwareLoadlock",
        "IMotionFirmwareStorageChamber",
        "IMotionFirmwareOctagon",
    ];
    const requiredVacuum = ["IValve", "IManualValve", "IPump"];
    const inputs = GetInputs();
    inputs.forEach((input) => {
        const label = input.parentElement.querySelector("label").innerText;
        const conditions = [adapterSufix.toLowerCase()];
        if (provided.includes(label)) {
            conditions.push("provided");
        }
        else if (requiredMotion.includes(label)) {
            conditions.push("required");
            conditions.push("motion");
        }
        else if (requiredVacuum.includes(label)) {
            conditions.push("required");
            conditions.push("vacuum");
        }
        else {
            conditions.push("required");
            conditions.push("vacuum");
            console.log("name is not known, setting to `required.vacuum`");
        }
        let options = input.querySelectorAll("option");
        options.forEach((o) => {
            const hasAll = conditions.every((c) => o.textContent.toLowerCase().includes(c));
            if (hasAll) {
                o.selected = true;
                return true;
            }
        });
    });
}
function SetOptics(adapterName) {
    console.log(`[optics] set adapter to ${adapterName}`);
    const computerName = adapterName.match(/(?<=@.*-).*/)[0];
    const provided = [
        "IBiprism",
        "IBiprismEvents",
        "IBiprismRotation",
        "IBiprismService",
        "IBiprismVoltage",
        "IBiprisms",
    ];
    const required = ["IHalSimAdc", "ISimRegister", "ISimSwitch"];
    const inputs = GetInputs();
    inputs.forEach((input) => {
        const label = input.parentElement.querySelector("label").innerText;
        const conditions = [computerName.toLowerCase()];
        if (provided.includes(label)) {
            conditions.push("axinitester");
        }
        else if (required.includes(label)) {
            conditions.push("required");
        }
        else {
            conditions.push("required");
            console.log("name is not known, setting to `required`");
        }
        let options = input.querySelectorAll("option");
        options.forEach((o) => {
            const hasAll = conditions.every((c) => o.textContent.toLowerCase().includes(c));
            if (hasAll) {
                o.selected = true;
                return true;
            }
        });
    });
}

})();

/******/ })()
;
//# sourceMappingURL=content.js.map