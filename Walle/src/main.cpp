/*
 *  Project 31-web-led - main.cpp
 *      LED managment through a Web page
 *
 *      This Web page, resident in the same ESP32 allows to change
 *      the LED state: it is a case of stateless control
 *
 *      Austral 2023 - Electronica Digital - EAM
 */



#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <AsyncTCP.h>
#include <SPIFFS.h>


//Server config:
#include <Arduino.h>

#include <WiFi.h>
#include "wifi_ruts.h"

AsyncWebServer server(80);    // Create a webserver object that listens for HTTP request on port 80 

//Sensor config:
#define LED 2
const double sound_speed = 0.0343; 
#define TRIG_PIN 19
#define ECHO_PIN 21
#define PLAYER 5
const int threashold = 30;
int touchValue;

//Constants for server
const char* input_parameter1 = "output";
const char* input_parameter2 = "state";

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP32 WEB SERVER</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    p {font-size: 3.0rem;}
    body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
    .switch {position: relative; display: inline-block; width: 120px; height: 68px} 
    .switch input {display: none}
    .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 6px}
    .slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 3px}
    input:checked+.slider {background-color: #b30000}
    input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
  </style>
</head>
<body>
  <h2>ESP32 WEB SERVER</h2>
  %BUTTONPLACEHOLDER%
<script>function toggleCheckbox(element) {
  var xhr = new XMLHttpRequest();
  if(element.checked){ xhr.open("GET", "/update?output="+element.id+"&state=1", true); }
  else { xhr.open("GET", "/update?output="+element.id+"&state=0", true); }
  xhr.send();
}
</script>
</body>
</html>
)rawliteral";

String outputState(int output){
  if(digitalRead(output)){
    return "checked";
  }
  else {
    return "";
  }
}

// Replaces placeholder with button section in your web page
String processor(const String& var){
  //Serial.println(var);
  if(var == "BUTTONPLACEHOLDER"){
    String buttons = "";
    buttons += "<h4>Output - GPIO 32</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"32\" " + outputState(32) + "><span class=\"slider\"></span></label>";

    buttons += "<h4>Output - GPIO 25</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"25\" " + outputState(25) + "><span class=\"slider\"></span></label>";

    buttons += "<h4>Output - GPIO 27</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"27\" " + outputState(27) + "><span class=\"slider\"></span></label>";

   buttons += "<h4>Output - GPIO 13</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"13\" " + outputState(13) + "><span class=\"slider\"></span></label>";

    return buttons;
  }
  return String();
}


void InitServer(){
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Send a GET request to <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
  server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage1;
    String inputMessage2;
    // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    if (request->hasParam(input_parameter1) && request->hasParam(input_parameter2)) {
      inputMessage1 = request->getParam(input_parameter1)->value();
      inputMessage2 = request->getParam(input_parameter2)->value();
      digitalWrite(inputMessage1.toInt(), inputMessage2.toInt());
    }
    else {
      inputMessage1 = "No message sent";
      inputMessage2 = "No message sent";
    }
    Serial.print("GPIO: ");
    Serial.print(inputMessage1);
    Serial.print(" - Set to: ");
    Serial.println(inputMessage2);
    request->send(200, "text/plain", "OK");
  });
}

//Functions for sensor

long get_pulse( void ){
    return pulseIn( ECHO_PIN, HIGH );    // in microseconds
}

void
send_trigger( void )
{
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
}


void
setup(void)
{
    pinMode(32,OUTPUT);
    digitalWrite(32, LOW);
    pinMode(25, OUTPUT);
    digitalWrite(25, LOW);
    pinMode(27, OUTPUT);
    digitalWrite(27, LOW);
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);

    Serial.begin(SERIAL_BAUD); // Start the Serial communication to send messages to the computer
    delay(10);
    Serial.println();

    pinMode(LED, OUTPUT);

    wifi_connect();

    InitServer();

    server.begin();
    Serial.println("HTTP server started");

    //Pins for sensor and stuff
  pinMode(TRIG_PIN, OUTPUT);          // trigPin as output
  digitalWrite(TRIG_PIN, LOW);        // trigPin to low
  pinMode(ECHO_PIN, INPUT);           // echoPin as input
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PLAYER, OUTPUT);
}

void
loop(void)
{
if(digitalRead(32) == HIGH){
  long duration;
  double distance;

  send_trigger();
  duration = get_pulse();

  distance = duration * sound_speed / 2;
  Serial.println("Distance: " + (int)distance);

  touchValue = touchRead(4);

  Serial.println("Touch value: " + touchValue);

  if (distance < 50){
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(PLAYER, HIGH);

  }

  if(touchValue < threashold){
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(PLAYER, LOW);
  }

    delay(500);
}

}
