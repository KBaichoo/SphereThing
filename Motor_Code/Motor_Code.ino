#include <Servo.h>

Servo myservo;

void arm(){
  // arm the speed controller, modify as necessary for your ESC  
  setSpeed(0);
  delay(2000); //delay 1 second,  some speed controllers may need longer
}

void setSpeed(int speed){
  // speed is from 0 to 100 where 0 is off and 100 is maximum speed
  //the following maps speed values of 0-100 to angles from 0-180,
  // some speed controllers may need different values, see the ESC instructions
  /*int angle = map(speed, 0, 100, 0, 180);*/
  int angle = speed;
  myservo.write(angle);    
}

void setup()
{
  pinMode(13, OUTPUT);
  myservo.attach(6);
  arm();  
}


void loop()
{
  int speed;
  digitalWrite(13, HIGH);
  
  // sweep up from 0 to to maximum speed in 20 seconds
  for(speed = 90; speed > 50; speed -= 5) {
    setSpeed(speed);
    delay(5000);
  }
  
  for(speed = 50; speed < 90; speed += 5){
    setSpeed(speed);
    delay(5000);
  }
  setSpeed(90);
  delay(3000);
  // sweep back down to 0 speed.
  for(speed = 90; speed < 140; speed += 5) {
    setSpeed(speed);
    delay(5000);
  }
  
 for(speed = 140; speed > 90; speed -= 5) {
    setSpeed(speed);
    delay(5000);
  }
  
  setSpeed(90);  
  delay(5000); // stop the motor for 5 seconds
  
  /*
  setSpeed(85);
  delay(10000);
  setSpeed(90);
  delay(10000);
  setSpeed(95);*/
} 
