// Import required libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

// WiFi SSID & Password
const char* ssid = "FAB-Smart-Home";
const char* password = "11223344556677889900";

// TODO: Add host name by Wifi access.

// Static IP address to SoftAP
IPAddress local_ip(192,168,1,1);
// Gateway IP address to SoftAP
IPAddress gateway(192,168,1,1);

IPAddress subnet(255, 255, 255, 0);

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
  Serial.print(var +" -> " );
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
    Serial.println("----------------------");
    return ledState2;

  }
  return String();
}

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);
  delay(100);

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  // Initialize SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi & print IP
  // WiFi.begin(ssid, password);
  // waitForWiFiConnectOrReboot(true);

  // Initialize AP (Access Point)
  WiFi.softAP(ssid, password);
  // Configure AP (Access Point)
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  
  setupServer();
}

void loop() {

}

// Wait for WiFi connection, and, if not connected, reboot
void waitForWiFiConnectOrReboot(bool printOnSerial)
{
  uint32_t notConnectedCounter = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    if (printOnSerial)
    {
      Serial.print(".");
    }
    notConnectedCounter++;
    if (notConnectedCounter > 50)
    { // Reset board if not connected after 5s
      if (printOnSerial)
      {
        Serial.println("");
        Serial.println("------------------------------------------------------");
        Serial.println("Resetting due to Wifi not connecting...");
        Serial.println("------------------------------------------------------");
      }
      ESP.restart();
    }
  }
  if (printOnSerial)
  {
    // Print wifi IP addess
    Serial.println("");
    Serial.println("WiFi connected..!");
    Serial.print("Got IP: ");
    Serial.println(WiFi.localIP());
  }
}

// Setup Server
void setupServer()
{
  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });

  // Route to change GPIO
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
  Serial.println("HTTP server started");
}
