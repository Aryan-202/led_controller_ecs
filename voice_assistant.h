#ifndef VOICE_ASSISTANT_H
#define VOICE_ASSISTANT_H

#include <HTTPClient.h>
#include <ArduinoJson.h>

class VoiceAssistant {
private:
    String apiKey;
    String apiUrl;

public:
    VoiceAssistant(String key, String url) : apiKey(key), apiUrl(url) {}

    String processVoiceCommand(String command) {
        if (command.length() == 0) {
            return "Sorry, I didn't hear anything.";
        }

        // Convert command to lowercase for easier processing
        command.toLowerCase();
        
        // Simple voice command processing
        if (command.indexOf("turn on light") != -1 || command.indexOf("switch on light") != -1 || command.indexOf("light on") != -1) {
            return "LIGHT_ON";
        }
        else if (command.indexOf("turn off light") != -1 || command.indexOf("switch off light") != -1 || command.indexOf("light off") != -1) {
            return "LIGHT_OFF";
        }
        else if (command.indexOf("auto mode") != -1 || command.indexOf("automatic mode") != -1) {
            return "MODE_AUTO";
        }
        else if (command.indexOf("manual mode") != -1) {
            return "MODE_MANUAL";
        }
        else if (command.indexOf("status") != -1 || command.indexOf("what's the status") != -1) {
            return "GET_STATUS";
        }

        // If no simple command matches, use Gemini AI
        return askGemini(command);
    }

private:
    String askGemini(String query) {
        if (WiFi.status() != WL_CONNECTED) {
            return "Error: No internet connection";
        }

        HTTPClient http;
        String url = apiUrl + "?key=" + apiKey;
        
        http.begin(url);
        http.addHeader("Content-Type", "application/json");

        // Create the request payload
        DynamicJsonDocument doc(1024);
        JsonArray parts = doc.createNestedArray("contents").createNestedObject().createNestedArray("parts");
        JsonObject textPart = parts.createNestedObject();
        textPart["text"] = "You are a voice assistant for a smart home system. The system controls lights using an ESP32. Available commands: turn on/off lights, switch to auto/manual mode, get status. Respond with only one of these: LIGHT_ON, LIGHT_OFF, MODE_AUTO, MODE_MANUAL, GET_STATUS, or UNKNOWN if the command doesn't match. User said: " + query;

        String requestBody;
        serializeJson(doc, requestBody);

        int httpResponseCode = http.POST(requestBody);

        if (httpResponseCode == 200) {
            String response = http.getString();
            http.end();

            // Parse the response
            DynamicJsonDocument responseDoc(2048);
            deserializeJson(responseDoc, response);

            String geminiResponse = responseDoc["candidates"][0]["content"]["parts"][0]["text"];
            geminiResponse.trim();
            
            return geminiResponse;
        } else {
            http.end();
            return "Error: API request failed with code " + String(httpResponseCode);
        }
    }
};

#endif