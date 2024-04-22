const btnPrompt = document.querySelector("#btn-prompt")
const btnRender = document.querySelector("#btn-render")
const [currentTab] = await chrome.tabs.query({ active: true, currentWindow: true })

const nameElement = document.getElementById("name-element")

btnPrompt.addEventListener('click', async () => {
    await chrome.tabs.sendMessage(currentTab.id, { action: "PROMPT" })
})

btnRender.addEventListener('click', async () => {
    await chrome.tabs.sendMessage(currentTab.id, { action: "RENDER" })
})

chrome.storage.sync.get(["name"], (res) => {
    const name = res.name ?? "???"
    nameElement.textContent = `Your name is ${name}`
})

// chrome.action.setBadgeText({
//     text: "adapter"
// })