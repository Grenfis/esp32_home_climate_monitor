#ifndef CO2SENSOR_HPP
#define CO2SENSOR_HPP

#include <MHZ19.h>
#include <HardwareSerial.h>

class Co2Sensor {
private:
    MHZ19 *_sensor;
    HardwareSerial *_serial;

    unsigned long _last_updated;

    int _co2_value;
    int8_t _temp_value;

public:
    Co2Sensor();
    ~Co2Sensor();

    void update(bool debugPrint = false);
    void calibrate();

    int getCO2();
    int8_t getTemp();

    void printFirmwareVersionToSerial();

    void printCO2ToSerial();
    void printTemptToSerial();

private:
    void init();
};

#endif