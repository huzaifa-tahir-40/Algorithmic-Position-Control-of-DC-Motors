#include "MG996R.hpp"

// ================================================
// Default Constructor
// ================================================

MG996R::MG996R() { }

// ================================================
// Initialize the pin of Servo in Class Contructor
// ================================================

MG996R::MG996R(byte pin)
{
  myservo.attach(pin);
}

// ================================================
// Go to the Specific Angle
// ================================================

void MG996R::write(int angle)
{
  if(angle >= 0) 
  {
    float radians = angle * pi / 180;                 // Convert Angle to Radians
    req_time = radians / w * 1000;                    // Calculate the required Time = (Angle / w * 1000) to reach the angle
    CCW_ROT(radians, req_time);                       // Rotate counter-clockwise for positive angle
    ref += angle;                                     // Update Reference Angle Distance
  }

  if(angle <= 0)
  {
    float radians = -angle * pi / 180;                // Convert Angle to Radians
    req_time = radians / w * 1000;                    // Calculate the required Time = (Angle / w * 1000) to reach the angle
    CW_ROT(radians, req_time);                        // Rotate clockwise for negative angle
    ref -= angle;                                     // Update Reference Angle Distance
  }

  if(ref > 360)
  {
    ref = 360 - ref;          // To keep reference angle periodic
  }
}

// ================================================
// Rotate Clockwise
// ================================================

void MG996R::CW_ROT(float rad, float req_time)
{
  unsigned long startTime = millis();                 // Starting time of function
  
  while (millis() - startTime < req_time) {           // While time of function less than required time to reach specific 'rad' angle
    myservo.write(0);                                 // Rotate servo in maximum speed
    delay(50);
  }

  Serial.println(millis() - startTime);
  for_ref_time += millis() - startTime;               // Update time required to go back to reference angle
  myservo.write(90);                                  // Stop the servo
}

// ================================================
// Rotate Counter Clock Wise
// ================================================

void MG996R::CCW_ROT(float rad, float req_time)
{
  unsigned long startTime = millis();               // Starting time of function
  
  while (millis() - startTime < req_time) {         // While time of function less than required time to reach specific 'rad' angle
    myservo.write(180);                             // Rotate servo to maximum speed
    delay(50);
  }

  Serial.println(millis() - startTime);
  for_ref_time += millis() - startTime;             // Update time required to go back to reference angle
  myservo.write(90);                                // Stop the servo
}

// ================================================
// Come Back to Reference Angle
// ================================================

void MG996R::Reference()
{
  unsigned long startTime = millis();               // Keep track of startTime of the Function
  while(millis() - startTime < for_ref_time)        // If the time required for reference angle is greater than time of function, keep rotating
  {
    if(ref > 0)
    {
      myservo.write(180);
      delay(50);
    }
    else if(ref < 0)
    {
      myservo.write(0);
      delay(50);
    }
  }
  myservo.write(90);
}