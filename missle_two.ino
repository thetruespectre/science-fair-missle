#include <Servo.h>
#include <Wire.h>

Servo servo1;
int angle = 0;
bool active = false;
const int addr = 10;
const int on = 2;

bool flag = false;
bool reset = false;

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
  if (reset) {
    servo1.write(90);
    reset = false;
  }

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
  if (angle == 250) {
    reset = true;
  }
  else {
    angle = 180 - angle;
    flag = true;
  }
}
