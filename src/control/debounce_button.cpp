#include <EduExo.h>

bool DebounceButton(int buttonPin,int debounceDelay) {
  static int buttonState;
  static int lastButtonState = LOW;
  static unsigned long lastDebounceTime = 0;
  bool buttonPressed = false;
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        buttonPressed = true;
      }
    }
  }
  lastButtonState = reading;
  return buttonPressed;
}