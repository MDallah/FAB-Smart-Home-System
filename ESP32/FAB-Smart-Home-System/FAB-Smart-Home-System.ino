// Import required libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include "DHT.h"

// WiFi SSID & Password
const char *ssid = "FAB-Smart-Home";
const char *password = "11223344556677889900";

// TODO: Add host name by Wifi access.

// Static IP address to SoftAP
IPAddress local_ip(192, 168, 1, 1);
// Gateway IP address to SoftAP
IPAddress gateway(192, 168, 1, 1);

IPAddress subnet(255, 255, 255, 0);

// Set GPIO
#define DHTPIN 33 // musst be a input digital pin
#define MR1PIN 25
#define MR2PIN 32
#define KPIN 26
#define SKPIN 26
#define APIN 26
#define C1PIN 26
#define C2PIN 26
#define SPIN 26
#define D1PIN 26
#define D2PIN 26
#define DGPIN 26

// Uncomment whatever type you're using!
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT22 // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

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
String processor(const String &var)
{
  Serial.print(var + " -> ");
  if (var == "MR1")
  {
    if (digitalRead(MR1PIN))
    {
      mr1State = "1";
    }
    else
    {
      mr1State = "0";
    }
    Serial.println(mr1State);
    return mr1State;
  }
  if (var == "MR2")
  {
    if (digitalRead(MR2PIN))
    {
      mr2State = "1";
    }
    else
    {
      mr2State = "0";
    }
    Serial.println(mr2State);
    Serial.println("----------------------");
    return mr2State;
  }
  if (var == "K")
  {
    if (digitalRead(KPIN))
    {
      kState = "1";
    }
    else
    {
      kState = "0";
    }
    Serial.println(kState);
    Serial.println("----------------------");
    return kState;
  }
  if (var == "SK")
  {
    if (digitalRead(SKPIN))
    {
      skState = "1";
    }
    else
    {
      skState = "0";
    }
    Serial.println(skState);
    Serial.println("----------------------");
    return skState;
  }
  if (var == "A")
  {
    if (digitalRead(APIN))
    {
      aState = "1";
    }
    else
    {
      aState = "0";
    }
    Serial.println(aState);
    Serial.println("----------------------");
    return aState;
  }
  if (var == "C1")
  {
    if (digitalRead(C1PIN))
    {
      c1State = "1";
    }
    else
    {
      c1State = "0";
    }
    Serial.println(c1State);
    Serial.println("----------------------");
    return c1State;
  }
  if (var == "C2")
  {
    if (digitalRead(C2PIN))
    {
      c2State = "1";
    }
    else
    {
      c2State = "0";
    }
    Serial.println(c2State);
    Serial.println("----------------------");
    return c2State;
  }
  if (var == "S")
  {
    if (digitalRead(SPIN))
    {
      sState = "1";
    }
    else
    {
      sState = "0";
    }
    Serial.println(sState);
    Serial.println("----------------------");
    return sState;
  }
  if (var == "D1")
  {
    if (digitalRead(D1PIN))
    {
      d1State = "1";
    }
    else
    {
      d1State = "0";
    }
    Serial.println(d1State);
    Serial.println("----------------------");
    return d1State;
  }
  if (var == "D2")
  {
    if (digitalRead(D2PIN))
    {
      d2State = "1";
    }
    else
    {
      d2State = "0";
    }
    Serial.println(d2State);
    Serial.println("----------------------");
    return d2State;
  }
  if (var == "DG")
  {
    if (digitalRead(DGPIN))
    {
      dgState = "1";
    }
    else
    {
      dgState = "0";
    }
    Serial.println(dgState);
    Serial.println("----------------------");
    return dgState;
  }
  return String();
}

