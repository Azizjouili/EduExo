#include <EduExo.h>

int servo_pos(int servoAnalogInPin) {
  return analogRead(servoAnalogInPin);
}

int servo_pos_deg(int servoAnalogInPin,float sValue90,float sValue0) {
    int posIs=servo_pos(servoAnalogInPin);
  return (90.0/(sValue90-sValue0))*(posIs-sValue0);
}