#ifndef SERVER_HPP
#define SERVER_HPP

#include <boost/asio.hpp>
#include "http_handler.h"
#include "video_transmission.h"

class Server {
public:
    Server(unsigned short port);
    void start();
    void run();

private:
    void accept_connections();
    void handle_client(std::shared_ptr<boost::asio::ip::tcp::socket> socket);

    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    HTTPHandler http_handler_;
    VideoTransmission video_transmission_;
};

#endif // SERVER_HPP