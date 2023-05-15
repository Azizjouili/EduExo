#include <EduExo.h>

void BLE_connect::begin() {
  Serial.begin(9600);
  while (!Serial);
  if (!BLE.begin()) {
    Serial.println("Failed to start BLE!");
    while (1);
  }
  BLE.setLocalName("Nano 33 IoT");
  BLE.setDeviceName("Nano 33 IoT");
  BLE.setAdvertisedService(service);
  service.addCharacteristic(characteristic);
  BLE.addService(service);
  BLE.advertise();
  Serial.println("BLE device started!");
}

void BLE_connect::loop() {
  BLEDevice central = BLE.central();
  if (central) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());

    while (central.connected()) {
      delay(10);
    }
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
  }
}






