#include <Servo.h>
#include <EduExo.h>
Servo myservo;

int forceValue=0;
int forceCalibrated=0;
int forceFiltered=0;
int forceDesired=10;
int forceThreshold=10;
int positionDesired;

int maxAngle=180;
int minAngle=80;
float gain=0.25;

float posIsDeg;
const float alpha = 0.2;

void setup() {
pinMode(4,OUTPUT);
digitalWrite(4,HIGH);
myservo.write(180);
myservo.attach(servoDigitalPin);
}

void loop() {

forceValue=analogRead(forcePin) ; //read force sensor value

forceCalibrated = forceIs(forceValue, forceOffset); //calibrate the force sensor value

forceFiltered = (1 - alpha) * forceFiltered + alpha * forceCalibrated;//Lowpass Filter
delay(10);

//Admittance Controller :
if (abs(forceFiltered)>forceThreshold)
{
positionDesired -= gain*(forceFiltered-forceDesired);
}
if (positionDesired<minAngle)
{
  positionDesired=minAngle;
}
else if (positionDesired >maxAngle)
{
  positionDesired=maxAngle;
}


myservo.write(positionDesired); //command servo to move to the desired position
delay(10);

//calculate the current servo angle and print it on the serial monitor.
posIsDeg=servo_pos_deg(servoAnalogPin,526,938); 
Serial.print("Position (in degrees):");
Serial.println (posIsDeg);
}
