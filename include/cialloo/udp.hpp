#ifndef CIALLOO_UDP_HPP
#define CIALLOO_UDP_HPP

#include <boost/asio.hpp>
#include <string>

#define UDP_DEFAULT_TIMEOUT 200      // ms

namespace cialloo {
namespace udp {

namespace net = boost::asio;

class client
{
    uint32_t timeout_;
    net::io_context io_;
    net::ip::udp::socket socket_;
    net::ip::udp::endpoint endpoint_;
    net::ip::udp::resolver resolver_;
    net::ip::udp::resolver::results_type results_type_;
public:
    client(std::string host, std::string port);
    ~client();
    client(const client&) = delete;
    client operator=(const client&) = delete;

    void set_timeout(uint32_t time);
    void send(unsigned char* array, size_t length);
    void send(const unsigned char* array, size_t length);
    void receive(unsigned char* p, size_t length);
};



} // namespace udp
} // namespace cialloo

#endif // CIALLOO_UDP_HPP