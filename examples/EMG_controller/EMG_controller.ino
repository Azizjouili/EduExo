#include <Servo.h>
#include <EduExo.h>
Servo myservo;

int emgBiceps;
int windowSize=8;
int reading_delay=10;
int emgMin=20;
int emgMax=960;
int minAngle=80;
int maxAngle=180;
int desiredAngle;
int currentAngle=180;


void setup() {
Serial.begin(9600);
delay(50);
myservo.write(180);
myservo.attach(3);
}

void loop() {

emgBiceps=movingAverageEMG(windowSize,emgPin,reading_delay); //read and filter the EMG signal from BICEPS

//print the EMG value of biceps 
Serial.print("EMG filtered: ");
Serial.println(emgBiceps);
delay(10);

//Calculate the corresponded servo angle and print it
desiredAngle=map(emgBiceps,emgMin,emgMax,maxAngle,minAngle);
Serial.print("desired angle : ");
Serial.println(desiredAngle);

while (currentAngle != desiredAngle) {
  if (currentAngle < desiredAngle) {
    currentAngle++;
  } else {
    currentAngle--;
  }
  myservo.write(currentAngle);
  delay(10);
}

}







