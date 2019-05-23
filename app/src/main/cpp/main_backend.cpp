/**
 * MIT License
 * Copyright (c) 2019 Anthony Rabine
 */

#include <string.h>
#include <pthread.h>
#include <jni.h>
#include <android/log.h>
#include <assert.h>

#include "BackendServer.h"


static BackendServer gBackendServer;
static tcp::TcpServer tcpServer(gBackendServer);

// Android log function wrappers
static const char* kTAG = "TancaLog";
#define LOGI(...) \
  ((void)__android_log_print(ANDROID_LOG_INFO, kTAG, __VA_ARGS__))
#define LOGW(...) \
  ((void)__android_log_print(ANDROID_LOG_WARN, kTAG, __VA_ARGS__))
#define LOGE(...) \
  ((void)__android_log_print(ANDROID_LOG_ERROR, kTAG, __VA_ARGS__))

extern "C" {

/*
 * Interface to Java side to initialize the file server at startup
 */
JNIEXPORT jint JNICALL
Java_eu_d8s_Tanca_MainActivity_initialize(JNIEnv *env, jobject instance) {
    LOGI("[TANCA] Starting Tanca server");
    jint tcpPort = 8081;

    gBackendServer.Initialize();
    tcpServer.Start(10, true, tcpPort, 8082);

    return tcpPort;
}

}
