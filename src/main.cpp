#include <Arduino.h>
#include "server/CSServer.hpp"
#include "co2Sensor/co2Sensor.hpp"
#include "dht22Sensor/dht22Sensor.hpp"

CSServer *server;
Co2Sensor *co2Sensor;
DHT22Sensor *dht22Sensor;

void setup() {
    Serial.begin(9600);

    server = new CSServer();
    co2Sensor = new Co2Sensor();
    dht22Sensor = new DHT22Sensor();

    co2Sensor->printFirmwareVersionToSerial();
    dht22Sensor->printSensorInfoToSerial();
}

void loop() {
    co2Sensor->update(true);
    dht22Sensor->update(true);
}