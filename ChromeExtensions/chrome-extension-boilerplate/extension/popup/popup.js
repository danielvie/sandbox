const checkAction = document.querySelector("#check-action")
const btnAction  = document.querySelector("#btn-action")

const [currentTab] = await chrome.tabs.query({ active: true, currentWindow: true })

const ACTION = {
    ECHO: 0,
    PAGE_CHANGED: 0,
}

checkAction.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: ACTION.ECHO })
})

btnAction.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: ACTION.ECHO })
})

chrome.runtime.onMessage.addListener((request, sender, response) => {
    console.log('received message from outside')
}) 

chrome.storage.sync.get(['checkValue'], (result) => {
    checkAction.checked = result.checkValue
})