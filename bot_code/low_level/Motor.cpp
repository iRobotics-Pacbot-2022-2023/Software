#include <Arduino.h>
#include <Encoder.h>

#include <Motor.h>

// some rough testing suggests min 5k based on electrical time constant
#define FREQ 10000
#define RES 15

Motor::Motor(uint8_t ph, uint8_t en): ph(ph), en(en) {
    pinMode(en, OUTPUT);
    pinMode(ph, OUTPUT);
    
    analogWriteFrequency(en, FREQ);
    analogWriteResolution(RES);
}

void Motor::setThrottle(int16_t throttle) {
    if (throttle > 0) {
        digitalWrite(ph, HIGH);
        analogWrite(en, throttle);
    } else {
        digitalWrite(ph, LOW);
        analogWrite(en, -throttle);
    }
    Serial.printf("%hd\n", throttle);
}