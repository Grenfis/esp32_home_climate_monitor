#ifndef DHT22SENSOR_HPP
#define DHT22SENSOR_HPP

#include <DHT.h>
#include <DHT_U.h>

class DHT22Sensor {
private:
    DHT_Unified *_sensor;
    uint32_t _update_period;
    uint32_t _last_updated;

    float _temp;
    float _humidity;
    float _heat_index;

public:
    DHT22Sensor();
    ~DHT22Sensor();

    void update(bool debugPrint = false);

    void printSensorInfoToSerial();
    void printTempToSerial();
    void printHumidityToSerial();
    void printHeatIndexToSerial();

    float getHumidity();
    float getTemp();
    float getHeatIndex();

private:
    void init();

    void computeHeatIndex();
    static float convertCtoF(float c);
    static float convertFtoC(float f);
};

#endif