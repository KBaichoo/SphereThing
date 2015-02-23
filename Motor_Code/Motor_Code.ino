#include <Servo.h>

# define RELAY 8

Servo myservo;

void arm(){
  // arm the speed controller, modify as necessary for your ESC  
  setSpeed(0);
  delay(1000); //delay 1 second,  some speed controllers may need longer
  int speed;
  for(int speed = 1; speed <= 10; speed++)
  {
       setSpeed(speed);
       delay(1000);
  }
  for(int speed = 10; speed >= 1; speed--)
  {
       setSpeed(speed);
       delay(1000);
  }
  setSpeed(0);
  
}

void setSpeed(int speed){
  // speed is from 0 to 100 where 0 is off and 100 is maximum speed
  //the following maps speed values of 0-100 to angles from 0-180,
  // some speed controllers may need different values, see the ESC instructions
  int angle = map(speed, 0, 100, 0, 180);
  myservo.write(angle);    
}

void switchDir()
{
        setSpeed(0);
        delay(5000);
        if(digitalRead(RELAY) == LOW)
             digitalWrite(RELAY, HIGH);
        else
             digitalWrite(RELAY, LOW);
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
  
  
  for(speed = 20; speed <= 70; speed+=10)
  {
      setSpeed(speed);
      delay(5000);
      switchDir();
      setSpeed(speed);
      delay(5000);
      setSpeed(0);
      delay(5000);
  }
  delay(1000);  
  
} 
