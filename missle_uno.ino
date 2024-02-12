#include <Servo.h>
#include <Wire.h>

Servo servo1;
int angle = 0;
bool active = false;
const int addr = 9;
bool flag = false;

const int delay1 = 500;
const int delay2 = 500;

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
  if (flag) {
    servo1.write(angle);
    Serial.println(angle);

    delay(delay1);
    servo1.write(90);
    delay(delay2);
    //active = false;
    flag = false;
  }
}

void fire(int f) {
  //active = true;
  angle = Wire.read();
  flag = true;
}
