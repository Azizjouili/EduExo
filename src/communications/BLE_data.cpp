#include <EduExo.h>

BLEData::BLEData():
  m_service("1101"),
  m_char("2A57", BLERead | BLEWrite),
  m_int("2A58", BLERead | BLEWrite)
{
}

void BLEData::begin()
{
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }

  BLE.setLocalName("Arduino Nano33IoT");
  BLE.setAdvertisedService(m_service);
  m_service.addCharacteristic(m_char);
  m_service.addCharacteristic(m_int);

  BLE.addService(m_service);

  BLE.advertise();
  Serial.println("Bluetooth device active, waiting for connections...");
}

void BLEData::sendSensorValue(uint8_t pin)
{
  BLEDevice central = BLE.central();

  if (central) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());
    digitalWrite(LED_BUILTIN, HIGH);

    while (central.connected()) {
      int sensorValue = analogRead(pin);
      Serial.print("Sensor value is now: ");
      Serial.println(sensorValue);
      m_int.writeValue(sensorValue);
      delay(200);
    }
  }
  Serial.print("Disconnected from central: ");
  Serial.println(central.address());
}

void BLEData::sendString(const char* str)
{
  BLEDevice central = BLE.central();
  if (central) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());
    digitalWrite(LED_BUILTIN, HIGH);
    while (central.connected()) {
      Serial.print("String sent: ");
      Serial.println(*str);
      m_char.writeValue(*str);
      delay(1000);
    }
  }
  Serial.print("Disconnected from central: ");
  Serial.println(central.address());
}
void BLEData::sendInt(int i)
{
  BLEDevice central = BLE.central();
  if (central) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());
    digitalWrite(LED_BUILTIN, HIGH);
    while (central.connected()) {
      Serial.print("Integer sent: ");
      Serial.println(i);
      m_int.writeValue(i);
      delay(1000);
    }
  }
  Serial.print("Disconnected from central: ");
  Serial.println(central.address());
}

void BLEData::readString() {
  BLEDevice central = BLE.central();
  if (central) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());
    digitalWrite(LED_BUILTIN, HIGH);
    while (central.connected()) {
      if (m_char.written()) {
        Serial.print(m_char.value());
      }
      delay(10);
    }
  }
  Serial.print("Disconnected from central: ");
  Serial.println(central.address());
}
void BLEData::readInt() {
  BLEDevice central = BLE.central();
  if (central) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());
    digitalWrite(LED_BUILTIN, HIGH);
    while (central.connected()) {
      if (m_int.written()) {
        Serial.print(m_int.value());
      }
      delay(10);
    }
  }
  Serial.print("Disconnected from central: ");
  Serial.println(central.address());
}
