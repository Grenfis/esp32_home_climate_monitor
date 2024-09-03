#ifndef CSSERVER_HPP
#define CSSERVER_HPP

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

class CSServer {
private:
    AsyncWebServer *_server;

public:
    CSServer();
    ~CSServer();

private:
    void init();
};

#endif