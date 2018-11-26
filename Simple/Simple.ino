/*
  Switches the polarity on two pins. 

  On and off times can be adjusted by changing the corresponding
  variables. 

  This code uses Arduino's delay function for on and off times and
  should therefore not be used with time sensitive code.

  by Walther Jensen
  https://github.com/DecoChrom/Arduino/Simple
*/

#include <Arduino.h>

// The following line is not needed when compiled from Arduino IDE
void setDisplayPower(bool polarity, float voltage);

// Set display pins to two PWM output (5,6)
const int displayPin0 = 5;
const int displayPin1 = 6;

// Set on, off timings for display
// and a boolean to control the polarity
int onInterval = 2000;
int offInterval = 5000;
bool side = true;
float voltage = 3.0;

void setup()
{
  pinMode(displayPin0, OUTPUT);
  pinMode(displayPin1, OUTPUT);

  Serial.begin(9600);
  Serial.println("Device booted.");
}


void loop()
{
  Serial.print("Powering on. ");
  Serial.println((side ? "One side." : "Other side"));

  setDisplayPower(side, voltage);
  
  // We flip side to flip the polarity.
  side = !side;
  delay(onInterval);

  Serial.println("Powering off.");

  setDisplayPower(side, 0);
  delay(offInterval);

}

void setDisplayPower(bool polarity, float voltage){
  // Convert voltage to 255 range
  int v = (voltage / 5.0) * 255;
  
  if (polarity){
    analogWrite(displayPin0, v);
    analogWrite(displayPin1, 0);
  } else {
    analogWrite(displayPin0, 0);
    analogWrite(displayPin1, v);
  }

}