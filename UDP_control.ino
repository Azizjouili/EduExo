#include <Arduino_LSM6DS3.h>
#include <Servo.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include <stdlib.h>
Servo myservo;

//Structure to save the sensor data in it with name and value
struct sensordata{
String sensorname;
String sensorvalue;
};
//object of type sensordata with 2 sensor measurments.
sensordata mysensordata[2];


int forcePin=A5;
int servoAnalogInPin = A3;
float force;
float posIs;
float posIsDeg;
int desiredPosition;
int status = WL_IDLE_STATUS;
int keyIndex = 0;    

//Wifi connection (ssid,username,password)
char ssid[] = "ssid";
char username[] = "username";
char pass[] = "password";

//port for UDP :
unsigned int localPort = 1236;      

//received packet:
char packetBuffer[255];
char  ReplyBuffer[] = "acknowledged"; 

//object of type WiFiUDP:
WiFiUDP Udp;

void setup() {
  Serial.begin(9600);
  delay(1000);
  myservo.write(180);
  myservo.attach(3);

  //Connection to wifi:
  while (!Serial);
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);
  }
  String fv = WiFi.firmwareVersion();
  if (fv != "1.1.0") {
    Serial.println("Please upgrade the firmware");
  }
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.beginEnterprise(ssid,username,pass);
    delay(10000);
  }
  Serial.println("Connected to wifi");

  //print the parameters of the WiFi connection:
  printWifiStatus();

  Udp.begin(localPort); //begin method to start UDP 
}


void loop() {

  //read force signal and calibrate it :
  force = analogRead(forcePin)-268; 

  //read position of servo and convert it in degrees :
  posIs = analogRead(A3);
  posIsDeg=(90.0/(526-938))*(posIs-938);
  Serial.println(force);

  //write mysensordata sensor names and sensor values:
  mysensordata[0].sensorname = "Force";
  mysensordata[1].sensorname = "Angle";
  mysensordata[0].sensorvalue = force;
  mysensordata[1].sensorvalue = posIsDeg;

//format mysensordata to be easy to handle in MATLAB and to have a unique number of characters:
if (posIsDeg < 100) {
  char formattedAngle[10];
  snprintf(formattedAngle, sizeof(formattedAngle), "%06.2f", posIsDeg);
  mysensordata[1].sensorvalue = formattedAngle;
}
if (force <0) {
  char formattedForce1[10];
  sprintf(formattedForce1, "%07.2f", force);
  mysensordata[0].sensorvalue = formattedForce1;
}
if (force >=0) {
  char formattedForce2[10];
  sprintf(formattedForce2, "%+07.2f", force);
  mysensordata[0].sensorvalue = formattedForce2;
}


  //Print the sensor names and sensor values:
    for (int i = 0; i < 2; i++) {
    Serial.print("Sensor Name: ");
    Serial.print(mysensordata[i].sensorname);
    Serial.print("\tSensor Data: ");
    Serial.println(mysensordata[i].sensorvalue);
  }

  //conver the struct to a string :
  String structString;
  for (int i = 0; i < 2; i++) {
    structString += mysensordata[i].sensorname;
    structString += ",";
    structString += String(mysensordata[i].sensorvalue);
    structString += ";";
  }
   
  //function to send UDP package via WiFi:
  sendUDP("10.181.118.208", localPort, structString.c_str());

  //read UDP package sent via WiFi:
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    int bytesRead = Udp.read(packetBuffer, packetSize);
    if (bytesRead > 0) {
      packetBuffer[bytesRead] = '\0';
      Serial.print("Received packet: ");
      Serial.println(packetBuffer);
    }
  }

  //convert the received string (position desired of the servo) to integer:
  int num = atoi(packetBuffer); 

  //command servo to go to the desired position sent via UDP:
  myservo.write(num);
  delay(1000);
}



void sendUDP(const char* ipAddress, unsigned int port, const char* data) {
  Udp.beginPacket(ipAddress, port);
  Udp.print(data);
  Udp.endPacket();
}

void printWifiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}