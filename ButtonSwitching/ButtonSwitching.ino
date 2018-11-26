/*
  Switches the polarity on two pins using a button input. 

  It automatically switches polarity per button press

  by Walther Jensen
  https://github.com/DecoChrom/Arduino/Advanced
*/

#include <Arduino.h>

// The following line is not needed when compiled from Arduino IDE
void setDisplayPower(bool polarity, float voltage);

// Set display pins to two PWM output (5,6)
const int displayPin0 = 5;
const int displayPin1 = 6;

// Set analog 0 to sense the button
const int buttonPin = A0;

// Set on, off timings for display
// and a boolean to control the polarity
bool side = true;
float voltage = 3.0;

// Don't change
bool lastState = false;

void setup()
{
  pinMode(displayPin0, OUTPUT);
  pinMode(displayPin1, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.println("Device booted.");
}

void loop()
{
  bool state = digitalRead(buttonPin);
  delay(20);
  if (state != lastState)
  {
    lastState = state;

    if (state)
    {
      Serial.println("Powering off.");
      setDisplayPower(side, 0);
    }
    else
    {
      Serial.print("Powering on. ");
      Serial.println((side ? "One side." : "Other side"));

      setDisplayPower(side, voltage);

      // We flip side to flip the polarity.
      side = !side;
    }
  }

}

void setDisplayPower(bool polarity, float voltage)
{
  // Convert voltage to 255 range
  int v = (voltage / 5.0) * 255;

  if (polarity)
  {
    analogWrite(displayPin0, v);
    analogWrite(displayPin1, 0);
  }
  else
  {
    analogWrite(displayPin0, 0);
    analogWrite(displayPin1, v);
  }
}