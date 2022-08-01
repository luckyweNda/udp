#include "cialloo/udp.hpp"
#include <string>
#include <iostream>
#include <chrono>

namespace cialloo {
namespace udp {

namespace net = boost::asio;

client::client(std::string host, std::string port)
    : socket_(io_, net::ip::udp::v4()),
      resolver_(io_),
      timeout_(UDP_DEFAULT_TIMEOUT)
{
    results_type_ = resolver_.resolve(host, port);
}

client::~client()
{
    if(socket_.is_open())
        socket_.close();
}

void client::set_timeout(uint32_t time)
{
    timeout_ = time;
}

void client::send(unsigned char* array, size_t length)
{
    send(array, length);
}

void client::send(const unsigned char* array, size_t length)
{
    socket_.send_to(net::buffer(array, length), *results_type_);
}

void client::receive(unsigned char* p, size_t length)
{
    socket_.async_receive(net::buffer(p, length), 
        [this](boost::system::error_code error, std::size_t bytes_recvd){
            if(error) std::cout << error.message() << std::endl;
        }
    );

    io_.restart();
    io_.run_for(std::chrono::milliseconds(timeout_));
    if(!io_.stopped()) socket_.cancel();
}

} // namespace udp
} // namespace cialloo