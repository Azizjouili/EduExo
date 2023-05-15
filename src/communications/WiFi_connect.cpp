#include <EduExo.h>
#include <credentials.h>

WiFiNINA_connect::WiFiNINA_connect() {}

void WiFiNINA_connect::begin() {
  my_ssid = ssid;
  my_user = user;
  my_pass = pass;
  WiFi.beginEnterprise(my_ssid, my_user, my_pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(3000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");
  printCurrentNet();
}

void WiFiNINA_connect::printCurrentNet() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}
