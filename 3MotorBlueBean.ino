#include <Servo.h>

Servo myservo;

void arm(){
  // arm the speed controller, modify as necessary for your ESC  
  setSpeed(0);
  delay(1000); //delay 1 second,  some speed controllers may need longer
  
  // sweep up from 0 to to maximum speed in 20 seconds
  int speed;
  //not high enough to start a disturbance
  for(speed = 0; speed <= 10; speed += 1) {
    setSpeed(speed);
    delay(1000);
  }
  // sweep back down to 0 speed.
  for(speed = 10; speed > 0; speed -= 1) {
    setSpeed(speed);
    delay(1000);
  }
}

void setSpeed(int speed){
  // speed is from 0 to 100 where 0 is off and 100 is maximum speed
  //the following maps speed values of 0-100 to angles from 0-180,
  // some speed controllers may need different values, see the ESC instructions
  int angle = map(speed, 0, 100, 0, 180);
  myservo.write(angle);   
// myservo1.write(angle); 
}

void setup()
{
 // pinMode(0, OUTPUT);
  myservo.attach(0);
//  myservo1.attach(6);

  arm();  
}


void loop()
{
  int speed;
  
   delay(1000);
  //runs revs outside of arming!
  for(speed = 20; speed <= 60; speed += 20) {
    setSpeed(speed);
    delay(5000);
    setSpeed(0);
    delay(3000);
  }
  /*setSpeed(20);
  delay(2000);*/
  
  setSpeed(0);  
  delay(3000); // stop the motor for 5 seconds
} 
