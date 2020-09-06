//Waveshare_BLE400 pio doc: https://docs.platformio.org/en/latest/boards/nordicnrf51/waveshare_ble400.html
//nRF51822 platform doc:    https://docs.platformio.org/en/latest/platforms/nordicnrf51.html#platform-nordicnrf51
//nRF51922 lib doc:         https://platformio.org/lib/show/2587/nRF51822
//BLEPheriperal lib:        https://platformio.org/lib/show/259/BLEPeripheral
//Arduino+nRF51822+pIO:     https://docs.platformio.org/en/latest/tutorials/nordicnrf52/arduino_debugging_unit_testing.html
//stlink debugging:         https://docs.platformio.org/en/latest/plus/debug-tools/stlink.html
//BlackMagicProbe debugging:https://docs.platformio.org/en/latest/plus/debug-tools/blackmagic.html
//Unit testing on HW:       https://docs.platformio.org/en/latest/plus/unit-testing.html

/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

#include <Arduino.h>

#define LED 20

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED, OUTPUT);
}

void loop()
{
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED, HIGH);
  // wait for a second
  delay(1000);
  // turn the LED off by making the voltage LOW
  digitalWrite(LED, LOW);
   // wait for a second
  delay(1000);
}

