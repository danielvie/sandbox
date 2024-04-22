cmake_minimum_required(VERSION 3.10)
project(websocket_client)

find_package(libwebsockets REQUIRED)

add_executable(websocket_client client.cpp)

link_directories(/opt/homebrew/Cellar/libwebsockets/4.3.2/lib)
target_link_libraries(websocket_client PRIVATE libwebsockets::libwebsockets)
