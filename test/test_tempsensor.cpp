#include <Arduino.h>
#include <unity.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "git-version.h"
#include "settings.h"

// void setUp(void) {
// // set stuff up here
// }

// void tearDown(void) {
// // clean stuff up here
// }

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
float tempValue=0;

void test_tempsensor_pin_number(void) {
    TEST_ASSERT_EQUAL(0, ONE_WIRE_BUS);
}

void test_tempsensor_presence(void) {
    TEST_ASSERT_GREATER_OR_EQUAL_INT(1, sensors.getDeviceCount());
}

void test_tempsensor_value(void) {
    sensors.requestTemperaturesByIndex(0);
    tempValue = sensors.getTempCByIndex(0);
    Serial.println("Temperature: " + String(tempValue) + " C.");
    TEST_ASSERT_NOT_EQUAL(-127, tempValue);
}

void setup() {
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();    // IMPORTANT LINE!
    RUN_TEST(test_tempsensor_pin_number);

    sensors.begin();
}

uint8_t i = 0;
const uint8_t max_iterations = 5;

void loop() {
    if (i < max_iterations)
    {
        RUN_TEST(test_tempsensor_presence);
        delay(500);
        RUN_TEST(test_tempsensor_value);
        delay(500);
        i++;
    }
    else if (i == max_iterations) {
      UNITY_END(); // stop unit testing
    }
}