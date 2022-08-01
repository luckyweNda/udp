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

    /**
     * sync receive after this time will break
     * 
     * @param time      time you want to wait for the receive
     */
    void set_timeout(uint32_t time);

    /**
     * send a message to target host
     * 
     * @param array     the message you want to send
     * @param length    message length
     */
    void send(unsigned char* array, size_t length);
    void send(const unsigned char* array, size_t length);

    /**
     * sync receive from socket
     * 
     * @param p             an unsigned char address to store result
     * @param length        max size of the address
     * @param bytes_recvd   store length of receive bytes
     */
    void receive(unsigned char* p, size_t length, size_t& bytes_recvd);
};



} // namespace udp
} // namespace cialloo

#endif // CIALLOO_UDP_HPP