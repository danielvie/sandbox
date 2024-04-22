/******/ (() => { // webpackBootstrap
var __webpack_exports__ = {};
/*!**********************!*\
  !*** ./src/index.ts ***!
  \**********************/
var ACTION;
(function (ACTION) {
    ACTION[ACTION["ECHO"] = 0] = "ECHO";
    ACTION[ACTION["PAGE_CHANGED"] = 1] = "PAGE_CHANGED";
})(ACTION || (ACTION = {}));
chrome.runtime.onMessage.addListener((request, _sender, _response) => {
    if (request.action === ACTION.ECHO) {
        console.log('received message with action ECHO');
    }
    else {
        console.log('COULD NOT UNDERSTAND THIS ACTION');
        console.log(request);
    }
});
chrome.storage.sync.get(['checkValue'], (results) => {
    console.log(results);
});

/******/ })()
;
//# sourceMappingURL=content.js.map