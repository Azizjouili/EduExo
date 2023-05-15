#include <EduExo.h>
#include <credentials.h>


MyUDP::MyUDP() {
}

void MyUDP::begin(int port) {
  my_ssid = ssid;
  my_user = user;
  my_pass = pass;
  WiFi.beginEnterprise(my_ssid, my_user, my_pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");
  udp.begin(port);
  Serial.print("Listening on port ");
  Serial.println(port);
  Serial.print("Local IP address: ");
  Serial.println(WiFi.localIP());
}

int MyUDP::readPacket(char* buffer, int bufferSize) {
  int packetSize = udp.parsePacket();
  if (packetSize) {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    udp.read(buffer, bufferSize);
    buffer[packetSize] = 0;
    Serial.println("Contents:");
    Serial.println(buffer);
    return packetSize;
  }
  return 0;
}

void MyUDP::sendPacket(char* data, int dataSize, IPAddress destIP, int destPort) {
  udp.beginPacket(destIP, destPort);
  udp.write(data, dataSize);
  udp.endPacket();
  Serial.print("Sent packet of size ");
  Serial.println(dataSize);
}
