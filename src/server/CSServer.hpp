#ifndef CSSERVER_HPP
#define CSSERVER_HPP

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "../co2Sensor/co2Sensor.hpp"
#include "../dht22Sensor/dht22Sensor.hpp"

class CSServer {
private:
    AsyncWebServer *_server;
    DHT22Sensor *_dht22_sensor;
    Co2Sensor *_co2_sensor;

public:
    CSServer(DHT22Sensor *dht22Sensor, Co2Sensor *co2Sensor);
    ~CSServer();

private:
    void init();
    void registerRoutes();
};

#endif