/**
 * MIT License
 * Copyright (c) 2019 Anthony Rabine
 */

#include <cstring>
#include <pthread.h>
#include <jni.h>
#include <android/log.h>
#include <cassert>

#include "http_server.h"

//static BackendServer gBackendServer;
//static tcp::TcpServer tcpServer(gBackendServer);

http_server server;


// Android log function wrappers
static const char* kTAG = "TancaLog";
#define LOGI(...) \
  ((void)__android_log_print(ANDROID_LOG_INFO, kTAG, __VA_ARGS__))
#define LOGW(...) \
  ((void)__android_log_print(ANDROID_LOG_WARN, kTAG, __VA_ARGS__))
#define LOGE(...) \
  ((void)__android_log_print(ANDROID_LOG_ERROR, kTAG, __VA_ARGS__))

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


extern "C" {

/*
 * Interface to Java side to initialize the file server at startup
 */
JNIEXPORT jint JNICALL
Java_eu_d8s_Tanca_MainActivity_initialize(JNIEnv *env, jobject instance) {
    LOGI("[TANCA] Starting Tanca server");
    jint tcpPort = 42422;

    try {


        bool foundFreePort = false;
        do {

            // foundFreePort = tcpServer.Start(10, true, tcpPort, tcpPort + 1);
            LOGI("[TANCA] TCP server started");

            if (port_in_use(tcpPort)) {
                tcpPort++;
            } else {
                foundFreePort = true;
            }
        } while (!foundFreePort);

        server.start(tcpPort);

    }
    catch(std::exception const&  ex)
    {
        LOGE("[TANCA] Exception: %s", ex.what());
    }



    return tcpPort;
}

}
