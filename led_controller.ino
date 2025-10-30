#include <WiFi.h>
#include <WebServer.h>
#include "config.h"
#include "web_content.h"
#include "voice_assistant.h"

// Global variables
int pirState = LOW;
int pirValue = 0;
bool manualControl = false;
bool ledManualState = false;

// Web server on port 80
WebServer server(80);

// Voice assistant
VoiceAssistant assistant(GEMINI_API_KEY, GEMINI_URL);

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  digitalWrite(ledPin, LOW);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Routes
  server.on("/", handleRoot);
  server.on("/led", handleLED);
  server.on("/mode", handleMode);
  server.on("/status", handleStatus);
  server.on("/voice", handleVoiceCommand); // New voice command route
  
  server.begin();
  Serial.println("HTTP server started");

  Serial.println("Calibrating PIR sensor...");
  delay(30000);
  Serial.println("PIR Sensor ready!");
}

void loop() {
  server.handleClient();

  if (!manualControl) {
    pirValue = digitalRead(pirPin);
    if (pirValue == HIGH) {
      digitalWrite(ledPin, HIGH);
      if (pirState == LOW) {
        Serial.println("Motion detected!");
        pirState = HIGH;
      }
    } else {
      digitalWrite(ledPin, LOW);
      if (pirState == HIGH) {
        Serial.println("Motion ended");
        pirState = LOW;
      }
    }
  }

  delay(100);
}

// Route handlers
void handleRoot() {
  server.send(200, "text/html", htmlPage);
}

void handleLED() {
  if (server.hasArg("state")) {
    String state = server.arg("state");

    if (state == "ON") {
      digitalWrite(ledPin, HIGH);
      ledManualState = true;
      server.send(200, "text/plain", "LED turned ON");
      Serial.println("LED manually ON");
    } else if (state == "OFF") {
      digitalWrite(ledPin, LOW);
      ledManualState = false;
      server.send(200, "text/plain", "LED turned OFF");
      Serial.println("LED manually OFF");
    }
  }
}

void handleMode() {
  if (server.hasArg("value")) {
    String mode = server.arg("value");

    if (mode == "MANUAL") {
      manualControl = true;
      server.send(200, "text/plain", "Manual mode activated");
      Serial.println("Switched to MANUAL mode");
    } else if (mode == "AUTO") {
      manualControl = false;
      server.send(200, "text/plain", "Auto mode activated");
      Serial.println("Switched to AUTO mode");
    }
  }
}

void handleStatus() {
  String json = "{";
  json += "\"ledState\":" + String(digitalRead(ledPin));
  json += ",\"motion\":" + String(digitalRead(pirPin));
  json += ",\"mode\":" + String(manualControl ? "\"manual\"" : "\"auto\"");
  json += "}";
  server.send(200, "application/json", json);
}

// New voice command handler
void handleVoiceCommand() {
  if (server.hasArg("command")) {
    String command = server.arg("command");
    Serial.println("Voice command received: " + command);
    
    String response = assistant.processVoiceCommand(command);
    Serial.println("Assistant response: " + response);
    
    // Execute the command
    if (response == "LIGHT_ON") {
      digitalWrite(ledPin, HIGH);
      ledManualState = true;
      server.send(200, "application/json", "{\"status\":\"success\", \"message\":\"Light turned on\", \"action\":\"light_on\"}");
    }
    else if (response == "LIGHT_OFF") {
      digitalWrite(ledPin, LOW);
      ledManualState = false;
      server.send(200, "application/json", "{\"status\":\"success\", \"message\":\"Light turned off\", \"action\":\"light_off\"}");
    }
    else if (response == "MODE_AUTO") {
      manualControl = false;
      server.send(200, "application/json", "{\"status\":\"success\", \"message\":\"Switched to auto mode\", \"action\":\"mode_auto\"}");
    }
    else if (response == "MODE_MANUAL") {
      manualControl = true;
      server.send(200, "application/json", "{\"status\":\"success\", \"message\":\"Switched to manual mode\", \"action\":\"mode_manual\"}");
    }
    else if (response == "GET_STATUS") {
      String status = digitalRead(ledPin) ? "ON" : "OFF";
      String mode = manualControl ? "manual" : "auto";
      String motion = digitalRead(pirPin) ? "detected" : "no motion";
      server.send(200, "application/json", 
        "{\"status\":\"success\", \"message\":\"Light is " + status + ", Mode: " + mode + ", Motion: " + motion + "\", \"action\":\"status\"}");
    }
    else {
      server.send(200, "application/json", "{\"status\":\"error\", \"message\":\"Command not recognized: " + response + "\"}");
    }
  } else {
    server.send(400, "application/json", "{\"status\":\"error\", \"message\":\"No command provided\"}");
  }
}