
const adapterSection = document.querySelector("#adapter-list-section")

const btnAdapters = document.querySelector("#btn-adapters")
const btnAddHour = document.querySelector("#btn-addhour")
const btnAddHour2 = document.querySelector("#btn-addhour2")
const btnCleanNotMaster = document.querySelector("#btn-clean-notmaster")
const btnCleanTests = document.querySelector("#btn-clean-tests")
const btnCleanWarns = document.querySelector("#btn-clean-warns")
const btnMaxSV = document.querySelector("#btn-max-sv")
const btnDelSectionNotes = document.querySelector("#btn-del-section-notes")

const btnFilterByChannel = document.querySelector("#btn-filter-by-channel")
const btnFilterByChannelClear = document.querySelector("#btn-filter-by-channel-clear")

const btnFilterByLabel = document.querySelector("#btn-filter-by-label")
const btnFilterByLabelClear = document.querySelector("#btn-filter-by-label-clear")

const btnFilterByNote = document.querySelector("#btn-filter-by-note")
const btnFilterByNoteClear = document.querySelector("#btn-filter-by-note-clear")

const btnFilterByParam = document.querySelector("#btn-filter-by-param")
const btnFilterByParamClear = document.querySelector("#btn-filter-by-param-clear")

const btnFilterByRange = document.querySelector("#btn-filter-by-range")
const btnFilterByRangeClear = document.querySelector("#btn-filter-by-range-clear")
const inFilterRangeIni = document.getElementById('in-filter-range-ini') as HTMLInputElement
const inFilterRangeEnd = document.getElementById('in-filter-range-end') as HTMLInputElement

const btnGotoOPT = document.querySelector("#btn-goto-opt-vm")
const btnSetVM = document.querySelector("#btn-setvm")
const btnSetVM_old = document.querySelector("#btn-setvm-old")
const btnSubHour = document.querySelector("#btn-subhour")
const btnSubHour2 = document.querySelector("#btn-subhour2")

const inAdapterFilter = document.getElementById('in-adapter-filter') as HTMLInputElement
const inFilterChannel = document.getElementById('in-filter-channel') as HTMLInputElement
const inFilterLabel = document.getElementById('in-filter-label') as HTMLInputElement
const inFilterNote = document.getElementById('in-filter-note') as HTMLInputElement
const inFilterParamName = document.getElementById('in-filter-param-name') as HTMLInputElement
const inFilterParamValue = document.getElementById('in-filter-param-value') as HTMLInputElement

const [currentTab] = await chrome.tabs.query({ active: true, currentWindow: true })

import { ACTION } from "../types";

btnFilterByChannel.addEventListener('click', () => {
    const channel = (document.getElementById('in-filter-channel') as HTMLInputElement).value
    chrome.tabs.sendMessage(currentTab.id, { action: ACTION.FILTER_BY_CHANNEL, channel: channel })
})

btnFilterByChannelClear.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: ACTION.CLEAR_FILTER })
})

btnFilterByNote.addEventListener('click', () => {
    const note = (document.getElementById('in-filter-note') as HTMLInputElement).value
    chrome.tabs.sendMessage(currentTab.id, { action: ACTION.FILTER_BY_NOTE, note: note })
})

btnFilterByParam.addEventListener('click', () => {
    const name = (document.getElementById('in-filter-param-name') as HTMLInputElement).value
    const value = (document.getElementById('in-filter-param-value') as HTMLInputElement).value
    chrome.tabs.sendMessage(currentTab.id, { action: ACTION.FILTER_BY_PARAM, param: {name: name, value: value} })
})

btnFilterByRange.addEventListener('click', () => {
    const ini = (document.getElementById('in-filter-range-ini') as HTMLInputElement).value
    const end = (document.getElementById('in-filter-range-end') as HTMLInputElement).value
    chrome.tabs.sendMessage(currentTab.id, { action: ACTION.FILTER_BY_PARAM, range: {ini: ini, end: end} })
})

btnFilterByNoteClear.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: ACTION.CLEAR_FILTER })
})

btnFilterByParamClear.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: ACTION.CLEAR_FILTER })
})

btnFilterByRangeClear.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: ACTION.CLEAR_FILTER })
})

btnFilterByLabel.addEventListener('click', () => {
    const label = (document.getElementById('in-filter-label') as HTMLInputElement).value
    chrome.tabs.sendMessage(currentTab.id, { action: ACTION.FILTER_BY_LABEL, label: label })
})

btnFilterByLabelClear.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: ACTION.CLEAR_FILTER })
})

