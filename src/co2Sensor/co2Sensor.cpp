#include "co2Sensor.hpp"

#define TXD_PIN GPIO_NUM_17
#define RXD_PIN GPIO_NUM_18
#define UART_NUM 1
#define BAUDRATE 9600

#define UPDATE_PERIOD 2000
#define AUTOLABIRATION_PERIOD 12e5

Co2Sensor::Co2Sensor() {
    _last_updated = 0;
    _co2_value = 0;
    _temp_value = 0;

    _sensor = new MHZ19();
    _serial = new HardwareSerial(UART_NUM);

    init();
}

Co2Sensor::~Co2Sensor() {
    delete _sensor;
    delete _serial;
}

void Co2Sensor::init() {
    _serial->begin(BAUDRATE, SERIAL_8N1, RXD_PIN, TXD_PIN);
    _sensor->begin(*_serial);

    _sensor->autoCalibration();
}

void Co2Sensor::update(bool debugPrint) {
    if ((millis() - _last_updated) >= UPDATE_PERIOD) {
        _co2_value = _sensor->getCO2();
        _temp_value = _sensor->getTemperature();

        if (debugPrint) {
            printCO2ToSerial();
            printTemptToSerial();
        }

        _last_updated = millis();
    }
}

void Co2Sensor::calibrate() {
    _sensor->autoCalibration(false);

    Serial.print("ABC Status: "); 
    _sensor->getABC() ? Serial.println("ON") :  Serial.println("OFF");

    Serial.println("Waiting alot of minutes to stabalise...");

    delay(AUTOLABIRATION_PERIOD);

    Serial.println("Calibrating..");

    _sensor->calibrate();
}

int Co2Sensor::getCO2() {
    return _co2_value;
}

int8_t Co2Sensor::getTemp() {
    return _temp_value;
}

void Co2Sensor::printFirmwareVersionToSerial() {
    char version[4];          
    _sensor->getVersion(version);

    Serial.print("\nCO2 firmware version: ");
    for(byte i = 0; i < 4; i++)
    {
        Serial.print(version[i]);
        if(i == 1)
        Serial.print(".");    
    }

    Serial.println();
}

void Co2Sensor::printCO2ToSerial() {
    Serial.print("CO2 ppm: ");
    Serial.println(_co2_value);
}

void Co2Sensor::printTemptToSerial() {
    Serial.print("CO2 temp: ");
    Serial.println(_temp_value);
}