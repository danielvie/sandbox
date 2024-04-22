
const WebSocket = require('ws')

const serverAddress = "wss://my-websocket-server-echo.glitch.me/"

const ws = new WebSocket(serverAddress, {
    headers: {
        "user-agent": "Mozilla"
    }
})

ws.on('open', () => {
    ws.send({x: 12, y:44})
})

ws.on('message', (msg) => {
    console.log(`received message: '${msg}'`)
})