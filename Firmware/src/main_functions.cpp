#include <Arduino.h>
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"
#include "constants.h"
#include "output_handler.h"
#include "main_functions.h"

#include "model.h"

namespace {
  tflite::ErrorReporter* error_reporter = nullptr;
  const tflite::Model* model = nullptr;
  tflite::MicroInterpreter* interpreter = nullptr;
  TfLiteTensor* input;
  TfLiteTensor* output;
  int inference_count = 0;

  constexpr int kTensorArenaSize = 2 * 1024;
  uint8_t tensor_arena[kTensorArenaSize];
}

void setup(void)
{
  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;

  model = tflite::GetModel(g_model);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
		TF_LITE_REPORT_ERROR(error_reporter,
						"Model provided is schema version %d not equal "
						"to supported version %d.",
						model->version(), TFLITE_SCHEMA_VERSION);
		return;
	}

  static tflite::AllOpsResolver resolver;

  static tflite::MicroInterpreter static_interpreter(
    model, resolver, tensor_arena, kTensorArenaSize, error_reporter);
  
  interpreter = &static_interpreter;

  TfLiteStatus allocate_status = interpreter->AllocateTensors();
	if (allocate_status != kTfLiteOk) {
		TF_LITE_REPORT_ERROR(error_reporter, "AllocateTensors() failed");
		return;
	}
  input = interpreter->input(0);
  output = interpreter->output(0);

  inference_count = 0;
}



void loop(void)
{
  float position = static_cast<float>(inference_count)/static_cast<float>(kInferencesPerCycle);
  float x_val = position * kXrange;

  input->data.f[0] = x_val;

  TfLiteStatus invoke_status = interpreter->Invoke();
  if(invoke_status != kTfLiteOk){
    error_reporter->Report("Invoke failed on x_val: %f\n", static_cast<double>(x_val));
    return;
  }

  float y_val = output->data.f[0];
  HandleOutput(error_reporter, x_val, y_val);

  inference_count += 1;
  if (inference_count >= kInferencesPerCycle) inference_count = 0;
}

