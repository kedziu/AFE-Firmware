/* AFE Firmware for smart home devices
  LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: http://smart-house.adrian.czabanowski.com/afe-firmware-pl/ */

#include "AFE-Sensor-DHT.h"

AFESensorDHT::AFESensorDHT(){};

void AFESensorDHT::begin() {
  AFEDataAccess Data;
  configuration = Data.getDHTConfiguration();
  _initialized = true;
}

float AFESensorDHT::getTemperature() {
  DHT dht(configuration.gpio, configuration.type == 1
                                  ? DHT11
                                  : configuration.type == 2 ? DHT21 : DHT22);
  dht.begin();
  return dht.readTemperature(configuration.temperature.unit == 0 ? false
                                                                 : true) +
         configuration.temperature.correction;
}

float AFESensorDHT::getHumidity() {
  DHT dht(configuration.gpio, configuration.type == 1
                                  ? DHT11
                                  : configuration.type == 2 ? DHT21 : DHT22);
  dht.begin();
  return dht.readHumidity() + configuration.humidity.correction;
}

float AFESensorDHT::getLatestTemperature() {
  temperatureInBuffer = false;
  return currentTemperature;
}

float AFESensorDHT::getLatestHumidity() {
  humidityInBuffer = false;
  return currentHumidity;
}

float AFESensorDHT::getHeatIndex() {
  DHT dht(configuration.gpio, configuration.type == 1
                                  ? DHT11
                                  : configuration.type == 2 ? DHT21 : DHT22);
  dht.begin();
  return dht.computeHeatIndex(currentTemperature, currentHumidity,
                              configuration.temperature.unit == 0 ? false
                                                                  : true);
}

boolean AFESensorDHT::temperatureSensorReady() {
  if (temperatureInBuffer) {
    return true;
  } else {
    return false;
  }
}

boolean AFESensorDHT::humiditySensorReady() {
  if (humidityInBuffer) {
    return true;
  } else {
    return false;
  }
}

void AFESensorDHT::listener() {
  if (_initialized) {
    unsigned long currentTime = millis();

    /* This code make sure that temperature and humidity reads are not closer
     * than 4sec */
    if (temperatureCounterStartTime == 0) {
      temperatureCounterStartTime = currentTime;
      if (humidityCounterStartTime != 0) {
        if (abs((temperatureCounterStartTime +
                 configuration.temperature.interval * 1000) -
                (humidityCounterStartTime +
                 configuration.humidity.interval * 1000)) <= 4000) {
          temperatureCounterStartTime -= 5000;
        }
      }
    }

    if (humidityCounterStartTime == 0) {
      humidityCounterStartTime = currentTime;
      if (abs((temperatureCounterStartTime +
               configuration.temperature.interval * 1000) -
              (humidityCounterStartTime +
               configuration.humidity.interval * 1000)) <= 4000) {
        humidityCounterStartTime -= 5000;
      }
    }

    if (currentTime - temperatureCounterStartTime >=
        configuration.temperature.interval * 1000) {
      float newTemperature = getTemperature();
      currentTemperature = newTemperature;
      temperatureInBuffer = true;
      temperatureCounterStartTime = 0;
    }

    if (currentTime - humidityCounterStartTime >=
        configuration.humidity.interval * 1000) {
      float newHumidity = getHumidity();
      currentHumidity = newHumidity;
      humidityInBuffer = true;
      humidityCounterStartTime = 0;
    }
  }
}
