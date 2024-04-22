
const ACTION = {
    ECHO: 0,
    PAGE_CHANGED: 1
}

chrome.tabs.onUpdated.addListener(function(tabId, changeInfo, tab) {
  // Check if the page has finished loading
  if (changeInfo.status === "complete") {
    // Send a message to the content script
    
    chrome.tabs.query({active: true, currentWindow: true}, function(tabs) {
        // Get the URL of the active tab
        let url = tabs[0].url;

        chrome.tabs.sendMessage(tabId, {action: ACTION.PAGE_CHANGED, url: url});
    });

  }
});
