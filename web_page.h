#ifndef WEB_PAGE_H
#define WEB_PAGE_H

const char* htmlPage = R"rawliteral(
<!DOCTYPE HTML>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { font-family: Arial; text-align: center; background: #f0f0f0; padding: 20px; }
    .button {
      background-color: #4CAF50; border: none; color: white;
      padding: 15px 32px; margin: 4px 2px;
      font-size: 16px; border-radius: 8px; width: 200px; cursor: pointer;
    }
    .button-off { background-color: #f44336; }
    .status { padding: 10px; margin: 10px; border-radius: 5px; font-weight: bold; }
    .auto { background-color: #2196F3; color: white; }
    .manual { background-color: #FF9800; color: white; }
  </style>
</head>
<body>
  <h2>ESP32 LED Controller</h2>
  <div class="status" id="modeStatus">Mode: Auto (PIR)</div>

  <p>LED Control:</p>
  <button class="button" onclick="controlLED('ON')">Turn LED ON</button><br>
  <button class="button button-off" onclick="controlLED('OFF')">Turn LED OFF</button><br><br>

  <button class="button" onclick="setMode('MANUAL')">Manual Mode</button><br>
  <button class="button" onclick="setMode('AUTO')">Auto Mode (PIR)</button><br>

  <p id="status">Status: Loading...</p>

  <script>
    function controlLED(state) {
      fetch('/led?state=' + state)
        .then(response => response.text())
        .then(data => {
          document.getElementById('status').innerHTML = 'Status: ' + data;
        });
    }

    function setMode(mode) {
      fetch('/mode?value=' + mode)
        .then(response => response.text())
        .then(data => {
          document.getElementById('status').innerHTML = 'Status: ' + data;
          document.getElementById('modeStatus').innerHTML = 
            'Mode: ' + (mode === 'MANUAL' ? 'Manual' : 'Auto (PIR)');
          document.getElementById('modeStatus').className =
            'status ' + (mode === 'MANUAL' ? 'manual' : 'auto');
        });
    }

    setInterval(function() {
      fetch('/status')
        .then(response => response.json())
        .then(data => {
          document.getElementById('status').innerHTML =
            'Status: LED ' + (data.ledState ? 'ON' : 'OFF') +
            ' | Motion: ' + (data.motion ? 'DETECTED' : 'No motion');
        });
    }, 2000);
  </script>
</body>
</html>
)rawliteral";

#endif
