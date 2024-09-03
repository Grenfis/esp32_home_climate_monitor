#include "CSServer.hpp"
#include <ArduinoJson.h>

#define PORT 80
#define SSID "Ucom7632_2.4G"
#define PASSWORD "SakhCom2022"

CSServer::CSServer(DHT22Sensor *dht22Sensor, Co2Sensor *co2Sensor) {
    _server = new AsyncWebServer(PORT);
    _co2_sensor = co2Sensor;
    _dht22_sensor = dht22Sensor;

    init();
}

CSServer::~CSServer() {
    delete _server;
}

void CSServer::init() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, PASSWORD);

    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.printf("WiFi Failed!\n");
        return;
    }

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    registerRoutes();

    _server->begin();
}

void CSServer::registerRoutes() {
    _server->on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "Welcome to home climate station");
    });

    _server->on("/api/dashboard", HTTP_GET, [this](AsyncWebServerRequest *request){
        JsonDocument doc;

        char tempBuf[5];
        sprintf(tempBuf, "%.2f", this->_dht22_sensor->getTemp());
        String tempStr(tempBuf);

        char humBuf[5];
        sprintf(humBuf, "%.2f", this->_dht22_sensor->getHumidity());
        String humStr(humBuf);

        char heatBuf[5];
        sprintf(heatBuf, "%.2f", this->_dht22_sensor->getHeatIndex());
        String heatStr(heatBuf);

        doc["co2"] = this->_co2_sensor->getCO2();
        doc["co2Temp"] = this->_co2_sensor->getTemp();
        doc["humidity"] = humStr;
        doc["temp"] = tempStr;
        doc["heatIndex"] = heatStr;

        String result;

        serializeJsonPretty(doc, result);

        request->send(200, "application/json", result);
    });
}