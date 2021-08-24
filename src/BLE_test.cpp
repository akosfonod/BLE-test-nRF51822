// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

// Import libraries (BLEPeripheral depends on SPI)
#include <Arduino.h>
#include <SPI.h>
#include <BLEPeripheral.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "git-version.h"
#include "settings.h"

const char* __attribute__((used)) commit_ID = GIT_COMMIT_ID;
#pragma message ("TIME: " __DATE__ " " __TIME__ " Version: " VERSION )

// create peripheral instance, see pinouts above
BLEPeripheral            blePeripheral        = BLEPeripheral();

// create service
BLEService               ledService           = BLEService(UUID0);
BLEService               temperatureService   = BLEService(UUID2);

// create characteristics
BLECharCharacteristic    switchCharacteristic               = BLECharCharacteristic(UUID1, BLERead | BLEWrite);
BLEFloatCharacteristic   temperatureCharacteristic          = BLEFloatCharacteristic(UUID3, BLERead);
BLEFloatCharacteristic   temperatureNotifyCharacteristic    = BLEFloatCharacteristic(UUID5, BLENotify);

// reacet descriptors
BLEDescriptor temperatureDescriptor = BLEDescriptor(UUID4,"Temp Celsius");


OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

int numberOfDevices; // Number of temperature devices found
float tempValue=0;
char* temperature=0;

#ifdef __PLATFORMIO_BUILD_DEBUG__
    unsigned int counter = 0;
#endif

void setup() {
    Serial.begin(BAUD);
    while (!Serial){;}
    sensors.begin();

    // set LED pin to output mode
    pinMode(LED_PIN, OUTPUT);

    numberOfDevices = sensors.getDeviceCount();
    Serial.print("Found ");
    Serial.print(numberOfDevices, DEC);
    Serial.println(" devices.");
    Serial.print("Parasite power is: "); 
    if (sensors.isParasitePowerMode()) Serial.println("ON");
    else Serial.println("OFF");

    // set advertised local name and service UUID
    blePeripheral.setLocalName("LED");
    blePeripheral.setDeviceName(DEVICE_NAME);
    blePeripheral.setAdvertisedServiceUuid(ledService.uuid());
    blePeripheral.setAdvertisedServiceUuid(temperatureService.uuid());

    // add service and characteristic
    blePeripheral.addAttribute(ledService);
    blePeripheral.addAttribute(switchCharacteristic);
    blePeripheral.addAttribute(temperatureService);
    blePeripheral.addAttribute(temperatureCharacteristic);
    blePeripheral.addAttribute(temperatureDescriptor);
    blePeripheral.addAttribute(temperatureNotifyCharacteristic);

    // begin initialization
    blePeripheral.begin();

    Serial.println(F("BLE LED Peripheral"));
    Serial.println(F(commit_ID));
}

void loop() {
    BLECentral central = blePeripheral.central();

    if (central) {
        // central connected to peripheral
        Serial.print(F("Connected to central: "));
        Serial.println(central.address());

        while (central.connected()) {
        // central still connected to peripheral
        if (switchCharacteristic.written()) {
            #ifdef __PLATFORMIO_BUILD_DEBUG__
                counter ++;
            #endif

            // central wrote new value to characteristic, update LED
            if (switchCharacteristic.value()) {
            Serial.println(F("LED on"));
            digitalWrite(LED_PIN, HIGH);
            } else {
            Serial.println(F("LED off"));
            digitalWrite(LED_PIN, LOW);
            }
            sensors.requestTemperatures();
            tempValue = sensors.getTempCByIndex(0);
            Serial.println("Temperature: " + String(tempValue));
            temperatureCharacteristic.setValue(tempValue);
            temperatureNotifyCharacteristic.setValue(tempValue);
        }
        }

    // central disconnected
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
    }
}
