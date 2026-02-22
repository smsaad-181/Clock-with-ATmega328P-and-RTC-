#include <Wire.h>

void setup(){
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Scanning I2C devices...");

  byte count = 0;
  for(byte address = 1; address < 127; address++){
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();

    if(error == 0){
      Serial.print("I2C device found at address 0x");
      if(address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
      count++;
    }
  }

  if(count == 0)
    Serial.println("No I2C devices found! Check your wiring!");
  else
    Serial.println("Scan complete!");
}

void loop(){}