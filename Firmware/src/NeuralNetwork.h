#ifndef __NeuralNetwork__
#define __NeuralNetwork__

#include <stdint.h>
#include <Arduino.h>

#define kTensorArenaSize    2000
namespace tflite
{
    template <unsigned int tOpCount>
    class MicroMutableOpResolver;
    class ErrorReporter;
    class Model;
    class MicroInterpreter;

    
} // namespace tflite

struct TfLiteTensor;

class NeuralNetwork
{
private:
    tflite::MicroMutableOpResolver<10> *resolver;
    tflite::ErrorReporter *error_reporter;
    const tflite::Model *model;
    tflite::MicroInterpreter *interpreter = nullptr;
    TfLiteTensor *input = nullptr;
    TfLiteTensor *output = nullptr;
	uint8_t tensor_arena[kTensorArenaSize];
    int inference_count = 0;

public:

    float *getInputBuffer();
    NeuralNetwork();
    float predict();
    void RunInference(void);
    float Result;
    int8_t Result8;
};

#endif