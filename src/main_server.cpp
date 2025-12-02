// chat_project/src/main_server.cpp
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

const int CHAT_PORT = 12345;

void handle_connection(tcp::socket socket) {
    try {

        for (;;) {

            char data[1024];
            

            boost::system::error_code error;
            size_t length = socket.read_some(boost::asio::buffer(data), error);
            
            // หาก Client ตัดการเชื่อมต่อ จะเกิด error::eof
            if (error == boost::asio::error::eof) {
                std::cout << "Client disconnected." << std::endl;
                break;
            } else if (error) {
                // error 
                throw boost::system::system_error(error);
            }


            std::cout << "Received from client: " << std::string(data, length) << std::endl;
            

            boost::asio::write(socket, boost::asio::buffer(data, length));
        }
    } catch (std::exception& e) {
        std::cerr << "Exception in session: " << e.what() << std::endl;
    }
}

int main() {
    try {
        // io_context 
        boost::asio::io_context io_context;

        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), CHAT_PORT));

        std::cout << "Chat Server started. Listening on port " << CHAT_PORT << "..." << std::endl;

        for (;;) {

            tcp::socket socket(io_context);
            acceptor.accept(socket);

            std::cout << "New client connected! Handling connection..." << std::endl;

            handle_connection(std::move(socket));
        }
    } catch (std::exception& e) {
        std::cerr << "Exception in server: " << e.what() << std::endl;
    }

    return 0;
}