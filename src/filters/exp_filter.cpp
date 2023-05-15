#include <EduExo.h>

ExpFilter::ExpFilter(float alpha) {
  this->alpha = alpha;
  this->prevFilteredValue = 0;
}

float ExpFilter::exponentialFilter(int pin) {
  int rawValue = analogRead(pin);
  float filteredValue = alpha * rawValue + (1 - alpha) * prevFilteredValue;
  prevFilteredValue = filteredValue;
  return filteredValue;
}
