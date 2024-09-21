#include <Arduino.h>
#include "server/CSServer.hpp"
#include "co2Sensor/co2Sensor.hpp"
#include "dht22Sensor/dht22Sensor.hpp"

CSServer *server;
Co2Sensor *co2Sensor;
DHT22Sensor *dht22Sensor;

void setup() {
    Serial.begin(9600);

    co2Sensor = new Co2Sensor();
    dht22Sensor = new DHT22Sensor();

    server = new CSServer(dht22Sensor, co2Sensor);

    co2Sensor->printFirmwareVersionToSerial();
}

void loop() {
    co2Sensor->update();
    dht22Sensor->update();
}