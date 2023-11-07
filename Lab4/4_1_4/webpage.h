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
    function updateSpeedCycle(value) {
      document.getElementById('speedValue').innerText = value;
    }
    function submitForm() {
      var speed = document.getElementById('speedSlider').value;
      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/update?speedValue=" + speed, true);
      xhr.send();
    }
  </script>
</head>
<body>
  <h2>Speed Control</h2>
  <p>
    <label for="speed">Speed (-100 - +100):</label>
    <input type="range" onchange="updateSpeedCycle(this.value); submitForm();" id="speedSlider" name="duty" min="-100" max="100" value="%SPEED%">
    <span id="speedValue">%SPEED%</span>
  </p>
</body>
</html>)rawliteral";