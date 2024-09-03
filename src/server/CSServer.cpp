#include "CSServer.hpp"

#define PORT 80
#define SSID "Ucom7632_2.4G"
#define PASSWORD "SakhCom2022"

CSServer::CSServer() {
    _server = new AsyncWebServer(PORT);

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

    _server->on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "Hello, world");
    });

    _server->begin();
}