void setup()
{
  // Serial port for debugging purposes
  Serial.begin(115200);
  delay(100);

  pinMode(MR1PIN, OUTPUT);
  pinMode(MR2PIN, OUTPUT);
  pinMode(KPIN, OUTPUT);
  pinMode(SKPIN, OUTPUT);
  pinMode(APIN, OUTPUT);
  pinMode(C1PIN, OUTPUT);
  pinMode(C2PIN, OUTPUT);
  pinMode(SPIN, OUTPUT);
  pinMode(D1PIN, OUTPUT);
  pinMode(D2PIN, OUTPUT);
  pinMode(DGPIN, OUTPUT);

  // Initialize SPIFFS
  if (!SPIFFS.begin(true))
  {
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

void loop()
{
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
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/index.html", String(), false, processor); });

  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/style.css", "text/css"); });

  // Route to load FABMationLogo.png file
  server.on("/FABMationLogo.png", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/FABMationLogo.png", "image/png"); });

  // Route to load SmartHome.png file
  server.on("/SmartHome.png", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/SmartHome.png", "image/png"); });

  // Route to change GPIO status
  server.on("/mr1", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              if (digitalRead(MR1PIN))
              {
                digitalWrite(MR1PIN, LOW);
              }
              else
              {
                digitalWrite(MR1PIN, HIGH);
              }
              request->send(SPIFFS, "/index.html", String(), false, processor);
            });

  server.on("/mr2", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              if (digitalRead(MR2PIN))
              {
                digitalWrite(MR2PIN, LOW);
              }
              else
              {
                digitalWrite(MR2PIN, HIGH);
              }
              request->send(SPIFFS, "/index.html", String(), false, processor);
            });

  server.on("/k", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              if (digitalRead(KPIN))
              {
                digitalWrite(KPIN, LOW);
              }
              else
              {
                digitalWrite(KPIN, HIGH);
              }
              request->send(SPIFFS, "/index.html", String(), false, processor);
            });

  server.on("/sk", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              if (digitalRead(SKPIN))
              {
                digitalWrite(SKPIN, LOW);
              }
              else
              {
                digitalWrite(SKPIN, HIGH);
              }
              request->send(SPIFFS, "/index.html", String(), false, processor);
            });

  server.on("/a", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              if (digitalRead(APIN))
              {
                digitalWrite(APIN, LOW);
              }
              else
              {
                digitalWrite(APIN, HIGH);
              }
              request->send(SPIFFS, "/index.html", String(), false, processor);
            });

  server.on("/c1", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              if (digitalRead(C1PIN))
              {
                digitalWrite(C1PIN, LOW);
              }
              else
              {
                digitalWrite(C1PIN, HIGH);
              }
              request->send(SPIFFS, "/index.html", String(), false, processor);
            });

  server.on("/c2", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              if (digitalRead(C2PIN))
              {
                digitalWrite(C2PIN, LOW);
              }
              else
              {
                digitalWrite(C2PIN, HIGH);
              }
              request->send(SPIFFS, "/index.html", String(), false, processor);
            });

  server.on("/s", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              if (digitalRead(SPIN))
              {
                digitalWrite(SPIN, LOW);
              }
              else
              {
                digitalWrite(SPIN, HIGH);
              }
              request->send(SPIFFS, "/index.html", String(), false, processor);
            });

  server.on("/d1", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              if (digitalRead(D1PIN))
              {
                digitalWrite(D1PIN, LOW);
              }
              else
              {
                digitalWrite(D1PIN, HIGH);
              }
              request->send(SPIFFS, "/index.html", String(), false, processor);
            });

  server.on("/d2", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              if (digitalRead(D2PIN))
              {
                digitalWrite(D2PIN, LOW);
              }
              else
              {
                digitalWrite(D2PIN, HIGH);
              }
              request->send(SPIFFS, "/index.html", String(), false, processor);
            });

  server.on("/dg", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              if (digitalRead(DGPIN))
              {
                digitalWrite(DGPIN, LOW);
              }
              else
              {
                digitalWrite(DGPIN, HIGH);
              }
              request->send(SPIFFS, "/index.html", String(), false, processor);
            });

  // Start server
  server.begin();
  Serial.println("HTTP server started");
}
