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
/*!***************************!*\
  !*** ./src/background.ts ***!
  \***************************/
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var _types__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./types */ "./src/types.ts");

chrome.tabs.onUpdated.addListener(function (tabId, changeInfo, _tab) {
    // Check if the page has finished loading
    if (changeInfo.status === "complete") {
        // Send a message to the content script
        chrome.tabs.query({ active: true, currentWindow: true }, function (tabs) {
            // Get the URL of the active tab
            if (tabs) {
                let url = tabs[0].url;
                chrome.tabs.sendMessage(tabId, { action: _types__WEBPACK_IMPORTED_MODULE_0__.ACTION.PAGE_CHANGED, url: url });
            }
        });
    }
});
chrome.runtime.onMessage.addListener(function (request, sender, sendResponse) {
    if (request.action == _types__WEBPACK_IMPORTED_MODULE_0__.ACTION.GOTOOPT) {
        chrome.tabs.update(request.tabId.id, { url: "https://nlein-jenkins3.emea.thermo.com/jenkins/job/CreateVM/job/CreateVM-Smokes_2.0/build?delay=0sec" })
            .then(() => console.log("Tab updated"))
            .catch((error) => console.error(error, 'asdfasdfasdfasdfasdf'));
    }
});

})();

/******/ })()
;
//# sourceMappingURL=background.js.map