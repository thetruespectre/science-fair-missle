#include <Servo.h>
//#include <Wire.h>

Servo servo1;
Servo servo2;
int angle = 0;
bool active;
const int addr = 9;

void setup() {
  // put your setup code here, to run once:
  servo1.attach(3);
  servo2.attach(6);
  servo1.write(90);
  servo2.write(90);
  Serial.begin(9600);
  //Wire.begin(addr);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Wire.onReceive(fire);
  while (Serial.available() > 0){
    angle = Serial.read();
    fire();
  }
}

void fire() {
  /*
  while (Wire.available() > 0) {
    angle = Wire.read();
  }
  */

  servo1.write(angle);
  angle = 0;
}