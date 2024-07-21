#include <Servo.h>        
#include <NewPing.h>      

// L298N Control Pins
const int LeftMotorForward = 4;
const int LeftMotorBackward = 5;
const int RightMotorForward = 6;
const int RightMotorBackward = 7;
int speedPinLeft = 9;  // PWM pin to control speed of left motor
int speedPinRight = 10; // PWM pin to control speed of right motor

#define SONAR_NUM 3       // Number of sensors
#define MAX_DISTANCE 300  // Maximum distance (in cm) to ping

NewPing sonar[SONAR_NUM] = {   
  NewPing(A1, A0, MAX_DISTANCE), // Left Trig Pin
  NewPing(13, 12, MAX_DISTANCE),  // Center Trig Pin
  NewPing(A3, A2, MAX_DISTANCE) // Right Trig Pin
};

Servo Myservo;  // Servo's name
boolean goesForward = false;
int distance;

int scanDistances[3]; // Holds the distances scanned: 0 = left, 1 = center, 2 = right
const int scanGap = 150; // Time gap between scans
unsigned long scanTime = 0;

int leftSpeed;
int rightSpeed;
int pwmAdjuster = 0;

void setup() {
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
  Myservo.attach(8);
  Myservo.write(90); // Center position
  delay(2000); // Wait for 2s.
  Serial.begin(9600);
}

void loop() {
  doScans();
  moveForward();
  handleObstacles();  
}

void setMotorSpeed(int leftSpeed, int rightSpeed) {
  analogWrite(speedPinLeft, leftSpeed);
  analogWrite(speedPinRight, rightSpeed);
}

void moveStop() {
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveForward() {
  setMotorSpeed(255, 255);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveBackward() {
  setMotorSpeed(200, 200);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, HIGH);
}

void slowDown() {
  setMotorSpeed(200, 200);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
}

void turnRight(int duration) {
  setMotorSpeed(255, 255);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  delay(duration);
  moveStop();
}

void turnLeft(int duration) {
  setMotorSpeed(255, 255);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, HIGH);
  delay(duration);
  moveStop();
}

void doScans() {
  if (millis() > scanTime) {
    scanDistances[0] = sonar[0].ping_cm();
    delay(250);
    scanDistances[1] = sonar[1].ping_cm();
    delay(250);
    scanDistances[2] = sonar[2].ping_cm();
    delay(250);
    
    // Print scanned distances for debugging
    Serial.print("Left: ");
    Serial.print(scanDistances[0]);
    Serial.print(" cm, Center: ");
    Serial.print(scanDistances[1]);
    Serial.print(" cm, Right: ");
    Serial.println(scanDistances[2]);
    
    scanTime = millis() + scanGap;
  }
}

void handleObstacles() {
  if (scanDistances[0] <= 2 && scanDistances[1] <= 2 && scanDistances[2] <= 2) {
    Serial.println("Obstacle very close in all directions, moving backward");
    moveBackward();
    delay(100);
    moveStop();
    return;
  }
  
  if (scanDistances[0] < 10 && scanDistances[1] >= 10 && scanDistances[2] >= 10) {
    // Only left distance is less than 10 cm
    Serial.println("Obstacle detected on the left");
    int mappedSpeed = map(scanDistances[0], 0, 10, 150, 255);
    setMotorSpeed(mappedSpeed, 255);
    delay(500);
  } else if (scanDistances[2] < 10 && scanDistances[0] >= 10 && scanDistances[1] >= 10) {
    // Only right distance is less than 10 cm
    Serial.println("Obstacle detected on the right");
    int mappedSpeed = map(scanDistances[2], 0, 10, 150, 255);
    setMotorSpeed(255, mappedSpeed);
    delay(500);
  } else if (scanDistances[0] < 15 && scanDistances[2] < 15 && scanDistances[1] >= 15) {
    // Both left and right distances are less than 15 cm
    Serial.println("Obstacles detected on both sides");
    if (scanDistances[0] < scanDistances[2]) {
      Serial.println("Turning right");
      setMotorSpeed(150, 255); // Turn right
    } else {
      Serial.println("Turning left");
      setMotorSpeed(255, 150); // Turn left
    }
    delay(500);
  } else if (scanDistances[1] < 10 && scanDistances[0] < 10 && scanDistances[2] < 10) {
    // Center distance is less than 10 cm
    Serial.println("Obstacle detected in the center");
    int mappedSpeed = map(scanDistances[0], 0, 10, 150, 255);
    setMotorSpeed(mappedSpeed, mappedSpeed);
    if (abs(scanDistances[0] - scanDistances[2]) <= 5) {
      // Check with servo
      Myservo.write(180); // Look left
      delay(500);
      int leftScan = sonar[1].ping_cm();

      Myservo.write(0); // Look right
      delay(500);
      int rightScan = sonar[1].ping_cm();

      Myservo.write(90); // Reset to center

      if (leftScan > rightScan) {
        Serial.println("Turning left based on servo scan");
        turnLeft(1000);
      } else {
        Serial.println("Turning right based on servo scan");
        turnRight(1000);
      }
    } else {
      if (scanDistances[0] > scanDistances[2]) {
        Serial.println("Turning right based on distance comparison");
        int mappedSpeed = map(scanDistances[0], 0, 10, 150, 255);
        setMotorSpeed(mappedSpeed, 255);
        delay(500);
      } else {
        Serial.println("Turning left based on distance comparison");
        int mappedSpeed = map(scanDistances[0], 0, 10, 150, 255);
        setMotorSpeed(255, mappedSpeed);
        delay(500);
      }
    }
  } else {
    moveForward(); // Continue moving forward at full speed
  }
}
