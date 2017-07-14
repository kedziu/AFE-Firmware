#include "AFE-Defaults.h"                                                                                                                                       

AFEDefaults::AFEDefaults () {}

void AFEDefaults::set() {
    AFEEEPROM Eeprom;
    Eeprom.erase();
    Eeprom.write(0,7,"1.0.0");        // Version
    Eeprom.writeUInt8(7,0);           // Firmware type
    Eeprom.writeUInt8(8,0);           // Language
    Eeprom.write(9,16,"AFE-DEVICE");  // Device name
    Eeprom.write(25,false);           // Debugger
    Eeprom.writeUInt8(26,0);          // Device mode

    Eeprom.write(27,false);           // Auto update
    Eeprom.write(28,120,"https://api.czabanowski.com");          // url

    Eeprom.write(212,true);          // DHCP config
    uint8_t ip[4] = {0,0,0,0};
    Eeprom.writeIP(213,ip);           // Device IP
    Eeprom.writeIP(217,ip);           // Gateway IP
    uint8_t subnet[4] = {255,255,255,0};
    Eeprom.writeIP(221,subnet);       // Subnet IP

    Eeprom.writeIP(257,ip);           // MQTT / Domoticz IP
    Eeprom.write(261,5,(long)1883);   // MQTT Port
    // Eeprom.write(261,5,"8080");       // Domoticz Port
    Eeprom.write(330,32,"/afedevice/");// MQTT Topic

    Eeprom.write(362,false);          // relay connected
    Eeprom.writeUInt8(364,0);         // relay state
    Eeprom.write(365,5,(long)0);      // relay time to off
    Eeprom.writeUInt8(370,2);         // Relay state after power on
    Eeprom.write(371,16,"relay");     // Relay name
    Eeprom.writeUInt8(387,0);         // Relay state after mqtt connected

    Eeprom.write(388,false);
    Eeprom.writeUInt8(390,0);
    Eeprom.writeUInt8(391,0);
    Eeprom.writeUInt8(392,0);
    Eeprom.write(393,false);
    Eeprom.write(395,5,(float)0);
    Eeprom.write(400,5,(long)60);
}
