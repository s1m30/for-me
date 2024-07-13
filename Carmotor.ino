#include <Servo.h>        // Include Servo Library
#include <NewPing.h>      // Include Newping Library

// L298N Control Pins
const int LeftMotorForward = 4;
const int LeftMotorBackward = 5;
const int RightMotorForward = 6;
const int RightMotorBackward = 7;
int speedPinLeft = 9; // PWM pin to control speed of left motor
int speedPinRight = 10; // PWM pin to control speed of right motor
#define TRIGGER_PIN  A1  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     A2  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 250 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 250cm.


Servo Myservo;  // Servo's name
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

boolean goesForward = false;
int distance = 100;

void setup()
{
  // Set L298N Control Pins as Output
   // Setting motor control pins as outputs
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorForward, OUTPUT);
  pinMode( RightMotorBackward, OUTPUT);
  
  // Setting PWM pins as outputs
  pinMode(speedPinLeft, OUTPUT);
  pinMode(speedPinRight, OUTPUT);

  analogWrite(speedPinLeft, 255); //ENA   pin
  analogWrite(speedPinRight, 255); //ENB pin
  Myservo.attach(8);
  Myservo.write(145);
  delay(2000);             // Wait for 2s.
  distance = readPing();    // Get Ping Distance.
  delay(100);               // Wait for 100ms.
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop()
{  
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);
  
  if (distance <= 25)
  {
    moveSlowdown();
    delay(600);
//    moveBackward();
//    delay(400);
//    moveStop();
//    delay(300);
    Myservo.write(50);
    distanceRight = readPing();
    delay(2000);
    Myservo.write(180);
    distanceLeft= readPing();
    delay(2000);
    Myservo.write(145);
    
    if (distanceRight >= distanceLeft)
    {
//      setMotorSpeed(100,255);
      turnRight();
      delay(300);
      moveStop();
    }
    else
    {
      turnLeft();
      delay(300);
      moveStop();
    }
  
  }
  else
  {
    moveForward(); 
  }

    distance = readPing();
}
int readPing()      // Read Ping Function for Ultrasonic Sensor.
{
  delay(100);                 // Wait 100ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  int cm = sonar.ping_cm();   //Send ping, get ping distance in centimeters (cm).
  if (cm==0)
  {
    cm=250;
  }
  return cm;
}

void aroundCorner(String dir){
  if (dir=="left"){
    turnLeft();
  }
  else (dir=="left"){
    turnLeft();
  }
}

void aroundCorner(String dir){
  if (dir=="left"){
    turnLeft();
  }
  else (dir=="left"){
    turnLeft();
  }
}

void setMotorSpeed(int leftSpeed, int rightSpeed) {
  analogWrite(speedPinLeft, leftSpeed);
  analogWrite(speedPinRight, rightSpeed);
}
void moveStop()       // Move Stop Function for Motor Driver.
{
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveForward()    // Move Forward Function for Motor Driver.
{
    digitalWrite(RightMotorForward, HIGH);
    digitalWrite(RightMotorBackward, LOW);
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(LeftMotorBackward, LOW);
}

void moveBackward()   // Move Backward Function for Motor Driver.
{
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, HIGH);
}

void turnRight()      // Turn Right Function for Motor Driver.
{
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

void turnLeft()       // Turn Left Function for Motor Driver.
{
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward,LOW);
}
void slowDown() // Slow down the car
{
  setMotorSpeed(128, 128);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
}
