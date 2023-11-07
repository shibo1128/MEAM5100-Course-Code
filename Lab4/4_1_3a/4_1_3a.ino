/*
  Author: Shibo Wang
  Date: 29th Oct 2023
*/
#include <WiFi.h>
#include <WiFiUdp.h>

//Set PINs 
#define POTENTIOMETER 4
#define LED 10

//define ADC and calculated duty variables
int ADC;
int duty;
int received_duty;

//define the constants of PWM port
const int LEDChannel0 = 0;
const int resolution = 14;
const int freq = 30;

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
  duty = map(ADC,0,4096,0,16384);
  udpBuffer[0] = duty & 0xff; // send 1st (LSB) byte of duty
  udpBuffer[1] = duty>>8; // send 2nd (MSB) byte of duty
  UDPTestServer.beginPacket(targetIP, 12345); // send to UDPport 12345
  UDPTestServer.printf(udpBuffer,2);
  UDPTestServer.endPacket();
  Serial.printf("\n Send:");
  Serial.println(udpBuffer);
}

//--------------------------------------Handle received data------------------------------------//
void handleUDPServer() {
  int cb = UDPTestServer.parsePacket();
  if (cb) {
    UDPTestServer.read(packetBuffer, UDP_PACKET_SIZE-1);
   
    //int len = UDPTestServer.read(packetBuffer, UDP_PACKET_SIZE-1);
    //packetBuffer[len] = 0;
    received_duty=packetBuffer[0] | packetBuffer[1]<<8;
    ledcWrite(LEDChannel0,received_duty);
    //Serial.printf("\n Receive:");
    Serial.printf("%c\n",received_duty);
  }
}

//--------------------------------------Setup Function------------------------------------//
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
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

  //setup the LED channel 0, with certain frequency and resolution.
  ledcSetup(LEDChannel0,freq,resolution);
  //Attach LED port and PWM channel
  ledcAttachPin(LED, LEDChannel0);
}

//--------------------------------------Loop Function------------------------------------//
void loop() {
  // put your main code here, to run repeatedly:

  //strcpy(udpBuffer, "Hello");
  fncUdpSend();
  delay(1);
  handleUDPServer();
  delay(1);
}
