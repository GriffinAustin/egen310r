#include <Servo.h>


// Macros
#define P1A 10 // PWM Pin
#define P2A 6 // PWM Pin
#define EN12 9 // Enable Pin

Servo servoLeft;
Servo servoRight;
char inputByte;


void setup() {
 servoLeft.attach(11);
 servoRight.attach(12);
 stopMoving();
 Serial.begin(9600); // Set baud rate to 9600

 pinMode(P1A, OUTPUT);
 pinMode(P2A, OUTPUT);
 pinMode(EN12, OUTPUT);
}

void loop() {
  while(Serial.available() > 0) { // Check if their is input available to read
    inputByte = Serial.read();
    Serial.println(inputByte); // Print command to user's console

    switch (inputByte) {
      case 'w':
        goForward();
        break;

      case 'x':
        goBackward();
        break;
       
      case 's':
        stopMoving();
        break;

      case 'a':
        veerLeft();
        break;

      case 'd':
        veerRight();
        break;

      case 'e': // Raise pulley
        turnMotorLeft(300);
        break;

      case 'c': // Lower pulley
        turnMotorRight(300);
        break;
    }
  }

  delay(50); // Helps with bluetooth latency
}

void L293D(char dir, int en) {
  if (dir == 'L')
  {
    if (en == 0) { // Disable if enable is 0
       Serial.println("Pulley motor stopped\n");
    } else {
       Serial.print("Starting pulley motor\n");         
    }
    digitalWrite(EN12 ,en); // Enable 1A and 2A 
    analogWrite(P1A, 255); // send PWM to P1A
    digitalWrite(P2A,LOW) ;// LOW signal to P2A to turn off 
   
  } else {
    if (en == 0) {
       Serial.println("Pulley motor stopped\n");
    } else {
       Serial.print("Starting pulley motor\n");   
    }    
    digitalWrite(EN12, en); // Disable 1A and 2A
    analogWrite(P2A, 255); // send PWM to P1A
    digitalWrite(P1A, LOW); // LOW signal to P1A to turn off
  }
}

void goForward() {
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1300);
}

void goBackward() {
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1700);
}

void stopMoving() {
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
}

void veerLeft()
{
  servoLeft.writeMicroseconds(1500 + 25);
  servoRight.writeMicroseconds(1500 - 85);
}

void veerRight()
{
  servoLeft.writeMicroseconds(1500 + 85);
  servoRight.writeMicroseconds(1500 - 25);
}

void turnMotorRight(int time) {
  L293D('R', 1); // Begin rotation
  delay(time);
  L293D('R', 0); // Stop motor
}

void turnMotorLeft(int time) {
  L293D('L', 1); // Begin rotation
  delay(time);
  L293D('L', 0); // Stop motor
}
