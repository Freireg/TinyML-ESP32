#include "NeuralNetwork.h"

NeuralNetwork *nn;


void setup()
{
  Serial.begin(115200);
  nn = new NeuralNetwork();
}

void loop()
{
  nn->RunInference();
  Serial.print(nn->Result8);
  Serial.print("\n");
  //Serial.print(nn->Result);
  //Serial.print("\n");
  delay(125);
}