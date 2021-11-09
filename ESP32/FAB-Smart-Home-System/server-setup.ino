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

  // Route to load temperature
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(200, "text/plain", getTemperature().c_str()); });

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

  server.on(
      "/settings", HTTP_POST, [](AsyncWebServerRequest *request) {},
      NULL,
      [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
      {
        // for (size_t i = 0; i < len; i++)
        // {
        //   Serial.write(data[i]);
        // }
        received_json = (char *)data;
        Serial.println();
        Serial.println("received_json: ");
        Serial.println(received_json);

        // Create configuration file
        Serial.println(F("Saving configuration..."));
        //saveConfig(configFile, config);
        saveJsonConfig(received_json);
        
        //request->send(200);
        request->send(200, "text/plain", "The setting has been changed!\nFAB-Smart-Home-System will be rebooted!");
        ESP.restart();
      });

  // Start server
  server.begin();
  Serial.println("HTTP server started");
}
