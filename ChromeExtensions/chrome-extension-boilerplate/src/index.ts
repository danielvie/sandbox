enum ACTION {
    ECHO = 0,
    PAGE_CHANGED = 1,
}

chrome.runtime.onMessage.addListener( (request, _sender, _response) => {
    
    if (request.action === ACTION.ECHO) {
        
        console.log('received message with action ECHO')
    } else {
        console.log('COULD NOT UNDERSTAND THIS ACTION')
        console.log(request)
    }
})

chrome.storage.sync.get(['checkValue'], (results) => {
    console.log(results)
})