#include <Servo.h>

Servo servoLeft;
Servo servoRight;

char inputByte;
void setup() {
 servoLeft.attach(11);
 servoLeft.writeMicroseconds(1500); // Stay still
 servoRight.attach(12);
 servoRight.writeMicroseconds(1500); // Stay still
 Serial.begin(9600);
 pinMode(13,OUTPUT);
  
}

void loop() {
  while(Serial.available()>0){
    inputByte= Serial.read();
    Serial.println(inputByte);
  
    if (inputByte == 'w') { // Go forward
      servoLeft.writeMicroseconds(1700);
      servoRight.writeMicroseconds(1300);
    }
    if (inputByte == 's') { // Stop
      servoLeft.writeMicroseconds(1500);
      servoRight.writeMicroseconds(1500);
    }
  }
}
