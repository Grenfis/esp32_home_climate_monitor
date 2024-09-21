#include "dht22Sensor.hpp"

#define DHT_PIN GPIO_NUM_35
#define DHT_TYPE DHT22

DHT22Sensor::DHT22Sensor() {
    _sensor = new DHT_Unified(DHT_PIN, DHT_TYPE);
    _last_updated = 0;
    _update_period = 0;
    _temp = 0;
    _humidity = 0;
    _heat_index = 0;

    init();
}

DHT22Sensor::~DHT22Sensor() {
    delete _sensor;
}

void DHT22Sensor::init() {
    _sensor->begin();

    sensor_t sensor;

    _sensor->temperature().getSensor(&sensor);
    _update_period = sensor.min_delay / 1000;
}

void DHT22Sensor::printSensorInfoToSerial() {
    sensor_t sensor;

    _sensor->temperature().getSensor(&sensor);
    Serial.println(F("------------------------------------"));
    Serial.println(F("Temperature Sensor"));
    Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
    Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
    Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
    Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
    Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
    Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
    Serial.println(F("------------------------------------"));


    _sensor->humidity().getSensor(&sensor);
    Serial.println(F("Humidity Sensor"));
    Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
    Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
    Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
    Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
    Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
    Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
    Serial.println(F("------------------------------------"));
}

void DHT22Sensor::update(bool printDebug) {
    if ((millis() - _last_updated) >= _update_period) {
        sensors_event_t event;

        _sensor->temperature().getEvent(&event);

        if (!isnan(event.temperature)) {
            _temp = event.temperature;
        }

        _sensor->humidity().getEvent(&event);

        if (!isnan(event.relative_humidity)) {
            _humidity = event.relative_humidity;
        }

        computeHeatIndex();

        if (printDebug) {
            printTempToSerial();
            printHumidityToSerial();
            printHeatIndexToSerial();
        }

        _last_updated = millis();
    }
}

void DHT22Sensor::printTempToSerial() {
    Serial.print("Temp: ");
    Serial.print(_temp);
    Serial.println("C");
}

void DHT22Sensor::printHumidityToSerial() {
    Serial.print("Humidity: ");
    Serial.print(_humidity);
    Serial.println("%");
}

void DHT22Sensor::printHeatIndexToSerial() {
    Serial.print("Heat index: ");
    Serial.print(_heat_index);
    Serial.println("C");
}

void DHT22Sensor::computeHeatIndex() {
    float hi;

    float temperature = convertCtoF(_temp);

    hi = 0.5 * (temperature + 61.0 + ((temperature - 68.0) * 1.2) +
              (_humidity * 0.094));

    if (hi > 79) {
        hi = -42.379 + 2.04901523 * temperature + 10.14333127 * _humidity +
            -0.22475541 * temperature * _humidity +
            -0.00683783 * pow(temperature, 2) +
            -0.05481717 * pow(_humidity, 2) +
            0.00122874 * pow(temperature, 2) * _humidity +
            0.00085282 * temperature * pow(_humidity, 2) +
            -0.00000199 * pow(temperature, 2) * pow(_humidity, 2);

        if ((_humidity < 13) && (temperature >= 80.0) &&
            (temperature <= 112.0))
        hi -= ((13.0 - _humidity) * 0.25) *
                sqrt((17.0 - abs(temperature - 95.0)) * 0.05882);

        else if ((_humidity > 85.0) && (temperature >= 80.0) &&
                (temperature <= 87.0))
        hi += ((_humidity - 85.0) * 0.1) * ((87.0 - temperature) * 0.2);
    }

    _heat_index = convertFtoC(hi);
}

float DHT22Sensor::convertCtoF(float c) {
    return c * 1.8 + 32;
}

float DHT22Sensor::convertFtoC(float f) {
    return (f - 32) * 0.55555;
}

float DHT22Sensor::getHumidity() {
    return _humidity;
}

float DHT22Sensor::getTemp() {
    return _temp;
}

float DHT22Sensor::getHeatIndex() {
    return _heat_index;
}