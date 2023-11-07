/*
  Author: Shibo Wang
  Date: 1nd Nov 2023
*/

#include <WiFi.h>
#include <WebServer.h>
#include "webpage.h"
#define motor1ENA 7
#define motor1ENB 8
#define SPEED 5

// Set your desired network credentials for AP mode
const char* ssid = "ESP32-Access-Point";
const char* password = "12345678"; // Minimum 8 characters for AP password
int frequency=3000;
WebServer server(80);

// Variables to hold duty cycle values

int speed;
int duty;
const int LEDChannel0 = 0;
const int resolution = 12;


String processor(const String& var) {

  if (var == "SPEED") {
    return String(speed);
  }
  return String();
}

void handleRoot() {
  String s = html;

  s.replace("%SPEED%", String(speed));
  server.send(200, "text/html", s);
}

void handleUpdate() {
  if (server.hasArg("speedValue")) {
 
    speed = server.arg("speedValue").toInt();
    

    //setup the LED channel 0, with certain frequency and resolution.
    ledcSetup(LEDChannel0,frequency,resolution);
    //Attach LED port and PWM channel
    ledcAttachPin(SPEED, LEDChannel0);
    Serial.print(speed);
    if (speed>=0){
      digitalWrite(motor1ENA, HIGH); 
      digitalWrite(motor1ENB, LOW);
      duty = map(speed,0,100,0,4096);
    }
    else{
      digitalWrite(motor1ENA, LOW); 
      digitalWrite(motor1ENB, HIGH);
      duty = map(-speed,0,100,0,4096);
    }
    // calculate duty cycle
    
    //generate duty cycle
    ledcWrite(LEDChannel0,duty);

  }
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);

  pinMode(motor1ENA, OUTPUT); 
  pinMode(motor1ENB, OUTPUT); 
   

  // Set up the ESP32 WiFi in AP mode
  WiFi.softAP(ssid, password);
  Serial.println("Access Point Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());
  server.begin();
  server.on("/", handleRoot);
  server.on("/update", handleUpdate);

  
}

void loop() {
  server.handleClient();
}
