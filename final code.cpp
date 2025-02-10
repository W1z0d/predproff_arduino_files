#include <Servo.h>

int val;
const int led = 13;
bool is_catch = 0, is_rotate = 0;

Servo rotate, cat;

void setup() {
    Serial1.begin(9600);
    pinMode(6, OUTPUT); // M1+
    pinMode(7, OUTPUT); // M1- 
    pinMode(46, OUTPUT); // M2+
    pinMode(45, OUTPUT); // M2-
    rotate.attach(5);
    cat.attach(2);
}

void open_manip(bool is) {
    cat.writeMicroseconds(1500 + 500 * is - 500 * !is);
    delay(75);
    cat.writeMicroseconds(1500);
}

void rotate_manip(bool is) {
    rotate.writeMicroseconds(1500 + 500 * is - 500 * !is);
    delay(100);
    rotate.writeMicroseconds(1500);
}

void change_speed(int speed1, int speed2) {
  analogWrite(6, speed1 * (speed1 > 0));
  analogWrite(7, -1 * speed1 * (speed1 < 0));

  analogWrite(45, speed2 * (speed2 > 0));
  analogWrite(46, -1 * speed2 * (speed2 < 0));
}

void loop() {
    if (Serial1.available()) {
        val = Serial1.read();
        if (val == '0') {
            change_speed(0, 0);
            delay(100);
        } else if (val == '1') {
            change_speed(255, 255);
            delay(100);
        } else if (val == '2') {
            change_speed(-255, -255);
            delay(100);
        } else if (val == '3') {
            change_speed(-255, 255);
            delay(100);
        } else if (val == '4') {
            change_speed(255, -255);
            delay(100);
        } else if (val == '9') {
            open_manip(is_catch);
            is_catch -= 1;
            delay(100);
        } else if (val == '8') {
            rotate_manip(is_rotate);
            is_rotate -= 1;
            delay(100);
        }
    }
}
