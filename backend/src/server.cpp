#include "server.h"
#include <iostream>

Server::Server(unsigned short port)
    : acceptor_(io_context_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
      http_handler_(),
      video_transmission_() {}

void Server::start() {
    accept_connections();
}

void Server::run() {
    io_context_.run();
}

void Server::accept_connections() {
    auto socket = std::make_shared<boost::asio::ip::tcp::socket>(io_context_);
    acceptor_.async_accept(*socket, [this, socket](const boost::system::error_code& error) {
        if (!error) {
            std::cout << "New connection from: " << socket->remote_endpoint() << std::endl;
            handle_client(socket);
        } else {
            std::cerr << "Accept error: " << error.message() << std::endl;
        }
        // Continue accepting new connections
        accept_connections();
    });
}

void Server::handle_client(std::shared_ptr<boost::asio::ip::tcp::socket> socket) {
    http_handler_.handle_request(socket, video_transmission_);
}