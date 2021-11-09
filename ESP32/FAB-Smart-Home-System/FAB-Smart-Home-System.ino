/*
  Rui Santos
  Complete project details at https://randomnerdtutorials.com/projects-esp32/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

// Import required libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include "DHT.h"
#include "ESP32_MailClient.h"
#include "time.h"
#include "esp_task_wdt.h"
#include "ArduinoJson.h"

// Add configuration structure.
struct Config
{
  char WiFi_ssid[64];
  char WiFi_password[64];
  char Email_sender[64];
  char Email_sender_password[64];
  char Email_recipient[64];
  int Time_to_send_email;
  int GMT_offset_sec;
  int Daylight_offset_sec;
};

String received_json;
const char *configFile = "/config.json";
Config config;
Config temporary_config;

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
// const char *wifi_ssid = "P48";
// const char *wifi_pass = "11223344556677889900";
const char *wifi_ssid = config.WiFi_ssid;
const char *wifi_pass = config.WiFi_password;
// TODO: Add host name by Wifi access.

const char *ntpServer = "pool.ntp.org"; // Network Time Protocol Server (NTP-Server)
const long gmtOffset_sec = config.GMT_offset_sec ;        //const long gmtOffset_sec = 3600;        // GMT +1 = 3600
const int daylightOffset_sec = config.Daylight_offset_sec ;    //const int daylightOffset_sec = 3600;    // Difference between standard time and daylight saving time(summer time)
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
#define emailSenderAccount config.Email_sender  // #define emailSenderAccount "testmd093@gmail.com"
#define emailSenderPassword config.Email_sender_password  // #define emailSenderPassword "mdtest123"
#define Recipient config.Email_recipient  // #define Recipient "testmd093@gmail.com"
#define time_to_send_mail config.Time_to_send_email  // #define time_to_send_mail 30
#define smtpServer "smtp.gmail.com"
#define smtpServerPort 587
//#define smtpServerPort 465
#define emailSubject "[ALERT] Server Room Temperature"
char emailMessage[2048];
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

  // Should load default config if run for the first time
  Serial.println(F("Loading configuration..."));
  loadConfig(config);

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
  if (WiFi.status() != WL_CONNECTED)
  {
    waitForWiFiConnectOrReboot(true);
  }
  else
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
}
