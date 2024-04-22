import websocket

# Connect to the WebSocket server
ws = websocket.WebSocket()
ws.connect("ws://localhost:3000")

# Send a message to the server
ws.send("Hello, server! (from python)")

# Wait for a response from the server
response = ws.recv()
print(response)

# Close the connection
ws.close()
