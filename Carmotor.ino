#include <Servo.h>        
#include <NewPing.h>      

// L298N Control Pins
const int LeftMotorForward = 4;
const int LeftMotorBackward = 5;
const int RightMotorForward = 6;
const int RightMotorBackward = 7;
int speedPinLeft = 3;  // PWM pin to control speed of left motor
int speedPinRight = 11; // PWM pin to control speed of right motor

#define SONAR_NUM 4   // Number of sensors
#define MAX_DISTANCE 300  // Maximum distance (in cm) to ping

NewPing sonar[SONAR_NUM] = {   
  NewPing(A1, A0, MAX_DISTANCE), // Left Forward Trig Pin
  NewPing(13, 12, MAX_DISTANCE), // Center Trig Pin
  NewPing(A3, A2, MAX_DISTANCE), // Right Forward Trig Pin
  NewPing(A5, A4, MAX_DISTANCE) // Right Trig Pin
};

Servo Myservo;  // Servo's name
int distance;
int scanDistances[5]; // Holds the distances scanned: 0 = left, 1 = center, 2 = right
const int scanGap = 500; // Time gap between scans
unsigned long scanTime = 0;
int previousScanDistances[3]; // Holds the previous distances scanned


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
  delay(5000); 
   
}

void loop() {
  doScans();
  moveForward();
  handleObstacles();
  if(scanDistances[3] > 50) {
    // Only left distance is less than 15cm
    turnRight(delayDuration2(scanDistances[3],90,200));
    Serial.println(scanDistances[3]);
  }
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
  setMotorSpeed(120, 120);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveBackward() {
  setMotorSpeed(100, 100);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, HIGH);
}

void slowDown() {
  setMotorSpeed(90, 90);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
}

void longturnRight(int duration) {
  setMotorSpeed(255, 255);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  delay(duration);
  moveStop();
}

void longturnLeft(int duration) {
  setMotorSpeed(255, 255);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, HIGH);
  delay(duration);
  moveStop();
}

void turnRight(int duration) {
  setMotorSpeed(200, 200);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward,LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
  delay(duration);
  moveStop();
}

void turnLeft(int duration) {
  setMotorSpeed(200, 200);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward,HIGH );
  digitalWrite(LeftMotorBackward, LOW);
  delay(duration);
  moveStop();
}


void doScans() {
  if (millis() > scanTime) {
    scanDistances[0] = sonar[0].ping_cm();
    scanDistances[1] = sonar[1].ping_cm();
    scanDistances[2] = sonar[2].ping_cm();
    scanDistances[4] = sonar[3].ping_cm();
    // Print scanned distances for debugging
    Serial.print("Left Forward: ");
    Serial.print(scanDistances[0]);
    Serial.print(" cm, Center: ");
    Serial.print(scanDistances[1]);
    Serial.print(" cm, Right Forward: ");
    Serial.println(scanDistances[2]);
    
    scanTime = millis() + scanGap;
  }
}

void handleObstacles() {
  if ((scanDistances[0] <= 5 && scanDistances[1] <= 5) ||
    (scanDistances[1] <= 5 && scanDistances[2] <= 5)||
    (scanDistances[0] <= 5 && scanDistances[2] <= 5))  {
    moveBackward();
    delay(500);
    moveStop();
    Serial.println("Situation 0");
  }
  
  if (scanDistances[0] < 15 && scanDistances[1] >= 15 && scanDistances[2] >= 15) {
    // Only left distance is less than 15cm
    turnRight(delayDuration(scanDistances[0],300,250));
    turnLeft(150);
    Serial.println("Situation 1");
  } else if (scanDistances[2] < 15 && scanDistances[0] >= 15 && scanDistances[1] >= 15) {
    // Only right distance is less than 15cm
    turnLeft(delayDuration(scanDistances[2],340,250));
    turnRight(150);
    Serial.println("Situation 2");
  } 
  else if (scanDistances[0] > 15 && scanDistances[2] < 15 &&  scanDistances[1] <= 15 ){
    // Only right distance is less than 15 cm
    Serial.println("Obstacle detected on the left");
    turnLeft(delayDuration(scanDistances[2],340,250));
    turnRight(150);
    Serial.println("Situation 3");
    }
    else if (scanDistances[0] < 15 && scanDistances[2] > 15 &&  scanDistances[1]<= 15 ){
      Serial.println("Turning right");
      // Only left distance is less than 15 cm
      Serial.println("Obstacle detected on the right");
      turnRight(delayDuration(scanDistances[0],330,250));
      turnLeft(150);
      Serial.println("Situation 4");
} else if (scanDistances[0] < 15 && scanDistances[2] < 15 && scanDistances[1] >= 15) {
    // Both left and right distances are less than 15cm
    if (scanDistances[0] < scanDistances[2]) {
      turnLeft(250);
       // Turn right
    } else {
      turnRight(250);
       // Turn left
    }
    delay(500);
    Serial.println("Situation 5");
  } 
  else if (scanDistances[1] < 15 && scanDistances[0] < 15 && scanDistances[2] < 15) {
    // Center distance is less than 20cm
    slowDown();
    if (abs(scanDistances[0] - scanDistances[2]) <= 3) {
      // Check with servo
      Myservo.write(180); // Look left
      delay(500);
      int leftScan = sonar[1].ping_cm();

      Myservo.write(0); // Look right
      delay(500);
      int rightScan = sonar[1].ping_cm();

      Myservo.write(90); // Reset to center
      
      if (leftScan > rightScan) {
        longturnLeft(350);
      } else {
        longturnRight(350);
      }
      Serial.println("Situation 6");
    } else {
      if (scanDistances[0] > scanDistances[2]) {
        turnLeft(450);
      } else {
        turnRight(450);
      }
      Serial.println("Situation 7");
    }
  }
}

int delayDuration(int dir,int uplim,int lolim)
{int dur = map(dir, 0, 15, uplim, lolim);
 return(dur);
}

 int delayDuration2(int dir,int uplim,int lolim)
{int dur = map(dir, 20, 0, uplim, lolim);
 return(dur);
}
