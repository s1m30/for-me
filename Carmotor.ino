int in1 = 2;
int in2 = 5;

int in1 =  n2 = 3;

void setup() {
  // put your setup code here, to run once:
   pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1,   OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  //(Optional)
  // pinMode(9,   OUTPUT); 
  // pinMode(10, OUTPUT);
  //(Optional)
}

void loop() { 
   // put your main code here, to run repeatedly:

  //Controlling speed (0   = off and 255 = max speed):     
  //(Optional)
  // analogWrite(9, 100); //ENA   pin
  // analogWrite(10, 200); //ENB pin
  //(Optional)
  
  forword();
  delay(3000);
  backword();
  delay(3000);
  turnRight();
  delay(3000);
  turnLeft();
  delay(3000);
  Stop();
  delay(3000);
}

void forword(){  //forword
digitalWrite(in1, LOW); //Left Motor backword Pin 
digitalWrite(in2, HIGH); //Left Motor forword Pin 
digitalWrite(in3, HIGH); //Right Motor forword Pin 
digitalWrite(in4, LOW); //Right Motor backword Pin 
}
void backword(){ //backword
digitalWrite(in1, HIGH); //Left Motor backword Pin 
digitalWrite(in2, LOW); //Left Motor forword Pin 
digitalWrite(in3, LOW); //Right Motor forword Pin 
digitalWrite(in4, HIGH); //Right Motor backword Pin 
}
void turnRight(){ //turnRight
digitalWrite(in1, LOW); //Left Motor backword Pin 
digitalWrite(in2, HIGH); //Left Motor forword Pin 
digitalWrite(in3, LOW); //Right Motor forword Pin 
digitalWrite(in4, HIGH); //Right Motor backword Pin 
}
void turnLeft(){ //turnLeft
digitalWrite(in1, HIGH); //Left Motor backword Pin 
digitalWrite(in2, LOW); //Left Motor forword Pin 
digitalWrite(in3, HIGH); //Right Motor forword Pin 
digitalWrite(in4, LOW); //Right Motor backword Pin 
}
void Stop(){ //stop
digitalWrite(in1, LOW); //Left Motor backword Pin 
digitalWrite(in2, LOW); //Left Motor forword Pin 
digitalWrite(in3, LOW); //Right Motor forword Pin 
digitalWrite(in4, LOW); //Right Motor backword Pin 
}
