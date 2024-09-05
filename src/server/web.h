#ifndef WEB_H
#define WEB_H

#include <Arduino.h>

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0" />
  <link rel="stylesheet" href="/static/style.css" />
  <title>Home climate station</title>
</head>
<body>
  <div class="page-title">Home station</div>
  <div class="container">
    <div class="row">
      <div class="col">
        <div class="title">CO2</div>
        <div class="value" id="co2_value"></div>
      </div>
      <div class="col">
        <div class="title">CO2 Temp</div>
        <div class="value" id="co2temp_value"></div>
      </div>
    </div>
    <div class="row">
      <div class="col">
        <div class="title">Temp</div>
        <div class="value" id="temp_value"></div>
      </div>
      <div class="col">
        <div class="title">Humidity</div>
        <div class="value" id="hum_value"></div>
      </div>
      <div class="col">
        <div class="title">Heat index</div>
        <div class="value" id="heat_value"></div>
      </div>
    </div>
  </div>
  <script src="/static/script.js"></script>
</body>
</html>
)rawliteral";

const char main_css[] PROGMEM = R"rawliteral(
body {
  margin: 2rem;
}
.page-title {
  font-weight: bold;
  font-size: 2rem;
  margin-bottom: 1rem;
}
.container {
  width: 100%;
  display: flex;
  flex-direction: column;
}
.row {
  display: flex;
  flex-direction: row;
}
.col {
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  margin: 0rem;
  padding: 0.8rem;
  background-color: #0277BD;
  border-style: solid;
  border-color: #9E9E9E;
  border-width: 0.5px;
  width: 100%;
}
.title {
  color: #FAFAFA;
  font-weight: bold;
  letter-spacing: 0.05rem;
  
}
.value {
  margin-top: 0.5rem;
  color: #FAFAFA;
}
)rawliteral";

const char main_js[] PROGMEM = R"rawliteral(
function run() {
  let co2elem = document.getElementById("co2_value");
  let co2tempElem = document.getElementById("co2temp_value");
  let tempElem = document.getElementById("temp_value");
  let humElem = document.getElementById("hum_value");
  let heatElem = document.getElementById("heat_value");

  fetch('/api/dashboard')
    .then(response => {
      return response.json();
    })
    .then(data => {
      co2elem.innerText = data.co2;
      co2tempElem.innerText = data.co2Temp;
      tempElem.innerText = data.temp + 'C';
      humElem.innerText = data.humidity + '%';
      heatElem.innerText = data.heatIndex + 'C';
    });
    setTimeout(run, 1000);
};
run();
)rawliteral";

#endif