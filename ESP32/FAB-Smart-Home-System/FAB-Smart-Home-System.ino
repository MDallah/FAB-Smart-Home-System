// Import required libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include "DHT.h"
#include "ESP32_MailClient.h"
#include "time.h"
#include "esp_task_wdt.h"

// Set connection mode "Wifi" or "softAP"
// Soft Access Point just to test.
// Internet connection is needed to get time and send Email.
//String conMode = "softAP";
String conMode = "Wifi";

// SoftAP SSID & Password
const char *ssid = "FAB-Smart-Home";
const char *password = "11223344556677889900";
// TODO: Add host name by Wifi access.

// Static IP address to SoftAP
IPAddress local_ip(192, 168, 1, 1);
// Gateway IP address to SoftAP
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

// WiFi SSID & Password
const char *wifi_ssid = "P48";
const char *wifi_pass = "11223344556677889900";
// TODO: Add host name by Wifi access.

const char *ntpServer = "pool.ntp.org"; // Network Time Protocol Server (NTP-Server)
const long gmtOffset_sec = 3600;        // GMT +1 = 3600
const int daylightOffset_sec = 3600;    // Difference between standard time and daylight saving time(summer time)
struct tm timeinfo;
char hour[3];
char minute[3];

// Set GPIO
#define DHTPIN 33 // must be a input digital pin
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
float temperature = 0.0;

// Simple Mail Transfer Protocol (SMTP)
// YOU MUST ENABLE less secure app option https://myaccount.google.com/lesssecureapps?pli=1
#define emailSenderAccount "testmd093@gmail.com"
#define emailSenderPassword "mdtest123"
#define smtpServer "smtp.gmail.com"
#define smtpServerPort 587
#define emailSubject "[ALERT] Server Room Temperature"
String Recipient = "testmd093@gmail.com";
String emailMessage;
bool emailSent = false;
// The Email Sending data object contains config and data to send
SMTPData smtpData;

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

  if (conMode == "softAP")
  {
    // Initialize AP (Access Point)
    WiFi.softAP(ssid, password);
    // Configure AP (Access Point)
    WiFi.softAPConfig(local_ip, gateway, subnet);
  }
  else if (conMode == "Wifi")
  {
    // Connect to Wi-Fi & print IP
    WiFi.begin(wifi_ssid, wifi_pass);
    waitForWiFiConnectOrReboot(true);
  }

  // Init and save the time in Esp32
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  // getLocalTime();
  // //disconnect WiFi as it's no longer needed
  // WiFi.disconnect(true);
  // WiFi.mode(WIFI_OFF);

  dht.begin();
  setupServer();
}

void loop()
{
  getLocalTime();
  readTemperature();
  
  strftime(hour, 3, "%H", &timeinfo);
  strftime(minute, 3, "%M", &timeinfo);
  // Serial.println(minute);
  
  if (String(minute) == "00" || String(minute) == "30")
  {
    emailSent = false;
  }
  
  if (String(hour) == "00" && String(minute) == "00")
  {
    Serial.println("Daily Reset");
    ESP.restart();
  }

  delay(60000); // 1 min = 60000 ms
}
