#ifndef VIDEOTRANSMISSION_HPP
#define VIDEOTRANSMISSION_HPP

#include <boost/asio.hpp>
#include <string>
#include <memory>

class VideoTransmission {
public:
    void stream_video(std::shared_ptr<boost::asio::ip::tcp::socket> socket, const std::string& uri);

private:
    std::string get_video_path(const std::string& uri);
    void send_video(std::shared_ptr<boost::asio::ip::tcp::socket> socket, const std::string& file_path, std::size_t start = 0, std::size_t end = 0);
};

#endif // VIDEOTRANSMISSION_HPP
