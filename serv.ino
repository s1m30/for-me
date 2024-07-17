#include <Servo.h>        // Include Servo Library
#include <NewPing.h>        // Include Servo Librar
#define MAX_DISTANCE 250
Servo Myservo;  // Servo's
int distanceRight; 
int distanceLeft; 
NewPing sonar(13, 12, MAX_DISTANCE);  // Center Trig Pin
void setup() {
  Myservo.attach(8);
  Myservo.write(90);
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  Myservo.write(90);
  Serial.println(sonar.ping_cm()); 
  delay(5000);  
  Myservo.write(180);
  distanceRight =  sonar.ping_cm();
  delay(5000);
  Serial.print("Right; ");
  Serial.print(distanceRight);
  Myservo.write(0);
  distanceLeft = sonar.ping_cm();
  delay(5000);
  Serial.print(" Left; ");
  Serial.println(distanceLeft);

 
}
