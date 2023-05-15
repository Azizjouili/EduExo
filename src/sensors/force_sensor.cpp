#include <EduExo.h>

int forceIs(int forceAnalogInPin, int forceOffset) {
  return analogRead(forceAnalogInPin) - forceOffset;
}