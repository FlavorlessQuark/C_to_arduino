#define ARDUINO_ARCH_AVR 1
#include <Servo/src/Servo.h>
#include <HardwareSerial.h>
#include <avr/io.h>
#include "../includes/arm.hpp"

void setup () {
    // Do Setup here

    Serial.begin(9600);
}



void loop () {
    // do loop stuff here
}

int main () {
    setup();
    while (42) {
        loop();
    }
}
