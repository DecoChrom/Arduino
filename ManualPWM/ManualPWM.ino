unsigned long now = 0;
unsigned long lastChange = 0;
int deltaHigh = 360;
int deltaLow = 140;
bool flag = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}

void loop() {
  now = micros();
  if (now < lastChange)
  {
    lastChange = now;
  }
  digitalWrite(5, LOW);
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
