// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

// Import libraries (BLEPeripheral depends on SPI)
#include <Arduino.h>
#include <SPI.h>
#include <BLEPeripheral.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "git-version.h"

#define UUID_end "e8f2537e4f6cd104768a1214"
#define UUID0 "19b10000" UUID_end
#define UUID1 "19b10001" UUID_end

// LED pin
#define LED_PIN         20  //P0.20     LED2
#define ONE_WIRE_BUS    0   //P0.00     SDA

#define VERSION "V0.0.0"
const char* commit_ID = GIT_COMMIT_ID;
#pragma message ("TIME: " __DATE__ " " __TIME__ " Version: " VERSION )

// create peripheral instance, see pinouts above
BLEPeripheral            blePeripheral        = BLEPeripheral();

// create service
BLEService               ledService           = BLEService(UUID0);

// create switch characteristic
BLECharCharacteristic    switchCharacteristic = BLECharCharacteristic(UUID1, BLERead | BLEWrite);

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

int numberOfDevices; // Number of temperature devices found

void setup() {
    Serial.begin(9600);
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
    blePeripheral.setAdvertisedServiceUuid(ledService.uuid());

    // add service and characteristic
    blePeripheral.addAttribute(ledService);
    blePeripheral.addAttribute(switchCharacteristic);

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
            // central wrote new value to characteristic, update LED
            if (switchCharacteristic.value()) {
            Serial.println(F("LED on"));
            digitalWrite(LED_PIN, HIGH);
            } else {
            Serial.println(F("LED off"));
            digitalWrite(LED_PIN, LOW);
            }
            sensors.requestTemperatures();
            Serial.println("Temperature: " + String(sensors.getTempCByIndex(0)));
        }
        }

    // central disconnected
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
    }
}
