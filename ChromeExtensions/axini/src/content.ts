import { ACTION, VMCONFIG } from "./types";

const config_vm_optics: VMCONFIG = {
  SMOKE_COMMENT: "xl mode axini[mbt]",
  PROJECT_BUILD_XML_PATH:
    "\\\\ach-ha-server\\HoldingArea\\ProjectBuildsFDT\\TEM\\TEM_ISO\\tem_platform_iso\\product\\project.build.xml",
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

const config_vm_optics_old: VMCONFIG = {
  SMOKE_COMMENT: "xl mode axini[mbt] 7.17.x",
  PROJECT_BUILD_XML_PATH:
    "\\\\ach-ha-server\\HoldingArea\\ProjectBuildsFDT\\TEM\\TEM_ISO\\tem_7.17.x_iso\\product\\project.build.xml",
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

const SetLogHour = (offset_minutes: number) => {
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
    if (!(e.children[0] as HTMLElement).innerText.includes("master"))
      e.remove();
  });
};

const CleanDangerMessages = () => {
  const formDanger = document.querySelectorAll(".form-text.text-danger");
  if (formDanger) formDanger.forEach((el) => (el.innerHTML = ""));

  const alertDanger = document.querySelectorAll(".alert.alert-danger");
  if (alertDanger) alertDanger.forEach((el) => el.remove());
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
  const selects: NodeListOf<HTMLElement> = document.querySelectorAll("select");

  // getting elements in `bold`
  let listAdapters: string[] = [];
  selects[0].querySelectorAll("option").forEach((o) => {
    listAdapters.push(o.textContent.replace(/\(compatible\)$/, ""));
  });

  console.log(listAdapters);
  return listAdapters;
}

