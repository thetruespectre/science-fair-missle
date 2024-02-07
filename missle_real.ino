#include <Servo.h>
#include <SR04.h>
#include <math.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

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
int a;
float b = 30;

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

  //Wire.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  // i copied most of the code (too lazy)
  for(int i=15;i<=165;i++){  
    servo1.write(i);
    a = sonar1.Distance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
    
    //radar(i);

    if (a > 0 && a <= range) {
      doo(i);
    }
  }
  // Repeats the previous lines from 165 to 15 degrees
  for(int i=165;i>=15;i--){  
    servo1.write(i);
    a = sonar1.Distance();

    //radar(i);

    if (a > 0 && a <= range) {
      doo(i);
    }
  }
}

double rad(int degree) {
  return degree*M_PI/180;
}

double ang(double radian) {
  return radian*180/M_PI;
}

void radar(int i) {
  Serial.print(i); // Sends the current degree into the Serial Port
  Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  Serial.print(round(a)); // Sends the distance value into the Serial Port
  Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
}


void doo(int i) {
  double c;
  double angle;
  c = sqrt(pow(a, 2) + pow(b, 2) - 2*a*b*cos(rad(i)));
  angle = ang(acos(
    sin(rad(i))/c*a
  ));
  /*
  Wire.beginTransmission(addr);
  Wire.write(round(angle));
  Wire.endTransmission();
  */
  Serial.println(round(angle));
}
