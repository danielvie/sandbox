#include <iostream>
#include <libwebsockets.h>

int main() {
  // Set up the WebSocket client context
  struct lws_context_creation_info info;
  memset(&info, 0, sizeof(info));
  info.port = CONTEXT_PORT_NO_LISTEN;
  info.protocols = protocols;
  info.gid = -1;
  info.uid = -1;
  struct lws_context *context = lws_create_context(&info);

  // Connect to the WebSocket server
  struct lws *client_wsi = lws_client_connect(context, "localhost", 8080, false, "/", "localhost", "http://localhost", NULL, -1);

  // Send a message to the server
  char message[] = "Hello, server!";
  lws_write(client_wsi, (unsigned char*)message, strlen(message), LWS_WRITE_TEXT);

  // Wait for a message from the server
  char buffer[1024];
  int length = lws_read(client_wsi, (unsigned char*)buffer, sizeof(buffer), LWS_READ_TEXT);
  std::cout << "Received message: " << buffer << std::endl;

  // Clean up and exit
  lws_context_destroy(context);
  return 0;
}
