#ifndef EduExo_H
#define EduExo_H
#include <Arduino.h>
#include <Servo.h>
#include <MyFunctions.h>

#include <WiFiNINA.h>
#include <ArduinoBLE.h>
#include <WiFiUdp.h>
#include <credentials.h>

const int servoAnalogPin = 3; //Servo connection analog pin
const int servoDigitalPin =3; //Servo connection digital pin
const int emgPin = 1;  //AUX connection for EMG
const int Aux2Pin = 2;  //Extra AUX connection 
const int LEDPin = 4;   //LED Pin
const int Button1 = 9;  //Button 1 connection pin
const int Button2 = 8;  //Button 2 connection pin
const int forcePin = 4; //Force sensor analog connection pin
const int forceOffset = 260; //Offset value for the force sensor

//Switch the digital pin value :
void toggle_pin(int pin);
 
//debounce button:
bool DebounceButton(int buttonPin, int debounceDelay);

//Read force sensor value :
int forceIs(int forceAnalogInPin, int forceOffset);

//Read EMG sensor value :
int emgIs(int emgPin);

//Read the servo motor position :
int servo_pos(int servoAnalogInPin);

//Read the servo motor position in degrees :
int servo_pos_deg(int servoAnalogInPin,float sValue90,float sValue0);

//connect the arduino board to a WPA2-Entreprise WiFi:
class WiFiNINA_connect {
  public:
    WiFiNINA_connect();
    void begin();
    void printCurrentNet();
  private:
    char* my_ssid;
    char* my_user;
    char* my_pass;
};

//connect the arduino board to bluetooth :
class BLE_connect {
  public:
    void begin();
    void loop();
  private:
    BLEService service;
    BLECharacteristic characteristic;
};

//emergency stop of the servo if a limit is exceeded :
class EmergencyStop {
public:
  EmergencyStop(Servo& servo);
  void stop(int stop_position);

private:
  Servo& _servo;
};

//moving average filter for the sensor measurement :
float movingAverage(int windowSize,int sensorPin, int reading_delay); 

float movingAverageEMG(int windowSize, int emgPin,int reading_delay);

float movingAverageForce(int windowSize, int forcePin, int forceOffset, int reading_delay);



//Exponential filter for the sensor measurement :
class ExpFilter {
  public:
    ExpFilter(float alpha);
    float exponentialFilter(int pin);
  private:
    float alpha;
    float prevFilteredValue;
};

//connect to wifi and read UDP data :
class MyUDP {
  public:
    MyUDP();
    void begin(int port);
    int readPacket(char* buffer, int bufferSize);
    void sendPacket(char* data, int dataSize, IPAddress destIP, int destPort);
  private:
    WiFiUDP udp;
    char* my_ssid;
    char* my_user;
    char* my_pass;
};

class BLEData {
  public:
    BLEData();
    void begin();
    void sendSensorValue(uint8_t pin);
    void sendString(const char* str);
    void sendInt(int i);
    void readString();
    void readInt();
    
  private:
    BLEService m_service;
    BLECharCharacteristic m_char;
    BLEIntCharacteristic m_int;
};

class BLE_control {
  public:
    BLE_control();
    void begin();
    void executeFunction();

  private:
    Servo myservo;
    BLEService ledService;
    BLEByteCharacteristic switchCharacteristic;
};
#endif 

