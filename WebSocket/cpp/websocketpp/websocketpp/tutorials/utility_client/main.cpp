/*
 * Copyright (c) 2014, Peter Thorson. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the WebSocket++ Project nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL PETER THORSON BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

// **NOTE:** This file is a snapshot of the WebSocket++ utility client tutorial.
// Additional related material can be found in the tutorials/utility_client
// directory of the WebSocket++ repository.

// #include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>

#include <websocketpp/common/thread.hpp>
#include <websocketpp/common/memory.hpp>

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <sstream>

using Client = websocketpp::client<websocketpp::config::asio_tls_client>;
using ConnectionHdl = websocketpp::connection_hdl;
using SslContext = websocketpp::lib::asio::ssl::context;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;

websocketpp::lib::shared_ptr<SslContext> on_tls_init() {
  auto ctx = websocketpp::lib::make_shared<SslContext>(
      boost::asio::ssl::context::sslv23);
  return ctx;
}

void on_open(Client* client, ConnectionHdl* connection, ConnectionHdl hdl) {
  *connection = hdl;
}

void on_message(Client* client, ConnectionHdl hdl,
                websocketpp::config::asio_client::message_type::ptr msg) {
  std::cout << "< " << msg->get_payload() << std::endl;
}

void close_connection(Client* client, ConnectionHdl* connection) {
  client->close(*connection, websocketpp::close::status::normal, "done");
}

void set_tls_init_handler(Client& client) {
  client.set_tls_init_handler(websocketpp::lib::bind(&on_tls_init));
}

void set_open_handler(Client& client, ConnectionHdl* connection) {
  client.set_open_handler(
      websocketpp::lib::bind(&on_open, &client, connection, ::_1));
}

void set_message_handler(Client& client) {
  client.set_message_handler(
      websocketpp::lib::bind(&on_message, &client, ::_1, ::_2));
}

void send_message(Client* client, ConnectionHdl* connection, std::string msg) {
  client->send(*connection, msg, websocketpp::frame::opcode::text);
}

void set_url(Client& client, std::string url) {
  websocketpp::lib::error_code ec;
  auto connection = client.get_connection(url, ec);
  client.connect(connection);
}

int main() {
    
    bool done = false;
    
    std::cout << "\n\n\n\n\n";
    std::cout << "mado\n";
    std::cout << "\n\n\n\n\n";

    Client client;
    ConnectionHdl connection;


    client.init_asio();
    
    set_tls_init_handler(client);
    set_open_handler(client, &connection);
    set_message_handler(client);
    
    set_url(client, "wss://my-websocket-server-echo.glitch.me/");
    
    websocketpp::lib::thread t1(&Client::run, &client);
    
    
    // std::cout << "Name: ";
    // std::getline(std::cin, name);
    std::string input;
    
    while(!done) {
        std::getline(std::cin, input);
        
        if(input == "close")
        {
            done = true;
            close_connection(&client, &connection);
        }
        else 
        {
            std::string msg{"minha mensagem"};
            send_message(&client, &connection, msg);
        }
    }

    return 0;
}

/*

clang++ -std=c++11 -stdlib=libc++ -I/Users/zaphoyd/software/websocketpp/ -I/Users/zaphoyd/software/boost_1_55_0/ -D_WEBSOCKETPP_CPP11_STL_ step4.cpp /Users/zaphoyd/software/boost_1_55_0/stage/lib/libboost_system.a

clang++ -I/Users/zaphoyd/software/websocketpp/ -I/Users/zaphoyd/software/boost_1_55_0/ step4.cpp /Users/zaphoyd/software/boost_1_55_0/stage/lib/libboost_system.a /Users/zaphoyd/software/boost_1_55_0/stage/lib/libboost_thread.a /Users/zaphoyd/software/boost_1_55_0/stage/lib/libboost_random.a

clang++ -std=c++11 -stdlib=libc++ -I/Users/zaphoyd/Documents/websocketpp/ -I/Users/zaphoyd/Documents/boost_1_53_0_libcpp/ -D_WEBSOCKETPP_CPP11_STL_ step4.cpp /Users/zaphoyd/Documents/boost_1_53_0_libcpp/stage/lib/libboost_system.a

*/
