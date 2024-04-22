let currentCameraPos = 1;
const cameraIdList = GetCameras();
console.log(cameraIdList);

function GetCameras() {
  let cameraList = [];
  navigator.mediaDevices.enumerateDevices().then((devices) => {
    devices.forEach((mediaDevice) => {
      if (mediaDevice.kind === "videoinput") {
        cameraList.push(mediaDevice.deviceId.toString());
      }
    });
  });
  return cameraList;
}

document.addEventListener("DOMContentLoaded", () => {
  var openCam = document.getElementById("b-open-cam");
  var video = document.getElementById("vid");
  var mediaDevices = navigator.mediaDevices;
  vid.muted = true;
  openCam.addEventListener("click", () => {
    mediaDevices
      .getUserMedia({
        video: {
          deviceId: cameraIdList[currentCameraPos],
        },
        audio: false,
      })
      .then((stream) => {
        // changing the source of video to current stream video.srcObject = stream;
        video.addEventListener("loadedmetadata", () => {
          video.play();
        });
      })
      .catch(alert);
  });

  document.getElementById("b-flip-x").addEventListener("click", () => {
    video.classList.toggle("flip-v");
  });

  document.getElementById("b-flip-y").addEventListener("click", () => {
    video.classList.toggle("flip-h");
  });

  document.getElementById("b-cameras").addEventListener("click", () => {
    let count = 1;
    navigator.mediaDevices.enumerateDevices().then((devices) => {
      console.log(devices);
      devices.forEach((mediaDevice) => {
        if (mediaDevice.kind === "videoinput") {
          const label = mediaDevice.label || `Camera ${count++}`;
          const id = mediaDevice.deviceId;
          console.log(label, id);
        }
      });
    });
  });

  document.getElementById("b-change-camera").addEventListener("click", () => {
    const cameraIdList = GetCameras();
    currentCameraPos += 1;
    currentCameraPos = currentCameraPos % cameraIdList.length;

    console.log(`change camera ${currentCameraPos}`);

    document.getElementById("b-open-cam").click();
  });
});
