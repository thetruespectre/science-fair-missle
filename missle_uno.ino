#include <Servo.h>
#include <Wire.h>

Servo servo1;
int angle = 0;
bool active = false;
const int addr = 9;
bool flag = false;
const int on = 2;

const int delay1 = 100;
const int delay2 = 100;
const int delay3 = 800;

void setup() {
  // put your setup code here, to run once:
  pinMode(on, OUTPUT);
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
    digitalWrite(on, HIGH);
    delay(delay2);
    digitalWrite(on, LOW);

    servo1.write(90);
    delay(delay3);
    //active = false;
    flag = false;
  }
}

void fire(int f) {
  //active = true;
  angle = Wire.read();
  angle = 180 - angle;
  flag = true;
}
