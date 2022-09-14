#include <Arduino.h>
#include "NeuralNetwork.h"

NeuralNetwork *nn;

float pi = 3.14159265;
float freq = 0.5;
float period = (1 / freq) * (1000000);

void setup()
{
  Serial.begin(115200);
  nn = new NeuralNetwork();
}

void loop()
{
  unsigned long timestamp = micros();
  timestamp = timestamp % (unsigned long)period;

  float x_val = ((float)timestamp * 2 * pi) / period;
  nn->getInputBuffer()[0] = x_val;

  float result = nn->predict();
  float y_val = result;

  Serial.print(x_val);
  Serial.print("\n");
  Serial.print(y_val);
  Serial.print("\n");
  delay(200);
}