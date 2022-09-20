#include "NeuralNetwork.h"

NeuralNetwork *nn;

float pi = 3.14159265;
float freq = 100;
float period = (1 / freq) * (1000000);

void setup()
{
  Serial.begin(115200);
  nn = new NeuralNetwork();
}

void loop()
{
  nn->RunInference();
}