#include <Servo.h> 
#include <EduExo.h>
Servo myservo;

int bicepsPin=emgPin; //EMG sensor biceps
int tricepsPin=Aux2Pin; //EMG sensor triceps
float emgBiceps=0.0; 
float emgTriceps=0.0;

int bicepsThreshold=250;
int tricepsThreshold=100;
int maxAngle=180;
int minAngle=80;
int step=10;
int actual_position;
int windowSize=8;
int reading_delay=10;
void setup() {
  Serial.begin(9600);
  delay (1000);
  myservo.write(180);
  myservo.attach(servoDigitalPin);
}   

void loop() {

emgBiceps=movingAverageEMG(windowSize,bicepsPin,reading_delay); //read and filter the EMG signal from BICEPS

emgTriceps=movingAverageEMG(windowSize,tricepsPin,reading_delay); //read and filter the EMG signal from TRICEPS

//print the EMG values of biceps and triceps
Serial.print("EMG biceps: ");
Serial.println(emgBiceps);
Serial.print("EMG triceps: ");
Serial.println(emgTriceps);
delay(10);

actual_position=servo_pos_deg(servoAnalogPin,526,938); 
Serial.print("Position (in degrees):");
Serial.println (actual_position);


if (emgBiceps-emgTriceps>bicepsThreshold && actual_position>=minAngle){   //the biceps signal is stronger than triceps signal
  myservo.write(actual_position-step);   
  delay(50);
}

else if ((emgTriceps-emgBiceps>tricepsThreshold)  && actual_position<=maxAngle){ //the triceps signal is stronger than biceps signal
  myservo.write(actual_position+step);
  delay(50);
}

}
