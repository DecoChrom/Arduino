/*
  ManualPWM

  This example shows how to create PWM by using the micros-function and avoiding analogWrite

  Using micros, there is no need using analogWrite, which overrides all pinmode-settings
  and thus disables any of the built-in pull-up resistors. Another advantage is that the
  code is free of delay-commands.

  Creating a manual PWM will still pulse bursts of 5v into your displays, which may
  lead to deterioration of the electrolyte and aging of the display.

  A variable using unsigned long to store the micros will overflow after approx. 70 minutes after 
  the Arduino started running.
  
  by Heiko Müller
  https://github.com/DecoChrom/Arduino/ManualPWM
  
*/

//time-keeping variables
unsigned long now = 0;
unsigned long lastChange = 0;
// this will give you ~1.5v readout on the voltmeter
int deltaHigh = 360;
int deltaLow = 140;
//needed to alternate states
bool flag = false;

void setup() {
  // setting pins 5 and 6 to output
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}

void loop() {
  //reading current runtime in micro-seconds
  now = micros();
  //checking for overflow, which will happen approx. 70 minutes after program started running
  if (now < lastChange)
  {
    lastChange = now;
  }
  //setting pin 5 to ground
  digitalWrite(5, LOW);
  //alternating between HIGH and LOW on pin 6 depending on values deltaHigh and deltaLow
  if ((now-lastChange > deltaHigh) && !flag)
  {
    lastChange = now;
    digitalWrite(6, HIGH); 
    flag = true;
  }
  if ((now-lastChange > deltaLow) && flag)
  {
    lastChange = now;
    digitalWrite(6, LOW);  
    flag = false; 
  } 
}
