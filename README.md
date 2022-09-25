# TinyML-ESP32

# Overview
This is my personal repository to test test TinyML Applications.
> * This branch model:  Value Comparator
> * Plataform used:     ESP32 | PlatformIO
> * Current status:     Working!
# Machine Learning Model
The modeling process can be found on [TinyML_Example_Model](https://github.com/Freireg/TinyML-ESP32/blob/main/TinyML_ESP32_Example.ipynb).
# Firmware Implementation
This is a basic example following the steps given by [atomic14](https://github.com/atomic14/tensorflow-lite-esp32).

Important note: In this example I used the recommended NeuralNetwork Class definitions:
```
class NeuralNetwork
{
private:
    tflite::MicroMutableOpResolver<10> *resolver;
    tflite::ErrorReporter *error_reporter;
    const tflite::Model *model;
    tflite::MicroInterpreter *interpreter;
    TfLiteTensor *input;
    TfLiteTensor *output;
    uint8_t *tensor_arena;

public:
    float *getInputBuffer();
    NeuralNetwork();
    float predict();
};

```