#include <Wire.h> //include library for I2C
#include <PVision.h>

int IRleft = 0;  // Compound Eye Left      - analog  input    A2 *looking out
int IRright = 3;  // Compound Eye Right     - analog  input    A3       
int IRup = 1;  // Compound Eye Up        - analog  input    A4
int IRdown =  2;  // Compound Eye Down      - analog  input    A5
int IRleds = 0;  // Compound Eye LEDs      - digital output   D0
int leftIRvalue;
int rightIRvalue;
int upIRvalue;
int downIRvalue;
int distance;
int initLeft;
int initRight;
int initUp;
int initDown;


PVision ircam;
byte result;
byte movement = 0;
int xservo;
int turnduration;

void setup()
{
  Serial.begin(9600);
  ircam.init();
  Wire.begin(); // Start I2C Bus as Master
  xservo = 90;
  turnduration = 100;
  
  
  digitalWrite(IRleds,HIGH);                                  // turn on IR LEDs to read TOTAL IR LIGHT (ambient + reflected)
  delayMicroseconds(100);                                     // Allow time for phototransistors to respond. (may not be needed)
  leftIRvalue=analogRead(IRleft);                             // TOTAL IR = AMBIENT IR + LED IR REFLECTED FROM OBJECT
  rightIRvalue=analogRead(IRright);                           // TOTAL IR = AMBIENT IR + LED IR REFLECTED FROM OBJECT
  upIRvalue=analogRead(IRup);                                 // TOTAL IR = AMBIENT IR + LED IR REFLECTED FROM OBJECT
  downIRvalue=analogRead(IRdown);                             // TOTAL IR = AMBIENT IR + LED IR REFLECTED FROM OBJECT
  
  initLeft = leftIRvalue;
  initRight = rightIRvalue;
  initUp = upIRvalue;
  initDown = downIRvalue;
}

void loop()
{
  IReye();
  //delay(1000);
  result = ircam.read();
  
  if (result && BLOB1) {
    movement = 1; //north
    if (ircam.Blob1.X > 700) {
      //xservo = xservo - 5;
      movement = 6; //counter clockwise
      Serial.println(xservo);
    }
    else if (ircam.Blob1.X < 300) {
      //xservo = xservo + 5;
      Serial.println(xservo);
      movement = 5; //clockwise
    }
    else if (ircam.Blob1.Size > 2) {
      movement = 1; //north / forward
    }
    else {
      movement = 0; //still
    }
    Wire.beginTransmission(9); // transmit to device #9
    Wire.write(movement);
    Wire.write(turnduration); 
    Wire.write(xservo);
    Wire.endTransmission();    // stop transmitting
    //Serial.print("BLOB1 detected. X:");
    Serial.println(ircam.Blob1.X);
    //Serial.print(" Y:");
    //Serial.print(ircam.Blob1.Y);
    //Serial.print(" Size:");
    //Serial.println(ircam.Blob1.Size);
  }
 
  else {
    movement = 0;
    xservo = xservo;
    Wire.beginTransmission(9); // transmit to device #9
    Wire.write(movement);           
    Wire.write(turnduration); 
    Wire.write(xservo);
    Wire.endTransmission();    // stop transmitting
  }

  // Short delay...
  //delay(10);
  
}

void IReye()//===============================================================Read IR compound eye================================================
{

  digitalWrite(IRleds,HIGH);                                  // turn on IR LEDs to read TOTAL IR LIGHT (ambient + reflected)
  delayMicroseconds(100);                                     // Allow time for phototransistors to respond. (may not be needed)
  leftIRvalue=analogRead(IRleft);                             // TOTAL IR = AMBIENT IR + LED IR REFLECTED FROM OBJECT
  rightIRvalue=analogRead(IRright);                           // TOTAL IR = AMBIENT IR + LED IR REFLECTED FROM OBJECT
  upIRvalue=analogRead(IRup);                                 // TOTAL IR = AMBIENT IR + LED IR REFLECTED FROM OBJECT
  downIRvalue=analogRead(IRdown);                             // TOTAL IR = AMBIENT IR + LED IR REFLECTED FROM OBJECT
  
  leftIRvalue = leftIRvalue - initLeft;                
  rightIRvalue = rightIRvalue - initRight;                      
  upIRvalue = upIRvalue - initUp;                              
  downIRvalue = downIRvalue - initDown;                      

  distance=(leftIRvalue+rightIRvalue+upIRvalue+downIRvalue)/4;// distance of object is average of reflected IR
  
//  Serial.print("leftIRvalue: ");
//  Serial.println(leftIRvalue);
//  Serial.print("rightIRvalue: ");
//  Serial.println(rightIRvalue);
//  Serial.print("upIRvalue: ");
//  Serial.println(upIRvalue);
//  Serial.print("downIRvalue: ");
//  Serial.println(downIRvalue);
//
//  Serial.println(distance);
  
  delay(10);
  
  if (leftIRvalue > 10 || rightIRvalue > 10 || upIRvalue > 10 || downIRvalue > 10) {
    if (leftIRvalue > rightIRvalue && leftIRvalue > upIRvalue && leftIRvalue > downIRvalue) {
      Serial.println("left");
    } 
    else if (rightIRvalue > leftIRvalue && rightIRvalue > upIRvalue && rightIRvalue > downIRvalue) {
      Serial.println("right");
    }
    else if (upIRvalue > leftIRvalue && upIRvalue > rightIRvalue && upIRvalue > downIRvalue) {
      Serial.println("up"); 
    }
    else {
      Serial.println("down"); 
    }
  } else {
    Serial.println("nothing");
  }
}
