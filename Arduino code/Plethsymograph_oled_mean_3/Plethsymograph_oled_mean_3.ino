/*Takes a square pulse from an input pin and measures the period. Triggers on low to high transition but can easily be modified to trig from high to low.
The period is meaned and then calculated to BPM as the purpose of the project is to measure heart rate from a plethysmograph.
Author: Nikolaj Simonsen 19.09.2016
*/

// pin definitions
int Plethysmograph = 7; //input pin

//OLED init using HW SPI
#define OLED_DC 9
#define OLED_CS 10
#include <SPI.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiSpi.h"
SSD1306AsciiSpi oled;

// global variables
int Count=0; //counts the read loop
int LastPlethyState=0; //Pulse detection
int ReadPlethyState=0; //Pulse detection
int BPM=0; //Holds the BPM value
unsigned long PlethyRead; //One Period
unsigned long PlethySum=0; //Sum of periods
unsigned long PlethyMean=0; //Mean of sum
unsigned long OldValue=millis(); //Init with millis, used to count period length in milli secs 
unsigned long NewValue=0; //used to count period length in milli secs

void setup() {         
  pinMode (Plethysmograph, INPUT); //input pin
//OLED init
  oled.begin(&Adafruit128x64, OLED_CS, OLED_DC);
  oled.setFont(lcd5x7);  
  oled.set2X();
  oled.clear(); 
  Serial.begin (9600); 
}

void loop() {

ReadPlethyState=digitalRead (Plethysmograph); //read the pulse from plethysmograph
if (ReadPlethyState != LastPlethyState) { //compare the PlethyState to the last PlethyState, if change enter the loop
  //set Plethystate to the opposite
  if (LastPlethyState==0) {
    LastPlethyState=1;
    }
    else {
    LastPlethyState=0;
    }
  if (ReadPlethyState==HIGH)  { //if the state is high the pulse went from low to high
  NewValue=millis(); //read millis into newvalue
  PlethyRead=NewValue-OldValue; //calculate the period 
  OldValue=NewValue; //update oldvalue with new value
  PlethySum+=PlethyRead; //sum the periods
  Count++;
  }    
}
//The Count value can be changed to accept more readings in the read loop, remember to change the PlethyMean division
if (Count==2){
    Count=0; //reset count
    PlethyMean=0; //reset PlethyMean
    PlethyMean=PlethySum/2; //Mean the sum of periods
    PlethySum=0; //reset Plethysum 
    BPM=60000/PlethyMean; //calculate as BPM
    
    //update OLED
    oled.clear();
    oled.println("Heart rate");  
    oled.print(BPM);
    oled.print(" BPM");
/*
    Serial.print("PlethyMean ");
    Serial.print(PlethyMean); //Serial print the tacho value
    Serial.print("   ");
    Serial.print("BPM ");
    Serial.print(BPM); //Serial print the BPM value
    Serial.println("   ");
*/
}
  }
