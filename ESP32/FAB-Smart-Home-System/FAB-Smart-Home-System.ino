/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com
*********/

// Import required libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

// Replace with your network credentials
const char* ssid = "P48";
const char* password = "11223344556677889900";

// Set LED GPIO
const int ledPin1 = 2;
const int ledPin2 = 4;
// Stores LED state
String ledState1;
String ledState2;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Replaces placeholder with LED state value
String processor(const String& var) {
  Serial.println("----------------");
  Serial.println(var);
  if (var == "STATE1") {
    if (digitalRead(ledPin1)) {
      ledState1 = "ON";
    }
    else {
      ledState1 = "OFF";
    }
    Serial.println(ledState1);
    return ledState1;
  }
  if (var == "STATE2") {
    if (digitalRead(ledPin2)) {
      ledState2 = "ON";
    }
    else {
      ledState2 = "OFF";
    }
    Serial.println(ledState2);
    return ledState2;
  }
  return String();
}

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  // Initialize SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });

  // Route to set GPIO to HIGH
  server.on("/1", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (digitalRead(ledPin1)) {
      digitalWrite(ledPin1, LOW);
    }
    else {
      digitalWrite(ledPin1, HIGH);
    }
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  server.on("/2", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (digitalRead(ledPin2)) {
      digitalWrite(ledPin2, LOW);
    }
    else {
      digitalWrite(ledPin2, HIGH);
    }
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Start server
  server.begin();
}

void loop() {

}
