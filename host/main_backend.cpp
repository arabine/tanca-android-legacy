/**
 * MIT License
 * Copyright (c) 2019 Anthony Rabine
 */

#include <cstring>
#include <pthread.h>
#include <cassert>

#include "http_server.h"

http_server server;


#include <boost/asio.hpp>

bool port_in_use(unsigned short port) {
    using namespace boost::asio;
    using ip::tcp;

    io_service svc;
    tcp::acceptor a(svc);

    boost::system::error_code ec;
    a.open(tcp::v4(), ec) || a.bind({ tcp::v4(), port }, ec);

    return ec == error::address_in_use;
}


int main()
{
    std::cout << "[TANCA] Starting Tanca server" << std::endl;
    uint16_t tcpPort = 42422;

    try {


        bool foundFreePort = false;
        do {

            // foundFreePort = tcpServer.Start(10, true, tcpPort, tcpPort + 1);


            if (port_in_use(tcpPort)) {
                tcpPort++;
            } else {
                foundFreePort = true;
            }
        } while (!foundFreePort);

        std::cout << "[TANCA] TCP server started on port: " << std::to_string(tcpPort) << std::endl;
        server.start(tcpPort);

    }
    catch(std::exception const&  ex)
    {
        printf("[TANCA] Exception: %s", ex.what());
    }





    for(;;)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
