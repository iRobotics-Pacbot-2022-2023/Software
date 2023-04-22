#include <Arduino.h>

#include "Motor.h"

Motor front_left(23, 12);
Motor front_right(11, 10);
Motor rear_left(9, 8);
Motor rear_right(6, 5);

void setup() {
    Serial.begin(115200);
}

void setThrottle(double fw_throttle, double lateral_throttle, double turn_throttle) {
    Serial.printf("fw: %f, lat: %f, turn: %f\n", fw_throttle, lateral_throttle, turn_throttle);

    double max_throttle = abs(turn_throttle) + abs(fw_throttle) + abs(lateral_throttle);
    if (max_throttle > 1) {
        turn_throttle /= max_throttle;
        fw_throttle /= max_throttle;
        lateral_throttle /= max_throttle;
    }

    double fl_throttle = fw_throttle - lateral_throttle - turn_throttle;
    double fr_throttle = -fw_throttle - lateral_throttle - turn_throttle;
    double rl_throttle = fw_throttle + lateral_throttle - turn_throttle;
    double rr_throttle = -fw_throttle + lateral_throttle - turn_throttle;

    front_left.setThrottle(fl_throttle * 0x7fffp0);
    front_right.setThrottle(fr_throttle * 0x7fffp0);
    rear_left.setThrottle(rl_throttle * 0x7fffp0);
    rear_right.setThrottle(rr_throttle * 0x7fffp0);
}

void loop() {
    unsigned long start = millis();
    while (!Serial5.available() && millis() - start < 500) {}
    if (millis() - start >= 500) {
        front_left.setThrottle(0);
        front_right.setThrottle(0);
        rear_left.setThrottle(0);
        rear_right.setThrottle(0);
        Serial.println("timeout, stopping");
        return;
    }
    Serial5.find("s\n");
    double fw_throttle = Serial5.parseFloat();
    double lateral_throttle = Serial5.parseFloat();
    double turn_throttle = Serial5.parseFloat();

    setThrottle(fw_throttle, lateral_throttle, turn_throttle);
}