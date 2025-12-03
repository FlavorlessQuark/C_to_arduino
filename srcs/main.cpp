#define ARDUINO_ARCH_AVR 1
#include <Servo/src/Servo.h>
// ^^ the above only works if included in the compile with -I, it's not actually in the system library folder
// Exact path may vary
#include <HardwareSeri
// Same as previous, the path to this needs to be added to the compile step as it isn't in the system library directory
// unless that's where you  installed it
#include <avr/io.h>

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
