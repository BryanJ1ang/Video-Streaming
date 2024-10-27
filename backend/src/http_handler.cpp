#include "http_handler.h"
#include <iostream>
#include <sstream>

void HTTPHandler::handle_request(std::shared_ptr<boost::asio::ip::tcp::socket> socket, VideoTransmission& video_transmission) {
    auto buffer = std::make_shared<boost::asio::streambuf>();
    boost::system::error_code error;

    // Read the request
    boost::asio::read_until(*socket, *buffer, "\r\n\r\n", error);
    if (error && error != boost::asio::error::eof) {
        std::cerr << "Read error: " << error.message() << std::endl;
        return;
    }

    std::istream request_stream(buffer.get());
    std::string method, uri;
    parse_request(*buffer, method, uri);

    std::cout << "Request: " << method << " " << uri << std::endl;

    if (method == "GET") {
        if (uri.find("/videos/") == 0) {
            // Handle video streaming
            video_transmission.stream_video(socket, uri);
        } else {
            // Handle other GET requests (e.g., static files)
            std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello from HTTPHandler!";
            send_response(socket, response);
        }
    } else {
        // Method not supported
        std::string response = "HTTP/1.1 405 Method Not Allowed\r\nContent-Length: 0\r\n\r\n";
        send_response(socket, response);
    }
}

void HTTPHandler::parse_request(boost::asio::streambuf& buffer, std::string& method, std::string& uri) {
    std::istream request_stream(&buffer);
    std::string request_line;
    std::getline(request_stream, request_line);
    std::istringstream iss(request_line);
    iss >> method >> uri;
}

void HTTPHandler::send_response(std::shared_ptr<boost::asio::ip::tcp::socket> socket, const std::string& response) {
    boost::asio::write(*socket, boost::asio::buffer(response));
}