import { ACTION } from "./types";

chrome.tabs.onUpdated.addListener(function(tabId, changeInfo, _tab) {
  // Check if the page has finished loading
  if (changeInfo.status === "complete") {
    // Send a message to the content script
    
    chrome.tabs.query({active: true, currentWindow: true}, function(tabs) {
        // Get the URL of the active tab
        if (tabs) {
            let url = tabs[0].url;
            chrome.tabs.sendMessage(tabId, {action: ACTION.PAGE_CHANGED, url: url});
        }
    });

  }
});

chrome.runtime.onMessage.addListener(function(request, sender, sendResponse) {
  if (request.action == ACTION.GOTOOPT) {
    chrome.tabs.update(request.tabId.id, {url: "https://nlein-jenkins3.emea.thermo.com/jenkins/job/CreateVM/job/CreateVM-Smokes_2.0/build?delay=0sec"})
      .then(() => console.log("Tab updated"))
      .catch((error) => console.error(error, 'asdfasdfasdfasdfasdf'));
  }
});
