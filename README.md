# TinyML-ESP32

# Overview
This is my personal repository to test test TinyML Applications.
> * This branch model:  Sine Wave Model
> * Plataform used:     ESP32 | PlatformIO
> * Current status:     Working!
# Machine Learning Model
The modeling process can be found on [TinyML_Sine_Model](https://github.com/Freireg/TinyML-ESP32/blob/SineWave/TinyML_Sine_Model.ipynb).
# Firmware Implementation
This is a basic example following the steps given by TinyML Foundation on how to build a embedded ML app using TensorFlow Lite.

Important note: In this example I used the recommended directory tree on **src** 
~~~
src
├── constants.cc
├── constants.h
├── main.cc
├── main_functions.cpp
├── main_functions.h
├── model.cc
├── model.h
├── output_handler.cc
└── output_handler.h
~~~

While using the **tfmicro** package on the **lib** folder
~~~
lib
├── /tfmicro
├── README
~~~