/******/ (() => { // webpackBootstrap
/******/ 	"use strict";
/******/ 	var __webpack_modules__ = ({

/***/ "./src/popup/popup.ts":
/*!****************************!*\
  !*** ./src/popup/popup.ts ***!
  \****************************/
/***/ ((module, __webpack_exports__, __webpack_require__) => {

__webpack_require__.a(module, async (__webpack_handle_async_dependencies__, __webpack_async_result__) => { try {
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var _types__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ../types */ "./src/types.ts");
const adapterSection = document.querySelector("#adapter-list-section");
const btnAdapters = document.querySelector("#btn-adapters");
const btnAddHour = document.querySelector("#btn-addhour");
const btnAddHour2 = document.querySelector("#btn-addhour2");
const btnCleanNotMaster = document.querySelector("#btn-clean-notmaster");
const btnCleanTests = document.querySelector("#btn-clean-tests");
const btnCleanWarns = document.querySelector("#btn-clean-warns");
const btnMaxSV = document.querySelector("#btn-max-sv");
const btnDelSectionNotes = document.querySelector("#btn-del-section-notes");
const btnFilterByChannel = document.querySelector("#btn-filter-by-channel");
const btnFilterByChannelClear = document.querySelector("#btn-filter-by-channel-clear");
const btnFilterByLabel = document.querySelector("#btn-filter-by-label");
const btnFilterByLabelClear = document.querySelector("#btn-filter-by-label-clear");
const btnFilterByNote = document.querySelector("#btn-filter-by-note");
const btnFilterByNoteClear = document.querySelector("#btn-filter-by-note-clear");
const btnFilterByParam = document.querySelector("#btn-filter-by-param");
const btnFilterByParamClear = document.querySelector("#btn-filter-by-param-clear");
const btnFilterByRange = document.querySelector("#btn-filter-by-range");
const btnFilterByRangeClear = document.querySelector("#btn-filter-by-range-clear");
const inFilterRangeIni = document.getElementById('in-filter-range-ini');
const inFilterRangeEnd = document.getElementById('in-filter-range-end');
const btnGotoOPT = document.querySelector("#btn-goto-opt-vm");
const btnSetVM = document.querySelector("#btn-setvm");
const btnSetVM_old = document.querySelector("#btn-setvm-old");
const btnSubHour = document.querySelector("#btn-subhour");
const btnSubHour2 = document.querySelector("#btn-subhour2");
const inAdapterFilter = document.getElementById('in-adapter-filter');
const inFilterChannel = document.getElementById('in-filter-channel');
const inFilterLabel = document.getElementById('in-filter-label');
const inFilterNote = document.getElementById('in-filter-note');
const inFilterParamName = document.getElementById('in-filter-param-name');
const inFilterParamValue = document.getElementById('in-filter-param-value');
const [currentTab] = await chrome.tabs.query({ active: true, currentWindow: true });

btnFilterByChannel.addEventListener('click', () => {
    const channel = document.getElementById('in-filter-channel').value;
    chrome.tabs.sendMessage(currentTab.id, { action: _types__WEBPACK_IMPORTED_MODULE_0__.ACTION.FILTER_BY_CHANNEL, channel: channel });
});
btnFilterByChannelClear.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: _types__WEBPACK_IMPORTED_MODULE_0__.ACTION.CLEAR_FILTER });
});
btnFilterByNote.addEventListener('click', () => {
    const note = document.getElementById('in-filter-note').value;
    chrome.tabs.sendMessage(currentTab.id, { action: _types__WEBPACK_IMPORTED_MODULE_0__.ACTION.FILTER_BY_NOTE, note: note });
});
btnFilterByParam.addEventListener('click', () => {
    const name = document.getElementById('in-filter-param-name').value;
    const value = document.getElementById('in-filter-param-value').value;
    chrome.tabs.sendMessage(currentTab.id, { action: _types__WEBPACK_IMPORTED_MODULE_0__.ACTION.FILTER_BY_PARAM, param: { name: name, value: value } });
});
btnFilterByRange.addEventListener('click', () => {
    const ini = document.getElementById('in-filter-range-ini').value;
    const end = document.getElementById('in-filter-range-end').value;
    chrome.tabs.sendMessage(currentTab.id, { action: _types__WEBPACK_IMPORTED_MODULE_0__.ACTION.FILTER_BY_PARAM, range: { ini: ini, end: end } });
});
btnFilterByNoteClear.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: _types__WEBPACK_IMPORTED_MODULE_0__.ACTION.CLEAR_FILTER });
});
btnFilterByParamClear.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: _types__WEBPACK_IMPORTED_MODULE_0__.ACTION.CLEAR_FILTER });
});
btnFilterByRangeClear.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: _types__WEBPACK_IMPORTED_MODULE_0__.ACTION.CLEAR_FILTER });
});
btnFilterByLabel.addEventListener('click', () => {
    const label = document.getElementById('in-filter-label').value;
    chrome.tabs.sendMessage(currentTab.id, { action: _types__WEBPACK_IMPORTED_MODULE_0__.ACTION.FILTER_BY_LABEL, label: label });
});
btnFilterByLabelClear.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: _types__WEBPACK_IMPORTED_MODULE_0__.ACTION.CLEAR_FILTER });
});
btnDelSectionNotes.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: _types__WEBPACK_IMPORTED_MODULE_0__.ACTION.DEL_SECTION_NOTES });
});
btnAdapters.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: _types__WEBPACK_IMPORTED_MODULE_0__.ACTION.ADAPTERS });
});
btnCleanTests.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: _types__WEBPACK_IMPORTED_MODULE_0__.ACTION.CLEAN_TESTS });
});
btnCleanWarns.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: _types__WEBPACK_IMPORTED_MODULE_0__.ACTION.CLEAN_WARNS });
});
btnMaxSV.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: _types__WEBPACK_IMPORTED_MODULE_0__.ACTION.MAX_SV });
});
btnCleanNotMaster.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: _types__WEBPACK_IMPORTED_MODULE_0__.ACTION.CLEAN_NOTMASTER });
});
btnGotoOPT.addEventListener('click', () => {
    // chrome.tabs.sendMessage(currentTab.id, { action: ACTION.GOTOOPT })
    chrome.runtime.sendMessage({ tabId: currentTab, action: _types__WEBPACK_IMPORTED_MODULE_0__.ACTION.GOTOOPT });
});
btnSetVM.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: _types__WEBPACK_IMPORTED_MODULE_0__.ACTION.SET_VM });
});
btnSetVM_old.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: _types__WEBPACK_IMPORTED_MODULE_0__.ACTION.SET_VM_OLD });
});
btnAddHour.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: _types__WEBPACK_IMPORTED_MODULE_0__.ACTION.ADDHOUR });
});
btnSubHour.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: _types__WEBPACK_IMPORTED_MODULE_0__.ACTION.SUBHOUR });
});
btnSubHour2.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: _types__WEBPACK_IMPORTED_MODULE_0__.ACTION.SUBHOUR2 });
});
btnAddHour2.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: _types__WEBPACK_IMPORTED_MODULE_0__.ACTION.ADDHOUR2 });
});
chrome.runtime.onMessage.addListener((request, _sender, _response) => {
    const fun_Adapters = () => {
        const adapters = request.adapters;
        const adapterFilter = inAdapterFilter.value;
        // check filter
        const re = new RegExp(adapterFilter);
        const filteredAdapters = adapters.filter(a => a.match(re));
        adapterSection.innerHTML = '';
        filteredAdapters.forEach(adapterName => {
            let el = document.createElement('button');
            el.textContent = adapterName;
            el.className = 'bg-gray-500 hover:bg-gray-600 border-gray-800';
            el.onclick = () => {
                chrome.tabs.sendMessage(currentTab.id, { action: _types__WEBPACK_IMPORTED_MODULE_0__.ACTION.SELECT_ADAPTER, adapterName: adapterName });
            };
            adapterSection.appendChild(el);
        });
    };
    const fun_MaxSV = () => {
        const ans = document.querySelector('#ans');
        const max = request.max;
        ans.innerText = `sv max -> ${max}`;
    };
    const funmap = {
        [_types__WEBPACK_IMPORTED_MODULE_0__.ACTION.ADAPTERS]: fun_Adapters,
        [_types__WEBPACK_IMPORTED_MODULE_0__.ACTION.MAX_SV]: fun_MaxSV,
    };
    try {
        funmap[request.action]();
    }
    catch (e) {
        console.log(e);
        console.log(request);
    }
});
inAdapterFilter.addEventListener('change', (e) => {
    const value = e.target.value;
    chrome.storage.sync.set({ adapterFilter: value });
});
inFilterChannel.addEventListener('change', (e) => {
    const value = e.target.value;
    chrome.storage.sync.set({ filterChannel: value });
});
inFilterLabel.addEventListener('change', (e) => {
    const value = e.target.value;
    chrome.storage.sync.set({ filterLabel: value });
});
inFilterNote.addEventListener('change', (e) => {
    const value = e.target.value;
    chrome.storage.sync.set({ filterNote: value });
});
inFilterParamName.addEventListener('change', (e) => {
    const value = e.target.value;
    chrome.storage.sync.set({ filterParamName: value });
});
inFilterParamValue.addEventListener('change', (e) => {
    const value = e.target.value;
    chrome.storage.sync.set({ filterParamValue: value });
});
inFilterRangeIni.addEventListener('change', (e) => {
    const value = e.target.value;
    chrome.storage.sync.set({ filterRangeIni: value });
});
inFilterRangeEnd.addEventListener('change', (e) => {
    const value = e.target.value;
    chrome.storage.sync.set({ filterRangeEnd: value });
});
chrome.storage.sync.get(['adapterFilter', 'filterChannel', 'filterNote', 'filterLabel', 'filterParamName', 'filterParamValue', 'filterRangeIni', 'filterRangeEnd'], (result) => {
    inAdapterFilter.value = result.adapterFilter || "";
    inFilterChannel.value = result.filterChannel || "";
    inFilterLabel.value = result.filterLabel || "";
    inFilterNote.value = result.filterNote || "";
    inFilterParamName.value = result.filterParamName || "";
    inFilterParamValue.value = result.filterParamValue || "";
    inFilterRangeIni.value = result.filterRangeIni || "";
    inFilterRangeEnd.value = result.filterRangeEnd || "";
});

