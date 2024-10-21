#include <iostream>
#include <boost/asio.hpp>

#include <string>


using boost::asio::ip::tcp;
using std::string;

string makeResponse(const string& request);

string makeResponse(const string& request) {
    return "HTTP/1.1 200 OK\nContent-Length: 13\nContent-Type: text/plain\n\nHello, world!";
}

int main() {
    try {
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8080));

        std::cout << "Server running on port 8080" << std::endl;

        while (true) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);  // Accept a connection

            boost::system::error_code error;
            boost::asio::streambuf buffer;
            boost::asio::read_until(socket, buffer, "\r\n", error);

            std::istream request_stream(&buffer);
            string request;
            std::getline(request_stream, request);
            std::cout << "Received request: " << request << std::endl;

            string response = makeResponse(request);
            boost::asio::write(socket, boost::asio::buffer(response), error);

            socket.shutdown(tcp::socket::shutdown_both, error);
            socket.close(); 
        }
    } catch (std::exception & e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}