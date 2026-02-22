#include "Wire.h"
#define DS1307_ADDRESS 0x68
byte zero = 0x00;

void setup(){
  Wire.begin();
  Serial.begin(9600);
  setDateTime();
  printDate();
  Serial.println("Time Set Successfully!");
}

void loop(){
  printDate();
  delay(1000);
}

void setDateTime(){

  // =============================
  // ONLY CHANGE THESE 2 VALUES:
  // =============================
  byte minute =  49;  // ← 49 minutes
  byte hour   =  10;  // ← 10 = 10 AM in 24h format
  // =============================

  // DO NOT CHANGE BELOW THIS LINE
  byte second  = 0;
  byte weekDay = 7;   // Saturday
  byte monthDay= 22;  // 22nd
  byte month   = 2;   // February
  byte year    = 26;  // 2026

  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero);

  Wire.write(decToBcd(second));
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));
  Wire.write(decToBcd(weekDay));
  Wire.write(decToBcd(monthDay));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));

  Wire.write(zero);
  Wire.endTransmission();
}

byte decToBcd(byte val){
  return ( (val/10*16) + (val%10) );
}

byte bcdToDec(byte val){
  return ( (val/16*10) + (val%16) );
}

void printDate(){
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero);
  Wire.endTransmission();

  Wire.requestFrom(DS1307_ADDRESS, 7);

  int second  = bcdToDec(Wire.read());
  int minute  = bcdToDec(Wire.read());
  int hour    = bcdToDec(Wire.read() & 0b111111);
  int weekDay = bcdToDec(Wire.read());
  int monthDay= bcdToDec(Wire.read());
  int month   = bcdToDec(Wire.read());
  int year    = bcdToDec(Wire.read());

  // Convert to 12-hour format
  String ampm = "AM";
  int hour12  = hour;

  if(hour == 0){
    hour12 = 12;
    ampm = "AM";
  }
  else if(hour < 12){
    hour12 = hour;
    ampm = "AM";
  }
  else if(hour == 12){
    hour12 = 12;
    ampm = "PM";
  }
  else{
    hour12 = hour - 12;
    ampm = "PM";
  }

  // Print to Serial Monitor
  Serial.print(month);
  Serial.print("/");
  Serial.print(monthDay);
  Serial.print("/");
  Serial.print(year);
  Serial.print("     ");
  Serial.print(hour12);
  Serial.print(":");
  if(minute < 10) Serial.print("0");
  Serial.print(minute);
  Serial.print(":");
  if(second < 10) Serial.print("0");
  Serial.print(second);
  Serial.print(" ");
  Serial.println(ampm);
}