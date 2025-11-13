#ifndef MGSERVO
#define MGSERVO
#include <Arduino.h>
#include <Servo.h>

class MG996R
{
private:
  const float pi = 3.142;

  float time_period_for_one = 1.515;                   // Experiment Data
  float w = 2 * pi / time_period_for_one;              // Angular Frequency w = deg2rad(360) / 1.515

  float req_time = 0;           // Initialize required time to reach a specific angle

  // For Control
  float ref = 0;                // Initialize Reference Angle
  float for_ref_time = 0;       // Initialize time required to come back to reference angle
  Servo myservo;

public:
  MG996R();
  MG996R(byte pin);
  void write(int angle);
  void Reference();

private:
  void CW_ROT(float rad, float req_time);              // Clockwise Rotation
  void CCW_ROT(float rad, float req_time);             // Counter Clockwise Rotation
};

#endif