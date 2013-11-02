#include <Wire.h>
#include <AFMotor.h>
#include <Servo.h> 

byte movement;
int xservo;
int turnduration;
Servo myservo;  // create servo object to control a servo 


AF_DCMotor leftrear(2, MOTOR12_1KHZ); // set right front wheel
AF_DCMotor rightrear(3, MOTOR12_1KHZ); // set right rear wheel
AF_DCMotor rightfront(4, MOTOR12_1KHZ); // set left front wheel
AF_DCMotor leftfront(1, MOTOR12_1KHZ); // set left front wheel
 
void setup() 
{ 
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  myservo.write(90); // center servo
  turnduration = 500;

  rightrear.setSpeed(225);     // set the speed to 200/255
  leftrear.setSpeed(225);     // set the speed to 200/255
  rightfront.setSpeed(225);     // set the speed to 200/255
  leftfront.setSpeed(225);     // set the speed to 200/255
  Wire.begin(9);                // Start I2C Bus as a Slave (Device Number 9)
  Wire.onReceive(receiveEvent); // register event

  movement = 0;
} 
 
 
void loop() { 
  
    //myservo.write(xservo);

  
  if (movement == 0) {
    still();
    Serial.println("still");
  }
  else if (movement == 1) {
    north(turnduration);
    Serial.println("north");
  }
  else if (movement == 2) {
    south(turnduration);
    Serial.println("south");
  }
  else if (movement == 3) {
    west(turnduration);
    Serial.println("west");
  }
  else if (movement == 4) {
    east(turnduration);
    Serial.println("east");
  }
  else if (movement == 5) {
    clockwise(turnduration);
    Serial.println("clockwise");
  }  
  else if (movement == 6) {
    counterclockwise(turnduration);
    Serial.println("counterclockwise");
  }
  else {
    still();
  }
} 
 
void clockwise(int turnduration) {
  leftrear.run(FORWARD);
  rightrear.run(BACKWARD);
  rightfront.run(BACKWARD);
  leftfront.run(FORWARD);
  delay(turnduration);
}

void counterclockwise(int turnduration) {
  leftrear.run(BACKWARD);
  rightrear.run(FORWARD);
  rightfront.run(FORWARD);
  leftfront.run(BACKWARD); 
  delay(turnduration);
}

void north(int turnduration) {
  leftrear.run(FORWARD);
  rightrear.run(FORWARD);
  rightfront.run(FORWARD);
  leftfront.run(FORWARD);
  delay(turnduration);
}

void still() {
  leftrear.run(RELEASE);
  rightrear.run(RELEASE);
  rightfront.run(RELEASE);
  leftfront.run(RELEASE); 
}

void south(int turnduration) {
  leftrear.run(BACKWARD);
  rightrear.run(BACKWARD);
  rightfront.run(BACKWARD);
  leftfront.run(BACKWARD);
  delay(turnduration);
}

void east(int turnduration) {
  leftrear.run(BACKWARD);
  rightrear.run(FORWARD);
  rightfront.run(BACKWARD);
  leftfront.run(FORWARD); 
  delay(turnduration);

}

void west(int turnduration) {
  leftrear.run(FORWARD);
  rightrear.run(BACKWARD);
  rightfront.run(FORWARD);
  leftfront.run(BACKWARD); 
  delay(turnduration);
}

void receiveEvent(int howMany) {
  movement = Wire.read();    // receive byte as an integer
  turnduration = Wire.read();
  xservo = Wire.read();
}

