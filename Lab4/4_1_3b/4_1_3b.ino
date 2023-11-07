

#include <WiFi.h>
#include <WebServer.h>

// Set your desired network credentials for AP mode
const char* ssid = "ESP32-Access-Point";
const char* password = "12345678"; // Minimum 8 characters for AP password

WebServer server(80);

// Variables to hold frequency and duty cycle values
int frequency = 3;
int dutyCycle = 50;

// HTML content with sliders
const char* html = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <script>
    function updateFrequency(value) {
      document.getElementById('frequencyValue').innerText = value;
    }
    function updateDutyCycle(value) {
      document.getElementById('dutyCycleValue').innerText = value;
    }
    function submitForm() {
      var freq = document.getElementById('freqSlider').value;
      var duty = document.getElementById('dutySlider').value;
      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/update?frequency=" + freq + "&dutyCycle=" + duty, true);
      xhr.send();
    }
  </script>
</head>
<body>
  <h2>Frequency & Duty Cycle Control</h2>
  <p>
    <label for="freq">Frequency (3 - 30Hz):</label>
    <input type="range" onchange="updateFrequency(this.value); submitForm();" id="freqSlider" name="freq" min="3" max="30" value="%FREQUENCY%">
    <span id="frequencyValue">%FREQUENCY%</span>Hz
  </p>
  <p>
    <label for="duty">Duty Cycle (0 - 100%):</label>
    <input type="range" onchange="updateDutyCycle(this.value); submitForm();" id="dutySlider" name="duty" min="0" max="100" value="%DUTYCYCLE%">
    <span id="dutyCycleValue">%DUTYCYCLE%</span>%
  </p>
</body>
</html>)rawliteral";

String processor(const String& var) {
  if (var == "FREQUENCY") {
    return String(frequency);
  }
  if (var == "DUTYCYCLE") {
    return String(dutyCycle);
  }
  return String();
}

void handleRoot() {
  String s = html;
  s.replace("%FREQUENCY%", String(frequency));
  s.replace("%DUTYCYCLE%", String(dutyCycle));
  server.send(200, "text/html", s);
}

void handleUpdate() {
  if (server.hasArg("frequency") && server.hasArg("dutyCycle")) {
    frequency = server.arg("frequency").toInt();
    dutyCycle = server.arg("dutyCycle").toInt();
    
    Serial.print("\nfrequency: ");
    Serial.print(frequency);

  }
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);

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
