#include <EduExo.h>

float movingAverageEMG(int windowSize, int emgPin,int reading_delay) {

  int sensorValues[windowSize]; 
  int sensorIndex = 0; 
  float sensorAverage = 0; 

  for (int i = 0; i < windowSize; i++) {
    sensorValues[i] = emgIs(emgPin);
    sensorAverage += sensorValues[i];
    delay(reading_delay);
  }
  return sensorAverage /= windowSize;

}