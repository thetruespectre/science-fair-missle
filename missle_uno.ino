#include <Servo.h>
#include <Wire.h>

Servo servo1;
int angle = 0;
const int addr = 9;
bool flag = false;

const int gate1 = 2;
const int gate2 = 4;
const int gate3 = 5;

const int reload = 8;
int count = 3;

const int delay1 = 500; //missle turn
const int delay2 = 150; //missle shoot
const int delay3 = 3000; //missle reset

void setup() {
  // put your setup code here, to run once:
  pinMode(gate1, OUTPUT);
  pinMode(gate2, OUTPUT);
  pinMode(gate3, OUTPUT);

  pinMode(reload, INPUT_PULLUP);
  
  servo1.attach(3);
  servo1.write(90);
  Serial.begin(9600);
  
  Wire.begin(addr);
  Serial.println("started");
  Wire.onReceive(fire);
}

void loop() {
  if (digitalRead(reload) == LOW) {
    count = 3;
  }

  if (flag) {
    
    if (count == 4) {
      shoot(gate1);
    } else if (count == 3) {
      shoot(gate2);
    } else if (count == 2) {
      shoot(gate3);
    } else if (count == 1) {
      shoot(gate4);
    } else {
      Serial.println("COUNT ERROR");
    }

    count -= 1;
    flag = false;
  }
}

void fire(int f) {
  //active = true;
  angle = Wire.read();
  angle = 180 - angle;
  if (count > 0) {
    flag = true;
  }
}

void shoot(int gate) {
  servo1.write(angle);
  Serial.println(angle);

  delay(delay1);
  digitalWrite(gate, HIGH);
  delay(delay2);
  digitalWrite(gate, LOW);
  delay(delay3);
}
