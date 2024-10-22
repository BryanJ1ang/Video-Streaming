#include "video_transmission.h"
#include <fstream>
#include <iostream>

void VideoTransmission::stream_video(std::shared_ptr<boost::asio::ip::tcp::socket> socket, const std::string& uri) {
    std::string file_path = get_video_path(uri);
    std::ifstream video_file(file_path, std::ios::binary | std::ios::ate);

    if (!video_file.is_open()) {
        std::string not_found = "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n";
        boost::asio::write(*socket, boost::asio::buffer(not_found));
        return;
    }

    std::streamsize file_size = video_file.tellg();
    video_file.seekg(0, std::ios::beg);

    // Simple response without byte-range support
    std::string header = "HTTP/1.1 200 OK\r\nContent-Type: video/mp4\r\nContent-Length: " + std::to_string(file_size) + "\r\n\r\n";
    boost::asio::write(*socket, boost::asio::buffer(header));

    // Send the file in chunks
    const std::size_t buffer_size = 8192;
    char buffer[buffer_size];
    while (video_file.read(buffer, buffer_size) || video_file.gcount() > 0) {
        boost::asio::write(*socket, boost::asio::buffer(buffer, video_file.gcount()));
    }
}

std::string VideoTransmission::get_video_path(const std::string& uri) {
    // Simple mapping from URI to file path
    // e.g., "/videos/sample.mp4" -> "videos/sample.mp4"
    return "." + uri;
}
