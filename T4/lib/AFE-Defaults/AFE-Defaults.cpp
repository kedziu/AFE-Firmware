/* AFE Firmware for smart home devices
  LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: http://smart-house.adrian.czabanowski.com/afe-firmware-pl/ */

#include "AFE-Defaults.h"

AFEDefaults::AFEDefaults() {}

void AFEDefaults::set() {

  AFEDataAccess *Data;

  DEVICE deviceConfiguration;
  FIRMWARE firmwareConfiguration;
  NETWORK networkConfiguration;
  MQTT MQTTConfiguration;
  RELAY RelayConfiguration;
  SWITCH SwitchConfiguration;
  LED LEDConfiguration;

  sprintf(firmwareConfiguration.version, FIRMWARE_VERSION);
  firmwareConfiguration.type = FIRMWARE_TYPE;
  firmwareConfiguration.autoUpgrade = 0;
  sprintf(firmwareConfiguration.upgradeURL, "");

  Data->saveConfiguration(firmwareConfiguration);

  // Serial << endl << "firmwareConfiguration";
  sprintf(deviceConfiguration.name, "AFE-Device");

  deviceConfiguration.isLED[0] = true;
  for (uint8_t i = 1; i < sizeof(deviceConfiguration.isLED); i++) {
    deviceConfiguration.isLED[i] = false;
  }

  for (uint8_t i = 0; i < sizeof(deviceConfiguration.isSwitch) - 1; i++) {
    deviceConfiguration.isSwitch[i] = true;
  }

  deviceConfiguration.isSwitch[sizeof(deviceConfiguration.isSwitch) - 1] =
      false;

  for (uint8_t i = 0; i < sizeof(deviceConfiguration.isRelay); i++) {
    deviceConfiguration.isRelay[i] = true;
  }

  deviceConfiguration.mqttAPI = false;
  deviceConfiguration.httpAPI = true;

  Data->saveConfiguration(deviceConfiguration);

  sprintf(networkConfiguration.ssid, "");
  sprintf(networkConfiguration.password, "");
  networkConfiguration.isDHCP = true;
  networkConfiguration.ip = IPAddress(0, 0, 0, 0);
  networkConfiguration.gateway = IPAddress(0, 0, 0, 0);
  networkConfiguration.subnet = IPAddress(255, 255, 255, 0);
  networkConfiguration.noConnectionAttempts = 10;
  networkConfiguration.waitTimeConnections = 1;
  networkConfiguration.waitTimeSeries = 60;

  Data->saveConfiguration(networkConfiguration);
  //  Serial << endl << "networkConfiguration";

  sprintf(MQTTConfiguration.host, "");
  MQTTConfiguration.ip = IPAddress(0, 0, 0, 0);
  sprintf(MQTTConfiguration.user, "");
  sprintf(MQTTConfiguration.password, "");
  MQTTConfiguration.port = 1883;
  sprintf(MQTTConfiguration.topic, "/device/");

  Data->saveConfiguration(MQTTConfiguration);

  RelayConfiguration.timeToOff = 0;
  RelayConfiguration.statePowerOn = 3;
  RelayConfiguration.stateMQTTConnected = 0;
  RelayConfiguration.ledID = 0;

  RelayConfiguration.gpio = 12;
  sprintf(RelayConfiguration.name, "switch1");
  Data->saveConfiguration(0, RelayConfiguration);

  RelayConfiguration.gpio = 5;
  sprintf(RelayConfiguration.name, "switch2");
  Data->saveConfiguration(1, RelayConfiguration);

  RelayConfiguration.gpio = 4;
  sprintf(RelayConfiguration.name, "switch3");
  Data->saveConfiguration(2, RelayConfiguration);

  RelayConfiguration.gpio = 15;
  sprintf(RelayConfiguration.name, "switch4");
  Data->saveConfiguration(3, RelayConfiguration);

  for (uint8_t i = 0; i < sizeof(deviceConfiguration.isRelay); i++) {
    Data->saveRelayState(i, false);
  }

  SwitchConfiguration.type = 0;
  SwitchConfiguration.sensitiveness = 50;

  SwitchConfiguration.gpio = 0;
  SwitchConfiguration.functionality = 0;
  SwitchConfiguration.relayID = 1;
  Data->saveConfiguration(0, SwitchConfiguration);

  SwitchConfiguration.gpio = 9;
  SwitchConfiguration.functionality = 1;
  SwitchConfiguration.relayID = 2;
  Data->saveConfiguration(1, SwitchConfiguration);

  SwitchConfiguration.gpio = 10;
  SwitchConfiguration.relayID = 3;
  Data->saveConfiguration(2, SwitchConfiguration);

  SwitchConfiguration.gpio = 14;
  SwitchConfiguration.relayID = 4;
  Data->saveConfiguration(3, SwitchConfiguration);

  LEDConfiguration.gpio = 13;
  LEDConfiguration.changeToOppositeValue = false;
  for (uint8_t i = 0; i < sizeof(deviceConfiguration.isLED); i++) {
    Data->saveConfiguration(i, LEDConfiguration);
  }

  Data->saveSystemLedID(1);

  Data->saveDeviceMode(2);
  Data->saveLanguage(1);
}

void AFEDefaults::eraseConfiguration() { Eeprom.erase(); }
