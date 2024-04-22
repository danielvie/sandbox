const http = require('http');
const WebSocket = require('ws');

const server = http.createServer((req, res) => {
  res.writeHead(200, { 'Content-Type': 'text/html' });
  res.write('<h1>WebSocket Server</h1>');
  res.end();
});

const wss = new WebSocket.Server({ server });

let cont = 0
wss.on('connection', (ws) => {
  console.log('WebSocket connection established');

  ws.on('message', (message) => {
    let res = `${message}; (${++cont})`
    console.log(`Received message: ${res}`);
    ws.send(`Echo: ${res}`);
  });

  ws.on('close', () => {
    console.log('WebSocket connection closed');
  });
});

server.listen(3000, () => {
  console.log('WebSocket server listening on port 3000');
});
