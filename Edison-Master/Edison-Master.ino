// Ref: https://www.arduino.cc/en/Tutorial/MasterWriter

#include <Wire.h>

byte x = 0;

void setup() {

  Wire.begin(); // Join i2c bus (address optional for master)
  Serial.begin(115200);   
}

int arbitaryDeviceNum = 8;
int num=0;
  
void loop(){
   
  Wire.beginTransmission(arbitaryDeviceNum); // Transmit to device
  //Wire.write("c is ");  // Sends five bytes
  Wire.write(num);
  Wire.endTransmission(); // Stop transmitting
  
  Serial.println(num); 
  num++;

  if(num % 10 == 0){
    num=0;
  }
  
  delay(2500);
}