chrome.runtime.onMessage.addListener((request, _sender, _response) => {
  const fun_Adapters = () => {
    const adapters = GetAvailableAdapters();

    chrome.runtime.sendMessage({ action: ACTION.ADAPTERS, adapters: adapters });
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

  const _filter = (elements: NodeListOf<Element>, value: string) => {
    // getting elements that are a match with the regex and are not hidden
    const re = new RegExp(value);
    const listOK = [];
    for (let index = 0; index < elements.length; index++) {
      const el = elements[index] as HTMLElement;
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
      const element = listOK[index] as HTMLElement;

      element.classList.remove("hidden");
    }
  };

  const fun_FilterByChannel = (channel: string) => {
    console.log(`FilterByChannel: \`/${channel}/\``);

    _filter(document.querySelectorAll("tbody .channel"), channel);
  };

  const fun_FilterByNote = (note: string) => {
    console.log(`FilterByNote: \`/${note}/\``);

    _filter(document.querySelectorAll("tbody .note"), note);
  };

  const fun_FilterByLabel = (label: string) => {
    console.log(`FilterByLabel: \`/${label}/\``);

    _filter(document.querySelectorAll("tbody .label"), label);
  };

  const fun_FilterByParam = (param: string) => {
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
      const el_name = elements[index].querySelector(".name") as HTMLElement;
      const el_value = el_name.parentElement.querySelector(
        ".value"
      ) as HTMLElement;
      const parent = el_name.closest(".step-row");

      if (
        el_name.innerText.match(re_name) &&
        el_value.innerText.match(re_value) &&
        !parent.classList.contains("hidden")
      ) {
        listOK.push(parent);
      }
    }

    // add hidden to all elements
    document
      .querySelectorAll("tbody .step-row")
      .forEach((e) => e.classList.add("hidden"));

    // display only selected elements
    for (let index = 0; index < listOK.length; index++) {
      const element = listOK[index] as HTMLElement;

      element.classList.remove("hidden");
    }
  };

  const fun_FilterByRange = (param: string) => {
    if (!param) {
      return false;
    }

    const ini: number = parseInt(param["ini"]) || 1;
    const end: number = parseInt(param["end"]) || 999999;

    console.log(`FilterByRange: ${ini} :: ${end}`);

    /* CUSTOM _FILTER FOR PARAM TO MATCH BOTH NAME AND VALUE OF THE ELEMENT */

    const elements = document.querySelectorAll("tbody .step");

    // getting elements that are a match with the regex and are not hidden
    const listOK = [];
    for (let index = 0; index < elements.length; index++) {
      const el = elements[index] as HTMLElement;
      const line_idx = parseInt(el.innerText);
      const parent = el.closest(".step-row");

      if (
        line_idx >= ini &&
        line_idx <= end &&
        !parent.classList.contains("hidden")
      ) {
        listOK.push(parent);
      }
    }

    // add hidden to all elements
    document
      .querySelectorAll("tbody .step-row")
      .forEach((e) => e.classList.add("hidden"));

    // display only selected elements
    for (let index = 0; index < listOK.length; index++) {
      const element = listOK[index] as HTMLElement;

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
    let r: number[] = [];

    sv.forEach((e: HTMLElement) => {
      const ei: number = parseInt(e.innerText);

      if (!isNaN(ei)) {
        r.push(ei);
      }
    });

    r = r.filter((e) => !isNaN(e));
    const max = Math.max.apply(null, r);
    console.log(`max sv: ${max}`);

    chrome.runtime.sendMessage({ action: ACTION.MAX_SV, max: max });
  };

  const funmap = {
    [ACTION.ADAPTERS]: fun_Adapters,
    [ACTION.CLEAN_TESTS]: fun_Clean_tests,
    [ACTION.SELECT_ADAPTER]: fun_Select_adapter,
    [ACTION.PAGE_CHANGED]: fun_Page_changed,
    // [ACTION.GET_MOUSE]: fun_Get_mouse,
    [ACTION.SET_VM]: () => SetVM(config_vm_optics),
    [ACTION.SET_VM_OLD]: () => SetVM(config_vm_optics_old),
    [ACTION.ADDHOUR]: () => SetLogHour(60),
    [ACTION.SUBHOUR]: () => SetLogHour(-60),
    [ACTION.ADDHOUR2]: () => SetLogHour(120),
    [ACTION.SUBHOUR2]: () => SetLogHour(-120),
    [ACTION.CLEAN_WARNS]: () => CleanDangerMessages(),
    [ACTION.CLEAN_NOTMASTER]: () => CleanTestNotMaster(),
    [ACTION.PLAY]: fun_Play,
    [ACTION.FILTER_BY_CHANNEL]: () => fun_FilterByChannel(request.channel),
    [ACTION.FILTER_BY_LABEL]: () => fun_FilterByLabel(request.label),
    [ACTION.FILTER_BY_NOTE]: () => fun_FilterByNote(request.note),
    [ACTION.FILTER_BY_PARAM]: () => fun_FilterByParam(request.param),
    [ACTION.FILTER_BY_RANGE]: fun_FilterByRange(request.range),
    [ACTION.DEL_SECTION_NOTES]: fun_DelNotesButton,
    [ACTION.CLEAR_FILTER]: fun_ClearFilter,
    [ACTION.MAX_SV]: fun_MinMaxSV,
  };

  try {
    funmap[request.action]();
  } catch (e) {
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

function SetVM(config_vm_optics: VMCONFIG) {
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
        } else {
          inputs[1].value = config_vm_optics[key];
        }
      }
    }
  }
}

function SetAdapter(adapterName: string) {
  const curProj = document
    .querySelector("#current-project")
    .textContent.toLowerCase();

  // uhv specific
  if (
    adapterName.includes("TFS@UHVLoader") &&
    curProj.includes("tfs_uhvloader")
  ) {
    const _name = adapterName.match(/TFS@UHVLoader.*/)[0];
    SetUHVLoader(_name);
    return false;
  } else if (
    adapterName.toLowerCase().includes("biprism") &&
    curProj.includes("tfs_optics")
  ) {
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

function SetUHVLoader(adapterName: string) {
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
    } else if (requiredMotion.includes(label)) {
      conditions.push("required");
      conditions.push("motion");
    } else if (requiredVacuum.includes(label)) {
      conditions.push("required");
      conditions.push("vacuum");
    } else {
      conditions.push("required");
      conditions.push("vacuum");
      console.log("name is not known, setting to `required.vacuum`");
    }

    let options = input.querySelectorAll("option");

    options.forEach((o) => {
      const hasAll = conditions.every((c) =>
        o.textContent.toLowerCase().includes(c)
      );

      if (hasAll) {
        o.selected = true;
        return true;
      }
    });
  });
}

function SetOptics(adapterName: string) {
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
    } else if (required.includes(label)) {
      conditions.push("required");
    } else {
      conditions.push("required");
      console.log("name is not known, setting to `required`");
    }

    let options = input.querySelectorAll("option");
    options.forEach((o) => {
      const hasAll = conditions.every((c) =>
        o.textContent.toLowerCase().includes(c)
      );
      if (hasAll) {
        o.selected = true;
        return true;
      }
    });
  });
}
