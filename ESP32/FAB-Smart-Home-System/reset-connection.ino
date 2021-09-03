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
