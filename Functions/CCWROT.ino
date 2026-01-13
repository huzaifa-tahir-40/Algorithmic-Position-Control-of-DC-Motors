void CCWROT(float angle, float w, Servo myServo)
{
  // Helps us travel the angle in clockwise direction

  float radians = -angle * pi / 180;
  float req_time = radians / w * 1000;
  unsigned long startTime = millis();               // Starting time of function
  
  while (millis() - startTime < req_time) {         // While time of function less than required time to reach specific 'rad' angle
    myServo.write(180);                             // Rotate servo to maximum speed
    delay(50);
  }

  Serial.println(millis() - startTime);
  for_ref_time -= millis() - startTime;             // Update time required to go back to reference angle
  myServo.write(90);                                // Stop the servo
}