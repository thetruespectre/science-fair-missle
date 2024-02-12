#include <Servo.h>
#include <Wire.h>

Servo servo1;
int angle = 0;
bool active = false;
const int addr = 9;

const int delay1 = 800;
const int delay2 = 250;

void setup() {
  // put your setup code here, to run once:
  servo1.attach(3);
  servo1.write(90);
  Serial.begin(9600);
  Wire.begin(addr);
  Serial.println("started");
  Wire.onReceive(fire);
}

void loop() {
  // put your main code here, to run repeatedly:
}

void fire(int f) {
  if (!active) {
    active = true;
    angle = Wire.read();

    Serial.println(angle);
    servo1.write(angle);

    delay(delay1);
    servo1.write(90);
    angle = 0;
    active = false;
    delay(delay2)
  }
  

}
