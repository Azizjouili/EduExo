#include <EduExo.h>

void toggle_pin(int pin) {
  // Read the current status of the pin
  int status = digitalRead(pin);
  // If the pin is currently HIGH, set it to LOW; otherwise, set it to HIGH
  if (status == HIGH) {
    digitalWrite(pin, LOW);
  } else {
    digitalWrite(pin, HIGH);
  }
}
