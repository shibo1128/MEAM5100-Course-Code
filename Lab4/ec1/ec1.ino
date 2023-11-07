/*
  Author: Shibo Wang
  Date: 4th Mov 2023
*/
#include <WiFi.h>
#include <WiFiUdp.h>

#define SWITCH 1
#define motor1ENA 7
#define motor1ENB 8
#define SPEED 5
#define POTENTIOMETER 4

//define ADC and calculated duty variables
int ADC;
int duty;
int received_duty;

//define the constants of PWM port
const int LEDChannel0 = 0;
const int resolution = 12;
const int freq = 3000;

// WiFi router congifuration
const char* router_ssid = "TP-Link_E0C8";
const char* router_pwd = "52665134";

//received packet
const int UDP_PACKET_SIZE = 10;
char packetBuffer[UDP_PACKET_SIZE];
//sending packet
char udpBuffer[UDP_PACKET_SIZE];

// initialize WiFi UDP
WiFiUDP UDPTestServer;

//Set host IP, target IP, Gateway and subnet mask.
IPAddress myIP (192,168,1,196);
IPAddress targetIP (192,168,1,137);
IPAddress Gateway (192, 168, 1, 1);
IPAddress subnetMask (255, 255, 255, 0);

//--------------------------------------UDP send Function------------------------------------//
void fncUdpSend()
{
  // send what ever you want upto buffer size
    // collect ADC
  ADC = analogRead(POTENTIOMETER);
  // calculate duty cycle
  duty = map(ADC,0,4096,0,4096);
  udpBuffer[0] = duty & 0xff; // send 1st (LSB) byte of duty
  udpBuffer[1] = duty>>8; // send 2nd (MSB) byte of duty
  if (digitalRead(SWITCH)){
    udpBuffer[2]=0Xff;
  }
  else{
    udpBuffer[2]=0x00;
  }
  UDPTestServer.beginPacket(targetIP, 12345); // send to UDPport 12345
  UDPTestServer.printf(udpBuffer,3);
  UDPTestServer.endPacket();
  //Serial.printf("\n Send:");
  //Serial.println(udpBuffer);
}

//--------------------------------------Handle received data------------------------------------//
void handleUDPServer() {
  int cb = UDPTestServer.parsePacket();
  if (cb) {
    UDPTestServer.read(packetBuffer, UDP_PACKET_SIZE-1);
   if (packetBuffer[2]==0xff){
    digitalWrite(motor1ENA, HIGH); 
    digitalWrite(motor1ENB, LOW);
  }
  else{
    digitalWrite(motor1ENA, LOW); 
    digitalWrite(motor1ENB, HIGH);
  }
    
    received_duty=packetBuffer[0] | packetBuffer[1]<<8;
    ledcWrite(LEDChannel0,received_duty);
    //Serial.println("\n Receive:");
    Serial.printf("%c\n",packetBuffer[2]);
  }
}

void setup(){
  Serial.begin(115200);
  pinMode(SWITCH, INPUT);
  Serial.print("Connecting to ");
  Serial.println(router_ssid);

  WiFi.config(myIP, Gateway, subnetMask);
  WiFi.begin(router_ssid, router_pwd);

  UDPTestServer.begin(12345); // any UDP port# up to 65535
  // but higher is safer > 1023
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  pinMode(motor1ENA, OUTPUT); 
  pinMode(motor1ENB, OUTPUT); 

  //setup the LED channel 0, with certain frequency and resolution.
  ledcSetup(LEDChannel0,freq,resolution);
  //Attach LED port and PWM channel
  ledcAttachPin(SPEED, LEDChannel0);
}

void loop(){
  
  fncUdpSend();
  delay(100);
  handleUDPServer();
  delay(100);
}