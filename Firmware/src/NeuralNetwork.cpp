#include <Arduino.h>
#include "NeuralNetwork.h"
#include "model.h"
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"

const int kArenaSize = 25 * 1024;

float pi = 3.14159265;
float freq = 150;
float period = (1 / freq) * (1000000);

NeuralNetwork::NeuralNetwork()
{
    	/* Set up logging. Google style is to avoid globals or statics because of
	 * lifetime uncertainty, but since this has a trivial destructor it's okay.
	 * NOLINTNEXTLINE(runtime-global-variables)
	 */
	static tflite::MicroErrorReporter micro_error_reporter;

	error_reporter = &micro_error_reporter;

	/* Map the model into a usable data structure. This doesn't involve any
	 * copying or parsing, it's a very lightweight operation.
	 */
	model = tflite::GetModel(g_model);
	if (model->version() != TFLITE_SCHEMA_VERSION) {
		TF_LITE_REPORT_ERROR(error_reporter,
						"Model provided is schema version %d not equal "
						"to supported version %d.",
						model->version(), TFLITE_SCHEMA_VERSION);
		return;
	}

	/* This pulls in all the operation implementations we need.
	 * NOLINTNEXTLINE(runtime-global-variables)
	 */
	static tflite::AllOpsResolver resolver;

	/* Build an interpreter to run the model with. */
	static tflite::MicroInterpreter static_interpreter(
		model, resolver, tensor_arena, kTensorArenaSize, error_reporter);
	interpreter = &static_interpreter;

	/* Allocate memory from the tensor_arena for the model's tensors. */
	TfLiteStatus allocate_status = interpreter->AllocateTensors();
	if (allocate_status != kTfLiteOk) {
		TF_LITE_REPORT_ERROR(error_reporter, "AllocateTensors() failed");
		return;
	}

	/* Obtain pointers to the model's input and output tensors. */
	input = interpreter->input(0);
	output = interpreter->output(0);

	/* Keep track of how many inferences we have performed. */
	inference_count = 0;
}

float *NeuralNetwork::getInputBuffer()
{
    return input->data.f;
}

float NeuralNetwork::predict()
{
    interpreter->Invoke();
    return output->data.f[0];
}

void NeuralNetwork::RunInference(void)
{
		unsigned long timestamp = micros();
  	timestamp = timestamp % (unsigned long)period;
		float x_val = ((float)timestamp * 2 * pi) / period;

		int8_t x = x_val/(input->params.scale + input->params.zero_point);
		//input->data.f[0] = x_val;
		input->data.int8[0] = x_val;
		interpreter->Invoke();

		Result8 = output->data.int8[0];
		Result = Result8 * output->params.scale;



}