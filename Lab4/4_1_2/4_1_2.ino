/*
  Author: Shibo Wang
  Date: 29th Oct 2023
*/
#define POTENTIOMETER 4
#define LED 10

//define ADC and calculated duty variables
int ADC;
int duty;

//define the constants of PWM port
const int LEDChannel0 = 0;
const int resolution = 14;
const int freq = 30;


void setup() {

  Serial.begin(9600); 
  //setup the LED channel 0, with certain frequency and resolution.
  ledcSetup(LEDChannel0,freq,resolution);
  //Attach LED port and PWM channel
  ledcAttachPin(LED, LEDChannel0);
}

void loop() {
  // collect ADC
  ADC = analogRead(POTENTIOMETER);
  // calculate duty cycle
  duty = map(ADC,0,4096,0,16384);
  //generate duty cycle
  ledcWrite(LEDChannel0,duty);
}
