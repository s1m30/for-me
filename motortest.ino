#include <Servo.h>        // Include Servo Library
#include <NewPing.h>      // Include Newping Library

// L298N Control Pins
const int LeftMotorForward = 4;
const int LeftMotorBackward = 5;
const int RightMotorForward = 6;
const int RightMotorBackward = 7;
int speedPinLeft = 9; // PWM pin to control speed of left motor
int speedPinRight = 10; // PWM pin to control speed of right motor

void setup() {
  // put your setup code here, to run once:
  // Set L298N Control Pins as Output
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);

  // Setting PWM pins as outputs
  pinMode(speedPinLeft, OUTPUT);
  pinMode(speedPinRight, OUTPUT);

  analogWrite(speedPinLeft, 255); // ENA pin
  analogWrite(speedPinRight, 255); // ENB pin
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0; i<=4; i++){
  moveForward();
  delay(8000);
  gradualTurnRight(500);
  setMotorSpeed(255, 255);
  gradualTurnRight(500); 
  setMotorSpeed(255, 255);
  };
  moveStop();

}

void setMotorSpeed(int leftSpeed, int rightSpeed) {
  analogWrite(speedPinLeft, leftSpeed);
  analogWrite(speedPinRight, rightSpeed);
}

void moveStop() // Move Stop Function for Motor Driver.
{
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveForward() // Move Forward Function for Motor Driver.
{
  setMotorSpeed(255, 255);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveBackward() // Move Backward Function for Motor Driver.
{
  setMotorSpeed(255, 255);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, HIGH);
}

void slowDown() // Slow down the car
{
  setMotorSpeed(150, 150);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
}

//void gradualTurnRight(int duration) // Gradual turn right by adjusting motor speeds
//{
//  setMotorSpeed(200, 100); // Adjust these values for smoother turning
//  digitalWrite(RightMotorForward, HIGH);
//  digitalWrite(RightMotorBackward, LOW);
//  digitalWrite(LeftMotorForward, HIGH);
//  digitalWrite(LeftMotorBackward, LOW);
//  delay(duration);
//  moveStop();
//}
void gradualTurnRight(int duration) // Gradual turn right by adjusting motor speeds
{
  setMotorSpeed(200, 100); // Adjust these values for smoother turning
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
  delay(duration);
  moveStop();
}


void gradualTurnLeft(int duration) // Gradual turn left by adjusting motor speeds
{
  setMotorSpeed(100, 200); // Adjust these values for smoother turning
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  delay(duration);
  moveStop();
}

void slowDown() // Slow down the car
{
  setMotorSpeed(128, 128);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
}
