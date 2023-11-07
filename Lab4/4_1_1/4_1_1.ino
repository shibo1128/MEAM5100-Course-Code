/*
  Author: Shibo Wang
  Date: 29th Oct 2023
*/
#define BUTTON 4
#define LED 10
bool state;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  state = digitalRead(BUTTON);
  if (state)
  {
    digitalWrite(LED, LOW);
  }
  else 
  {
    digitalWrite(LED, HIGH);
  }
}
