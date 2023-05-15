#include <EduExo.h>

float movingAverage(int windowSize, int sensorPin,int reading_delay) {

  int sensorValues[windowSize]; 
  int sensorIndex = 0; 
  float sensorAverage = 0; 

  for (int i = 0; i < windowSize; i++) {
    sensorValues[i] = analogRead(sensorPin);
    sensorAverage += sensorValues[i];
    delay(reading_delay);
  }
  return sensorAverage /= windowSize;

}