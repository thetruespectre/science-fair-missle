#include <Servo.h>
#include <Wire.h>

Servo servo1;
Servo servo2;
int angle = 0;
bool active;
const int addr = 10;

void setup() {
  // put your setup code here, to run once:
  servo1.attach(3);
  servo2.attach(6);
  servo1.write(90);
  servo2.write(90);
  Serial.begin(9600);
  Wire.begin(addr);
  Serial.println("started");

  Wire.onReceive(fire);
}

void loop() {
  // put your main code here, to run repeatedly:
}

void fire(int f) {
  Serial.println("FIRING");
  /*
  byte a, b;
  a = Wire.read();
  b = Wire.read();
  Serial.println(a);
  Serial.println(b);

  angle = a;
  angle = (angle << 8) | b;
  */
  angle = Wire.read();

  servo1.write(angle);
  Serial.println(angle);
  delay(1000);
  servo1.write(90);
  angle = 0;
}
