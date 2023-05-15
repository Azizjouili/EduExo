#include <EduExo.h>

BLE_control::BLE_control() :
  ledService("180A"), switchCharacteristic("2A57", BLERead | BLEWrite)
{
}

void BLE_control::begin() {
  Serial.begin(9600);
  myservo.attach(3);
  while (!Serial);
  pinMode(LED_BUILTIN, OUTPUT);
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy failed!");
    while (1);
  }
  BLE.setLocalName("Nano 33 IoT");
  BLE.setAdvertisedService(ledService);
  ledService.addCharacteristic(switchCharacteristic);
  BLE.addService(ledService);
  switchCharacteristic.writeValue(0);
  BLE.advertise();
  Serial.println("BLE LED Peripheral");
}

void BLE_control::executeFunction() {
  BLEDevice central = BLE.central();
  if (central) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());
    while (central.connected()) {
      if (switchCharacteristic.written()) {
        switch (switchCharacteristic.value()) {  
          case 01:
            function1(myservo);
            break;
          case 02:
            function2(myservo);  
            break;
          case 03:
            function3(myservo);
            break;
          case 04:
            function4(myservo);
            break;
          default:
            break;
        }
      }
    }
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
}

