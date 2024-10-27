#include <iostream>
#include <boost/asio.hpp>
#include <server.h>

#include <string>


using boost::asio::ip::tcp;
using std::string;

string makeResponse(const string& request) {
    return "HTTP/1.1 200 OK\nContent-Length: 13\nContent-Type: text/plain\n\nHello, world!";
}
int main() {
    try {
        // Initialize server on port 8080
        Server server(8080);

        // Start the server
        server.start();

        // Run the I/O context to perform asynchronous operations
        server.run();
    } catch (std::exception& e) {
        std::cerr << "Server Exception: " << e.what() << std::endl;
    }

    return 0;
}