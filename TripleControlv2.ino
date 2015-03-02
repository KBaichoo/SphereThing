//Triple ESC Serial Control
#include <Servo.h>

Servo myservo1;
Servo myservo2;
Servo myservo3;
String incomingString;

void arm(){
  // arm the speed controller, modify as necessary for your ESC  
  setSpeed(0, 'a');
  setSpeed(0, 'b');
  setSpeed(0, 'c');
  delay(1000); //delay 1 second,  some speed controllers may need longer
  
  // sweep up from 0 to to maximum speed in 20 seconds
  int speed;
  //not high enough to start a disturbance
  for(speed = 0; speed <= 10; speed += 1) {
    setSpeed(speed,'a');
    setSpeed(speed, 'b');
    setSpeed(speed, 'c');
    delay(1000);
  }
  // sweep back down to 0 speed.
  for(speed = 10; speed > 0; speed -= 1) {
    setSpeed(speed, 'a');
    setSpeed(speed, 'b');
    setSpeed(speed, 'c');
    delay(1000);
  }
}


void setSpeed(int speed, char servoNum) {
  // speed is from 0 to 100 where 0 is off and 100 is maximum speed
  //the following maps speed values of 0-100 to angles from 0-180,
  // some speed controllers may need different values, see the ESC instructions
  int angle = map(speed, 0, 100, 0, 180);
  if(servoNum == 'a')
     myservo1.write(angle);
  else if(servoNum == 'b')
     myservo2.write(angle);
  else
     myservo3.write(angle);  
}





void setup() {
  myservo1.attach(0);
  myservo2.attach(1);
  myservo3.attach(2);
  Serial.begin(57600);
  Serial.setTimeout(25);
  arm();  
}


void loop() {
  if(Serial.available() > 0) {
    char ch = Serial.read();
    if (ch != 'x' &&  !(ch == 'a' || ch == 'b' || ch == 'c')){
      
      Serial.print("I have received: ");
      Serial.print(ch);
    
      incomingString += ch;
    } else if(ch == 'a' || ch == 'b' || ch == 'c' || ch =='d' ){
       int val = incomingString.toInt();
       Serial.println("Printing the value: ");
       Serial.println(val);
       if(val > -1 && val <= 100)
       {
          Serial.println("Value is between 0 and 180");
          if(ch != 'd'){
            //just turn one motor on.
            Serial.print("Setting speed to Servo: ");
            Serial.println(val);
            setSpeed(val, ch);
          }else{
            //turn on all motors
            Serial.print("Setting ALL servos to:");
            Serial.println(val);
            setSpeed(val, 'a');
            setSpeed(val, 'b');
            setSpeed(val, 'c'); 
          }
       }
       else
       {
           Serial.println("Value is NOT between 0 and 180");
           Serial.println("Error with the input");
       }
       incomingString = "";
    } else if(ch == 'x'){
      //emergency exit;
      setSpeed(0,'a');
      setSpeed(0, 'b');
      setSpeed(0, 'c');
    }
  }
}

