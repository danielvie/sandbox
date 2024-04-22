#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>

using namespace boost::asio;
using namespace boost::beast;
using namespace boost::beast::websocket;

int main(int argc, char* argv[])
{
    try
    {
        // Create the io_context
        io_context ioc;

        // Create the resolver and resolve the endpoint
        ip::tcp::resolver resolver{ioc};
        auto const results = resolver.resolve("localhost", "3000");
        
        // Connect to the first endpoint in the list
        stream<tcp_stream> ws{ioc};
        ws.next_layer().connect(results);

        // perform WebSocket handshake
        ws.handshake("localhost", "/");
        
        // Send a message
        ws.write(boost::asio::buffer("Hello, Mado (from cpp)!!!!!"));

        // Receive a message
        multi_buffer buffer;
        ws.read(buffer);

        // Print the message
        std::cout << boost::beast::buffers(buffer.data()) << std::endl;

        // Close the WebSocket connection
        ws.close(websocket::close_code::normal);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
