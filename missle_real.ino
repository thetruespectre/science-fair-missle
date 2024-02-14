#include <Servo.h>
#include <SR04.h>
#include <math.h>
#include <Wire.h>

const int del = 15;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

const int addr1 = 9;
const int addr2 = 10;

const int trig1 = 2;
const int trig2 = 4;
const int trig3 = 7;
const int trig4 = 8;

const int echo1 = 10;
const int echo2 = 11;
const int echo3 = 12;
const int echo4 = 13;

const int range = 50;

SR04 sonar1 = SR04(echo1, trig1);
SR04 sonar2 = SR04(echo2, trig2);
SR04 sonar3 = SR04(echo3, trig3);
SR04 sonar4 = SR04(echo4, trig4);
int a1;
int a2;
int a3;
int a4;

const int b = 17;

//do .Distance() for distance. 0 means there's nothing there

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  servo1.attach(3);
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(9);

  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);
  
  Wire.begin();
  Serial.println("Started");
}

void loop() {
  // put your main code here, to run repeatedly:
  // i copied most of the code (too lazy)
  for(int i=15;i<=165;i++){  
    servo1.write(i);
    delay(del);
    a1 = sonar1.Distance();
    a2 = sonar2.Distance();
    a3 = sonar3.Distance();
    a4 = sonar4.Distance();
    //a2, a3, a4 = 0;
    
    radar(i, a1);
    radar(i, a2);
    radar(i, a3);
    radar(i, a4);

    if (a1 > 0 && a1 <= range) {
      doo(i, a1, addr1);
    }
    if (a2 > 0 && a2 <= range) {
      doo(i, a2, addr1);
    }
    if (a3 > 0 && a3 <= range) {
      doo(i, a3, addr2);
    }
    if (a4 > 0 && a4 <= range) {
      doo(i, a4, addr2);
    }
  }
  // Repeats the previous lines from 165 to 15 degrees
  for(int i=165;i>=15;i--){  
    servo1.write(i);
    delay(del);
    a1 = sonar1.Distance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
    a2 = sonar2.Distance();
    a3 = sonar3.Distance();
    a4 = sonar4.Distance();
    //a2, a3, a4 = 0;

    radar(i, a1);
    radar(i, a2);
    radar(i, a3);
    radar(i, a4);

    if (a1 > 0 && a1 <= range) {
      doo(i, a1, addr1);
    }
    if (a2 > 0 && a2 <= range) {
      doo(i, a2, addr1);
    }
    if (a3 > 0 && a3 <= range) {
      doo(i, a3, addr2);
    }
    if (a4 > 0 && a4 <= range) {
      doo(i, a4, addr2);
    }
  }
}

double rad(int degree) {
  return degree*M_PI/180;
}

double ang(double radian) {
  return radian*180/M_PI;
}

void radar(int i, int a) {
  Serial.print(i); // Sends the current degree into the Serial Port
  Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  Serial.print(round(a)); // Sends the distance value into the Serial Port
  Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
}


void doo(int i, int a, int address) {

  double c;
  double angl;
  byte angle;
  c = sqrt(
    pow(a, 2) + pow(b, 2) - 2*a*b*cos(rad(i))
    );

  angl = ang(asin(
    sin(rad(i))/c*a
  ));

  angle = round(angl);
  
  Wire.beginTransmission(address);
  Wire.write(angle);
  Wire.endTransmission();
  //Serial.println(angle);
}
