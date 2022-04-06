#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>

class http_server
{

public:
    http_server();
    ~http_server();

    void start(unsigned short tcpPort);
    void stop();

private:
    boost::asio::io_context ioc;

    boost::asio::ip::tcp::socket socket;

    std::thread m_thread;

    unsigned short mTcpPort = 8181;

    void run();

    // "Loop" forever accepting new connections.
    void accept(boost::asio::ip::tcp::acceptor& acceptor, boost::asio::ip::tcp::socket& socket);
};