__webpack_async_result__();
} catch(e) { __webpack_async_result__(e); } }, 1);

/***/ }),

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
/******/ 	/* webpack/runtime/async module */
/******/ 	(() => {
/******/ 		var webpackQueues = typeof Symbol === "function" ? Symbol("webpack queues") : "__webpack_queues__";
/******/ 		var webpackExports = typeof Symbol === "function" ? Symbol("webpack exports") : "__webpack_exports__";
/******/ 		var webpackError = typeof Symbol === "function" ? Symbol("webpack error") : "__webpack_error__";
/******/ 		var resolveQueue = (queue) => {
/******/ 			if(queue && !queue.d) {
/******/ 				queue.d = 1;
/******/ 				queue.forEach((fn) => (fn.r--));
/******/ 				queue.forEach((fn) => (fn.r-- ? fn.r++ : fn()));
/******/ 			}
/******/ 		}
/******/ 		var wrapDeps = (deps) => (deps.map((dep) => {
/******/ 			if(dep !== null && typeof dep === "object") {
/******/ 				if(dep[webpackQueues]) return dep;
/******/ 				if(dep.then) {
/******/ 					var queue = [];
/******/ 					queue.d = 0;
/******/ 					dep.then((r) => {
/******/ 						obj[webpackExports] = r;
/******/ 						resolveQueue(queue);
/******/ 					}, (e) => {
/******/ 						obj[webpackError] = e;
/******/ 						resolveQueue(queue);
/******/ 					});
/******/ 					var obj = {};
/******/ 					obj[webpackQueues] = (fn) => (fn(queue));
/******/ 					return obj;
/******/ 				}
/******/ 			}
/******/ 			var ret = {};
/******/ 			ret[webpackQueues] = x => {};
/******/ 			ret[webpackExports] = dep;
/******/ 			return ret;
/******/ 		}));
/******/ 		__webpack_require__.a = (module, body, hasAwait) => {
/******/ 			var queue;
/******/ 			hasAwait && ((queue = []).d = 1);
/******/ 			var depQueues = new Set();
/******/ 			var exports = module.exports;
/******/ 			var currentDeps;
/******/ 			var outerResolve;
/******/ 			var reject;
/******/ 			var promise = new Promise((resolve, rej) => {
/******/ 				reject = rej;
/******/ 				outerResolve = resolve;
/******/ 			});
/******/ 			promise[webpackExports] = exports;
/******/ 			promise[webpackQueues] = (fn) => (queue && fn(queue), depQueues.forEach(fn), promise["catch"](x => {}));
/******/ 			module.exports = promise;
/******/ 			body((deps) => {
/******/ 				currentDeps = wrapDeps(deps);
/******/ 				var fn;
/******/ 				var getResult = () => (currentDeps.map((d) => {
/******/ 					if(d[webpackError]) throw d[webpackError];
/******/ 					return d[webpackExports];
/******/ 				}))
/******/ 				var promise = new Promise((resolve) => {
/******/ 					fn = () => (resolve(getResult));
/******/ 					fn.r = 0;
/******/ 					var fnQueue = (q) => (q !== queue && !depQueues.has(q) && (depQueues.add(q), q && !q.d && (fn.r++, q.push(fn))));
/******/ 					currentDeps.map((dep) => (dep[webpackQueues](fnQueue)));
/******/ 				});
/******/ 				return fn.r ? promise : getResult();
/******/ 			}, (err) => ((err ? reject(promise[webpackError] = err) : outerResolve(exports)), resolveQueue(queue)));
/******/ 			queue && (queue.d = 0);
/******/ 		};
/******/ 	})();
/******/ 	
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
/******/ 	
/******/ 	// startup
/******/ 	// Load entry module and return exports
/******/ 	// This entry module used 'module' so it can't be inlined
/******/ 	var __webpack_exports__ = __webpack_require__("./src/popup/popup.ts");
/******/ 	
/******/ })()
;
//# sourceMappingURL=popup.js.map