btnDelSectionNotes.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: ACTION.DEL_SECTION_NOTES })
})

btnAdapters.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: ACTION.ADAPTERS })
})

btnCleanTests.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: ACTION.CLEAN_TESTS })
})

btnCleanWarns.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: ACTION.CLEAN_WARNS })
})

btnMaxSV.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: ACTION.MAX_SV })
})

btnCleanNotMaster.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: ACTION.CLEAN_NOTMASTER })
})

btnGotoOPT.addEventListener('click', () => {
    // chrome.tabs.sendMessage(currentTab.id, { action: ACTION.GOTOOPT })
    chrome.runtime.sendMessage({tabId: currentTab, action: ACTION.GOTOOPT})
})

btnSetVM.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: ACTION.SET_VM })
})

btnSetVM_old.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: ACTION.SET_VM_OLD })
})


btnAddHour.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: ACTION.ADDHOUR })
})

btnSubHour.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: ACTION.SUBHOUR })
})

btnSubHour2.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: ACTION.SUBHOUR2 })
})

btnAddHour2.addEventListener('click', () => {
    chrome.tabs.sendMessage(currentTab.id, { action: ACTION.ADDHOUR2 })
})

chrome.runtime.onMessage.addListener((request, _sender, _response) => {
    
    const fun_Adapters = () => {
        const adapters: string[] = request.adapters
        const adapterFilter = inAdapterFilter.value
        
        // check filter
        const re = new RegExp(adapterFilter)
        const filteredAdapters = adapters.filter(a => a.match(re))
        
        adapterSection.innerHTML = ''
        
        filteredAdapters.forEach(adapterName => {
            let el = document.createElement('button')
            el.textContent = adapterName
            el.className = 'bg-gray-500 hover:bg-gray-600 border-gray-800'
            el.onclick = () => {
                chrome.tabs.sendMessage(currentTab.id, { action: ACTION.SELECT_ADAPTER, adapterName: adapterName })
            }
            adapterSection.appendChild(el)
        })
    }
    
    const fun_MaxSV = () => {
        const ans:HTMLElement = document.querySelector('#ans')
        
        const max = request.max
        ans.innerText = `sv max -> ${max}`
    }
    
    const funmap = {
        [ACTION.ADAPTERS]: fun_Adapters,
        [ACTION.MAX_SV]: fun_MaxSV,
    }
    
    try {
        funmap[request.action]()
    } catch (e) {
        console.log(e)
        console.log(request)
    }
    
}) 

inAdapterFilter.addEventListener('change', (e) => {
    const value=  (e.target as HTMLInputElement).value
    
    chrome.storage.sync.set({adapterFilter: value})
})

inFilterChannel.addEventListener('change', (e) => {
    const value=  (e.target as HTMLInputElement).value
    
    chrome.storage.sync.set({filterChannel: value})
})

inFilterLabel.addEventListener('change', (e) => {
    const value = (e.target as HTMLInputElement).value
    
    chrome.storage.sync.set({filterLabel: value})
})

inFilterNote.addEventListener('change', (e) => {
    const value = (e.target as HTMLInputElement).value
    
    chrome.storage.sync.set({filterNote: value})
})

inFilterParamName.addEventListener('change', (e) => {
    const value = (e.target as HTMLInputElement).value
    
    chrome.storage.sync.set({filterParamName: value})
})

inFilterParamValue.addEventListener('change', (e) => {
    const value = (e.target as HTMLInputElement).value
    
    chrome.storage.sync.set({filterParamValue: value})
})

inFilterRangeIni.addEventListener('change', (e) => {
    const value = (e.target as HTMLInputElement).value
    
    chrome.storage.sync.set({filterRangeIni: value})
})

inFilterRangeEnd.addEventListener('change', (e) => {
    const value = (e.target as HTMLInputElement).value
    
    chrome.storage.sync.set({filterRangeEnd: value})
})

chrome.storage.sync.get(['adapterFilter', 'filterChannel', 'filterNote', 'filterLabel', 'filterParamName', 'filterParamValue', 'filterRangeIni', 'filterRangeEnd'], (result) => {
    inAdapterFilter.value = result.adapterFilter || ""
    inFilterChannel.value = result.filterChannel || ""
    inFilterLabel.value = result.filterLabel || ""
    inFilterNote.value = result.filterNote || ""
    inFilterParamName.value = result.filterParamName || ""
    inFilterParamValue.value = result.filterParamValue || ""
    inFilterRangeIni.value = result.filterRangeIni || ""
    inFilterRangeEnd.value = result.filterRangeEnd || ""
})