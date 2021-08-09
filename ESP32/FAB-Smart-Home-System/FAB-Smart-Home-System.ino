// Import required libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include "DHT.h"

// WiFi SSID & Password
const char* ssid = "FAB-Smart-Home";
const char* password = "11223344556677889900";

// TODO: Add host name by Wifi access.

// Static IP address to SoftAP
IPAddress local_ip(192, 168, 1, 1);
// Gateway IP address to SoftAP
IPAddress gateway(192, 168, 1, 1);

IPAddress subnet(255, 255, 255, 0);

// Digital pin connected to the DHT sensor
#define DHTPIN 33 // musst be a output digital pin

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22 // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);


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
  Serial.print(var + " -> " );
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

  dht.begin();
  setupServer();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f))
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
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

  // Route to load FABMationLogo.png file
  server.on("/FABMationLogo.png", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/FABMationLogo.png", "image/png");
  });

  // Route to load SmartHome.png file
  server.on("/SmartHome.png", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/SmartHome.png", "image/png");
  });

  // Route to change GPIO status
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
