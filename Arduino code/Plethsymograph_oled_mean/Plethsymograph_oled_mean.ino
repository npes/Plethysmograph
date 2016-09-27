// Simple SPI test for ebay 128x64 oled.

// pin definitions
#define OLED_DC 9
#define OLED_CS 10

#include <SPI.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiSpi.h"
int count=0;

SSD1306AsciiSpi oled;

// global variables
long ReadPlethyHigh;
long ReadPlethyLow;
unsigned long PlethySum;
int Plethysmograph = 7;
int LastPlethyState=0;
int ReadPlethyState=0;
int BPM=0;
int BPMmean=0;
int BPMfinal=0;
unsigned long OldValue=millis();
unsigned long NewValue=0;
//------------------------------------------------------------------------------
void setup() {         
  pinMode (Plethysmograph, INPUT); 
  oled.begin(&Adafruit128x64, OLED_CS, OLED_DC);
  oled.setFont(lcd5x7);  
  oled.set2X();
  oled.clear(); 
  Serial.begin (9600); 
}
//------------------------------------------------------------------------------
void loop() {

for (int i=0; i<10; i++){
ReadPlethyState=digitalRead (Plethysmograph); //read the pulse from plethysmograph
if (ReadPlethyState != LastPlethyState) { //compare the PlethyState to the last PlethyState, if change enter the loop
      if (LastPlethyState==0) {
      LastPlethyState=1;
    }
      else {
      LastPlethyState=0;
      }
  if (ReadPlethyState==HIGH)  { //if the state is high the Tacho went from low to high
    NewValue=millis();
//    Serial.print("NewValue ");
//    Serial.print(NewValue); //Serial print the tacho value
//    Serial.print("   ");
    PlethySum=NewValue-OldValue;
//    Serial.print("OldValue before ");
//    Serial.print(OldValue); //Serial print the tacho value
//    Serial.print("   ");
    OldValue=NewValue;
//    Serial.print("OldValue after ");
//    Serial.print(OldValue); //Serial print the tacho value
//    Serial.print("   ");
    BPM=60000/PlethySum;
    BPMmean+=BPM;
  }    
}
}
    BPMfinal=0;
    BPMfinal=BPMmean/10
    Serial.print("Plethysum ");
    Serial.print(PlethySum); //Serial print the tacho value
    Serial.print("   ");
    Serial.print("BPM ");
    Serial.print(BPM); //Serial print the BPM value
    Serial.println("   ");
  oled.clear();
  oled.println("Heart rate");  
  oled.print(BPM);
  oled.print(" BPM");

// delay (100);
  }
