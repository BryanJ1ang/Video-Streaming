#ifndef HTTPHANDLER_HPP
#define HTTPHANDLER_HPP

#include <boost/asio.hpp>
#include <memory>
#include "video_transmission.h"

class HTTPHandler {
public:
    void handle_request(std::shared_ptr<boost::asio::ip::tcp::socket> socket, VideoTransmission& video_transmission);

private:
    void parse_request(boost::asio::streambuf& buffer, std::string& method, std::string& uri);
    void send_response(std::shared_ptr<boost::asio::ip::tcp::socket> socket, const std::string& response);
};

#endif // HTTPHANDLER_HPP