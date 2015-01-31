    int i = 0;
    int x[100];
    int y[100];
    int z[100];    

void setup() {
    // initialize serial communication at 57600 bits per second:
    Serial.begin(57600);
    Serial.setTimeout(25);
}
 
// the loop routine runs over and over again forever:
void loop() {
  
    //Stuff from acceleration
  
    AccelerationReading accel = {0, 0, 0};
    
    accel = Bean.getAcceleration();
 
    uint16_t r = (abs(accel.xAxis)) / 4;
    uint16_t g = (abs(accel.yAxis)) / 4;
    uint16_t b = (abs(accel.zAxis)) / 4;
 
    Bean.setLed((uint8_t)r,(uint8_t)g,(uint8_t)b);
 

   if(i < 100){
     //record data
     x[i] = accel.xAxis;
     y[i] = accel.yAxis;
     z[i] = accel.zAxis;
   }
   
   //print 100 data sets
   if( i == 100){
     Serial.print("x\n");
     for(int k = 0; k < 100; k++){
        Serial.print(x[k]);
        Serial.print("\n");
     }
     Serial.print("\n");

     Serial.print("y\n");
     for(int w = 0; w < 100; w++){
        Serial.print(y[w]);
        Serial.print("\n");
     }
     Serial.print("\n");
     
     
     Serial.print("z\n");
     for(int n = 0; n < 100; n++){
        Serial.print(z[n]);
        Serial.print("\n");
     }
     Serial.print("\n");
     i = 0;
   }
    i++;
    Bean.sleep(10);
    
 
}
