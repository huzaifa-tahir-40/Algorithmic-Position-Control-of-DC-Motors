void CWROT(float angle, float w, Servo myServo)
{
  // Helps us travel the angle in clockwise direction
  
  float radians = angle * pi / 180;                   // Convert Angle to Radians
  float req_time = radians / w * 1000;                // Calculate Time = Angle / w * 1000
  unsigned long startTime = millis();                 // Starting time of function
  
  while (millis() - startTime < req_time) {           // While time of function less than required time to reach specific 'rad' angle
    myServo.write(0);                                 // Rotate servo in maximum speed
    delay(50);
  }

  Serial.println(millis() - startTime);
  for_ref_time += millis() - startTime;               // Update time required to go back to reference angle
  myServo.write(90);                                  // Stop the servo
}