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
  // Set L298N Control Pins as Output
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);

  // Setting PWM pins as outputs
  pinMode(speedPinLeft, OUTPUT);
  pinMode(speedPinRight, OUTPUT);

  // Stop the motors initially
  moveStop();
  Serial.begin(9600);
}

void loop() {
  gradualTurnRight(10000);
  delay(60000);
  // Test left motor speeds
  testLeftMotorSpeeds();

  // Test right motor speeds
  testRightMotorSpeeds();
}

// Function to test left motor speeds from 0 to 255
void testLeftMotorSpeeds() {
  for (int speed = 0; speed <= 255; speed++) {
    Serial.println(speed);
    setMotorSpeed(speed,255);
    moveForward(); // Set the direction for left motor
    delay(2000); // Adjust delay for testing purposes
  }
  moveStop();
  delay(1000); // Delay before testing the right motor
}

// Function to test right motor speeds from 0 to 255
void testRightMotorSpeeds() {
  for (int speed = 0; speed <= 255; speed++) {
    Serial.println(speed);
    setMotorSpeed(255,speed);
    moveForward(); // Set the direction for right motor
    delay(2000); // Adjust delay for testing purposes
  }
  moveStop();
  delay(1000); // Delay before restarting the loop
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
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveBackward() // Move Backward Function for Motor Driver.
{
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

void gradualTurnRight(int duration) // Gradual turn right by adjusting motor speeds
{
  setMotorSpeed(255, 255); // Adjust these values for smoother turning
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
