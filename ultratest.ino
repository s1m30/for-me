#include <NewPing.h>
// defines pins numbers

#define MAX_DISTANCE 300
NewPing sonar[3] = {   // Sensor object array.
  NewPing(A3, A2, MAX_DISTANCE), // Right Trig Pin
  NewPing(A1, A0, MAX_DISTANCE), //Left Trig Pin
  NewPing(13, 12, MAX_DISTANCE)//Center Trig Pin
};

long duration;
int distance;
void setup() {
  Serial.begin(9600); // Starts the serial communication
}
void loop() {
  int Right=sonar[0].ping_cm();
  delay(500);
  int Left=sonar[1].ping_cm();
  delay(700);
  int Center=sonar[2].ping_cm();
  delay(500);
  Serial.print("Right: ");
  Serial.print(Right);
  Serial.print("cm ");
  Serial.print("Left: ");
  Serial.print(Left);
  Serial.print("cm ");
  Serial.print("Center: ");
  Serial.print(Center);
  Serial.println("cm ");
  delay(15000);
//  // Clears the trigPin
//  digitalWrite(trigPin, LOW);
//  delayMicroseconds(2);
//  // Sets the trigPin on HIGH state for 10 micro seconds
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin, LOW);
//  // Reads the echoPin, returns the sound wave travel time in microseconds
//  duration = pulseIn(echoPin, HIGH);
//  // Calculating the distance
//  distance = duration * 0.034 / 2;
//  // Prints the distance on the Serial Monitor
//  Serial.print("Distance: ");
//  Serial.println(distance);
}
