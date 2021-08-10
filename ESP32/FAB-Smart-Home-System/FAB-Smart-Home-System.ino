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
const int mr1Pin = 25;
const int mr2Pin = 32;
const int kPin = 32;
const int skPin = 32;
const int aPin = 32;
const int c1Pin = 32;
const int c2Pin = 32;
const int sPin = 32;
const int d1Pin = 32;
const int d2Pin = 32;
const int dgPin = 32;



// Stores LED state
String mr1State;
String mr2State;
String kState;
String skState;
String aState;
String c1State;
String c2State;
String sState;
String d1State;
String d2State;
String dgState;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Replaces placeholder with LED state value
String processor(const String& var) {
  Serial.print(var + " -> " );
  if (var == "MR1") {
    if (digitalRead(mr1Pin)) {
      mr1State = "1";
    }
    else {
      mr1State = "0";
    }
    Serial.println(mr1State);
    return mr1State;
  }
  if (var == "MR2") {
    if (digitalRead(mr2Pin)) {
      mr2State = "1";
    }
    else {
      mr2State = "0";
    }
    Serial.println(mr2State);
    Serial.println("----------------------");
    return mr2State;

  }
  if (var == "K") {
    if (digitalRead(kPin)) {
      kState = "1";
    }
    else {
      kState = "0";
    }
    Serial.println(kState);
    Serial.println("----------------------");
    return kState;

  }
  if (var == "SK") {
    if (digitalRead(skPin)) {
      skState = "1";
    }
    else {
      skState = "0";
    }
    Serial.println(skState);
    Serial.println("----------------------");
    return skState;

  }
  if (var == "A") {
    if (digitalRead(aPin)) {
      aState = "1";
    }
    else {
      aState = "0";
    }
    Serial.println(aState);
    Serial.println("----------------------");
    return aState;

  }
  if (var == "C1") {
    if (digitalRead(c1Pin)) {
      c1State = "1";
    }
    else {
      c1State = "0";
    }
    Serial.println(c1State);
    Serial.println("----------------------");
    return c1State;

  }
  if (var == "C2") {
    if (digitalRead(c2Pin)) {
      c2State = "1";
    }
    else {
      c2State = "0";
    }
    Serial.println(c2State);
    Serial.println("----------------------");
    return c2State;

  }
  if (var == "S") {
    if (digitalRead(sPin)) {
      sState = "1";
    }
    else {
      sState = "0";
    }
    Serial.println(sState);
    Serial.println("----------------------");
    return sState;

  }
  if (var == "D1") {
    if (digitalRead(d1Pin)) {
      d1State = "1";
    }
    else {
      d1State = "0";
    }
    Serial.println(d1State);
    Serial.println("----------------------");
    return d1State;

  }
  if (var == "D2") {
    if (digitalRead(d2Pin)) {
      d2State = "1";
    }
    else {
      d2State = "0";
    }
    Serial.println(d2State);
    Serial.println("----------------------");
    return d2State;

  }
  if (var == "DG") {
    if (digitalRead(dgPin)) {
      dgState = "1";
    }
    else {
      dgState = "0";
    }
    Serial.println(dgState);
    Serial.println("----------------------");
    return dgState;

  }
  return String();
}

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);
  delay(100);

  pinMode(mr1Pin, OUTPUT);
  pinMode(mr2Pin, OUTPUT);
  pinMode(kPin, OUTPUT);
  pinMode(skPin, OUTPUT);
  pinMode(aPin, OUTPUT);
  pinMode(c1Pin, OUTPUT);
  pinMode(c2Pin, OUTPUT);
  pinMode(sPin, OUTPUT);
  pinMode(d1Pin, OUTPUT);
  pinMode(d2Pin, OUTPUT);
  pinMode(dgPin, OUTPUT);

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
//  // Wait a few seconds between measurements.
//  delay(2000);
//
//  // Reading temperature or humidity takes about 250 milliseconds!
//  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
//  float h = dht.readHumidity();
//  // Read temperature as Celsius (the default)
//  float t = dht.readTemperature();
//  // Read temperature as Fahrenheit (isFahrenheit = true)
//  float f = dht.readTemperature(true);
//
//  // Check if any reads failed and exit early (to try again).
//  if (isnan(h) || isnan(t) || isnan(f))
//  {
//    Serial.println(F("Failed to read from DHT sensor!"));
//    return;
//  }
//
//  // Compute heat index in Fahrenheit (the default)
//  float hif = dht.computeHeatIndex(f, h);
//  // Compute heat index in Celsius (isFahreheit = false)
//  float hic = dht.computeHeatIndex(t, h, false);
//
//  Serial.print(F("Humidity: "));
//  Serial.print(h);
//  Serial.print(F("%  Temperature: "));
//  Serial.print(t);
//  Serial.print(F("°C "));
//  Serial.print(f);
//  Serial.print(F("°F  Heat index: "));
//  Serial.print(hic);
//  Serial.print(F("°C "));
//  Serial.print(hif);
//  Serial.println(F("°F"));
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
  server.on("/mr1", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (digitalRead(mr1Pin)) {
      digitalWrite(mr1Pin, LOW);
    }
    else {
      digitalWrite(mr1Pin, HIGH);
    }
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  server.on("/mr2", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (digitalRead(mr2Pin)) {
      digitalWrite(mr2Pin, LOW);
    }
    else {
      digitalWrite(mr2Pin, HIGH);
    }
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  server.on("/k", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (digitalRead(kPin)) {
      digitalWrite(kPin, LOW);
    }
    else {
      digitalWrite(kPin, HIGH);
    }
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  server.on("/sk", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (digitalRead(skPin)) {
      digitalWrite(skPin, LOW);
    }
    else {
      digitalWrite(skPin, HIGH);
    }
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  server.on("/a", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (digitalRead(aPin)) {
      digitalWrite(aPin, LOW);
    }
    else {
      digitalWrite(aPin, HIGH);
    }
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  server.on("/c1", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (digitalRead(c1Pin)) {
      digitalWrite(c1Pin, LOW);
    }
    else {
      digitalWrite(c1Pin, HIGH);
    }
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  server.on("/c2", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (digitalRead(c2Pin)) {
      digitalWrite(c2Pin, LOW);
    }
    else {
      digitalWrite(c2Pin, HIGH);
    }
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  server.on("/s", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (digitalRead(sPin)) {
      digitalWrite(sPin, LOW);
    }
    else {
      digitalWrite(sPin, HIGH);
    }
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  server.on("/d1", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (digitalRead(d1Pin)) {
      digitalWrite(d1Pin, LOW);
    }
    else {
      digitalWrite(d1Pin, HIGH);
    }
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  server.on("/d2", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (digitalRead(d2Pin)) {
      digitalWrite(d2Pin, LOW);
    }
    else {
      digitalWrite(d2Pin, HIGH);
    }
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  server.on("/dg", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (digitalRead(dgPin)) {
      digitalWrite(dgPin, LOW);
    }
    else {
      digitalWrite(dgPin, HIGH);
    }
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Start server
  server.begin();
  Serial.println("HTTP server started");
}
