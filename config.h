#ifndef CONFIG_H
#define CONFIG_H

// WiFi credentials
const char* ssid = "IQ Z9";
const char* password = "12345679";

// Gemini API Configuration
const String GEMINI_API_KEY = "AIzaSyB-E5QGT0ma9QOQdAuY7MztABgbce3GAro"; // Replace with your actual key
const String GEMINI_URL = "https://generativelanguage.googleapis.com/v1beta/models/gemini-pro:generateContent";

// Pin configuration
const int pirPin = 15;   // PIR sensor
const int ledPin = 2;    // LED

#endif