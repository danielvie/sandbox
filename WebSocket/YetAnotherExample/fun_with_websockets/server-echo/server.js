
const WebSocket = require('ws')
const PORT = 3000

const wsserver = new WebSocket.Server({
    port: PORT
})

wsserver.on('connection', (socket) => {
    // feedback on the console
    console.log('a client just connected')
    
    // attach some behavior to the incoming socket
    socket.on('message', (msg) => {
        console.log(`received message from client: ${msg}`)
        // socket.send("take this back: " + msg)
        
        // broadcast message to all connected clients
        wsserver.clients.forEach((client) => {
            client.send(`take this back: ${msg}`)
        })
    })
    
    // feedback on disconnect
    socket.on('close', (el) => {
        console.log("[close]")
    })
})

console.log(`${new Date()} Server is listening on port ${PORT}`)