#include "output_handler.h"


void HandleOutput(tflite::ErrorReporter* error_reporter, float x_value, float y_value)
{
  // Log the current X and Y values
  error_reporter->Report("x_value: %f, y_value: %f\n", x_value, y_value);
}
                  