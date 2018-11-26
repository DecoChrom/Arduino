/*
  Switches the polarity on two pins with timers. 

  On and off times can be adjusted by changing the corresponding
  variables. 

  This code uses timers that allow for other time sensitive code to
  run.

  by Walther Jensen
  https://github.com/DecoChrom/Arduino/Advanced
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

// Don't change
long lastChange = 0;
bool powerIsOn = false;

void setup()
{
  pinMode(displayPin0, OUTPUT);
  pinMode(displayPin1, OUTPUT);

  Serial.begin(9600);
  Serial.println("Device booted.");
}

void loop()
{
  long now = millis();

  if (powerIsOn)
  {
    if (now - lastChange >= onInterval)
    {
      lastChange = now;
      Serial.println("Powering off.");

      setDisplayPower(side, 0);
      powerIsOn = false;
    }
  }
  else
  {
    if (now - lastChange >= offInterval)
    {
      lastChange = now;
      Serial.print("Powering on. ");
      Serial.println((side ? "One side." : "Other side"));

      setDisplayPower(side, voltage);

      // We flip side to flip the polarity.
      side = !side;
      powerIsOn = true;
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