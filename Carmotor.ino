#include <Servo.h>        // Include Servo Library
#include <NewPing.h>      // Include Newping Library

// L298N Control Pins
const int LeftMotorForward = 4  ;
const int LeftMotorBackward = 5;
const int RightMotorForward = 6;
const int RightMotorBackward = 7;
int speedPinLeft = 9; // PWM pin to control speed of left motor
int speedPinRight = 10; // PWM pin to control speed of right motor

#define SONAR_NUM 3      // Number of sensors.
#define MAX_DISTANCE 300 // Maximum distance (in cm) to ping.

NewPing sonar[3] = {   // Sensor object array.
  NewPing(A3, A2, MAX_DISTANCE), // Right Trig Pin
  NewPing(A1, A0, MAX_DISTANCE), // Left Trig Pin
  NewPing(13, 12, MAX_DISTANCE)  // Center Trig Pin
};

Servo Myservo;  // Servo's name
boolean goesForward = false;
int distance;

void setup()
{
  Serial.begin(9600);
  // Set L298N Control Pins as Output
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
//  analogWrite(speedPinLeft, 255); // ENA pin
//  analogWrite(speedPinRight, 255); // ENB pin
  Myservo.attach(8);
  Myservo.write(90);
  delay(2000); // Wait for 2s.
}


void loop()
{
  slowDown();
  distance = sonar[2].ping_cm();
  delay(1000);
  Serial.println(distance);
//  if (distance <= 20)
//  {
//    slowDown();
//    int distanceR = sonar[0].ping_cm();
//    delay(200);
//    int distanceL = sonar[1].ping_cm();
//    delay(200);
//    if (distance <= 15)
//    {
//      if (abs(distance - distanceR) <= 5 && abs(distance - distanceL) <= 5 && abs(distanceR - distanceL) <= 5) {
//        Myservo.write(180);
//        distanceL = sonar[2].ping_cm();
//        Serial.print("left; ");
//        Serial.print(distanceL);
//        delay(2500);
//        Myservo.write(0);
//        distanceR = sonar[2].ping_cm();
//        Serial.print("Right; ");
//        Serial.print(distanceR);
//        delay(2500);
//
//        // For CORNERS
//        if (distanceR >= distanceL)
//        {
//          turnRight(500);
//          turnRight(500);
//          Myservo.write(90); // Return to center
//        }
//        else
//        {
//          turnLeft(500);
//          turnLeft(500);
//          Myservo.write(90); // Return to center
//        }
//      }
//      // For Obstacles
//      else {
//        if (distanceL > distanceR) {
//          turnLeft(600);
//        }
//        else {
//          turnRight(600);
//        }
//      }
//    }
//  }
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

void turnRight(int duration) // Gradual turn right by adjusting motor speeds
{
//  setMotorSpeed(255, 255); // Adjust these values for smoother turning
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  delay(duration);
  moveStop();
}

void turnLeft(int duration) // Gradual turn left by adjusting motor speeds
{
//  setMotorSpeed(255, 255); // Adjust these values for smoother turning
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  delay(duration);
  moveStop();
}

