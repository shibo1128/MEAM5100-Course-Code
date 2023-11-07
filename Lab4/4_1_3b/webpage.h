/*
  Author: Shibo Wang
  Date: 1nd Nov 2023
*/

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