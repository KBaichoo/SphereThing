#include <Servo.h>

Servo myservo;
String incomingString;

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
  Serial.print("the values is ");
  Serial.print(speed);
  Serial.print("\n");  
}

void setup()
{
  myservo.attach(0);
  Serial.begin(57600);
  Serial.setTimeout(25);
  arm();  
}


void loop()
{
  // If there is incoming value
  if(Serial.available() > 0)
  {
    // read the value
    char ch = Serial.read();
  
    /*
    *  If ch isn't a newline
    *  (linefeed) character,
    *  we will add the character
    *  to the incomingString
    */
    if (ch != 'x'){
      // Print out the value received
      // so that we can see what is
      // happening
      
      Serial.print("I have received: ");
      Serial.print(ch);
      Serial.print('\n');
    
      // Add the character to
      // the incomingString
      incomingString += ch;
    }
    // received a newline (linefeed) character
    // this means we are done making a string
    else{
      // print the incoming string
      Serial.println("I am printing the entire string");
      Serial.println(incomingString);
    
      // Convert the string to an integer
      int val = incomingString.toInt();
    
      // print the integer
      Serial.println("Printing the value: ");
      Serial.println(val);
    
      /*
      *  We only want to write an integer between
      *  0 and 180 to the motor. 
      */
      if (val > -1 && val <= 100) {
       // Write to Servo
       setSpeed(val);
     }
     // The value is not between 0 and 180.
     // We do not want write this value to
     // the motor.
     else {
       Serial.println("Value is NOT between 0 and 180");
       // IT'S a TRAP!
       Serial.println("Error with the input");
     }
    
      // Reset the value of the incomingString
      incomingString = "";
    }
  }
}
