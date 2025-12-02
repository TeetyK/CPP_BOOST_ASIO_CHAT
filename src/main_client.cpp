// chat_project/src/main_client.cpp
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
// TEST PORT
const int CHAT_PORT = 12345;

int main(int argc, char* argv[]) {
    try {
        if (argc != 2) {
            std::cerr << "Usage: chat_client <server_ip_address>" << std::endl;
            std::cerr << "Example: chat_client 127.0.0.1" << std::endl;
            return 1;
        }

        // IP Address ของ Server รับจาห CMD
        std::string server_ip = argv[1];

        boost::asio::io_context io_context;
        tcp::socket socket(io_context);
        
        boost::asio::ip::address ip_address = boost::asio::ip::make_address(server_ip);
        tcp::endpoint endpoint(ip_address, CHAT_PORT);
        // tcp::endpoint endpoint(boost::asio::ip::address::from_string(server_ip), CHAT_PORT);

        std::cout << "Connecting to server at " << server_ip << ":" << CHAT_PORT << "..." << std::endl;
        
        socket.connect(endpoint);

        std::cout << "Connected! Start chatting (type 'exit' to quit)." << std::endl;

        for (;;) {
            std::cout << "You: ";
            std::string message;
            std::getline(std::cin, message);

            if (message == "exit") {
                break;
            }
            
            boost::asio::write(socket, boost::asio::buffer(message + "\n"));

            char reply_data[1024];
            size_t reply_length = socket.read_some(boost::asio::buffer(reply_data));
            
            std::cout << "Server echoed: " << std::string(reply_data, reply_length) << std::endl;
        }
        
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}