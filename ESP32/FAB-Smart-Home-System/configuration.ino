// Loads the configuration from a file
void loadConfig(Config &config)
{
  // Open file for reading
  File file = SPIFFS.open(configFile);
  if (!file)
  {
    Serial.println("Failed to open file for reading");
    return;
  }

  printConfFile();

  // Allocate a temporary JsonDocument
  // Don't forget to change the capacity to match your requirements.
  // Use arduinojson.org/v6/assistant to compute the capacity.
  StaticJsonDocument<512> doc;
  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, file);

  if (error)
  {
    Serial.println(F("Failed to parse data"));
  }
  else
  {
    // Copy values from the JsonDocument to the Config
    strlcpy(config.WiFi_ssid,          // <- destination
            doc["wifi_ssid"],          // <- source
            sizeof(config.WiFi_ssid)); // <- destination's capacity
    strlcpy(config.WiFi_password,
            doc["wifi_password"],
            sizeof(config.WiFi_password));
    config.WiFi_Mode = doc["wifi_mode"];
    strlcpy(config.Email_sender,
            doc["email_sender"],
            sizeof(config.Email_sender));
    strlcpy(config.Email_sender_password,
            doc["email_sender_password"],
            sizeof(config.Email_sender_password));
    strlcpy(config.Email_recipient,
            doc["email_recipient"],
            sizeof(config.Email_recipient));
    config.Time_to_send_email = doc["time_to_send_email"];
    strlcpy(config.Time_server,
            doc["time_server"],
            sizeof(config.Time_server));
    config.GMT_offset_sec = doc["gmt_offset_sec"];
    config.Daylight_offset_sec = doc["daylight_offset_sec"];
    Serial.println("configuration has been loaded");
  }
  // Close the file
  file.close();
}

void ParseJson(String data, Config &config)
{
  // Allocate a temporary JsonDocument
  // Don't forget to change the capacity to match your requirements.
  // Use arduinojson.org/v6/assistant to compute the capacity.
  StaticJsonDocument<512> doc;
  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, data);

  if (error)
  {
    Serial.println(F("Failed to parse data"));
  }
  else
  {
    // Copy values from the JsonDocument to the Config
    strlcpy(config.WiFi_ssid,          // <- destination
            doc["wifi_ssid"],          // <- source
            sizeof(config.WiFi_ssid)); // <- destination's capacity
    strlcpy(config.WiFi_password,
            doc["wifi_password"],
            sizeof(config.WiFi_password));
    config.WiFi_Mode = doc["wifi_mode"];
    strlcpy(config.Email_sender,
            doc["email_sender"],
            sizeof(config.Email_sender));
    strlcpy(config.Email_sender_password,
            doc["email_sender_password"],
            sizeof(config.Email_sender_password));
    strlcpy(config.Email_recipient,
            doc["email_recipient"],
            sizeof(config.Email_recipient));
    config.Time_to_send_email = doc["time_to_send_email"];
    strlcpy(config.Time_server,
            doc["time_server"],
            sizeof(config.Time_server));
    config.GMT_offset_sec = doc["gmt_offset_sec"];
    config.Daylight_offset_sec = doc["daylight_offset_sec"];
    Serial.println("configuration has been parsed");
  }
}

void saveJsonConfig(String json_data)
{
  ParseJson(json_data, temporary_config);
  saveConfig(temporary_config);
  printConfFile();
  //ParseJson(json_data.c_str(), temporary_config);
  // Delete existing file, otherwise the configuration is appended to the file
  //SPIFFS.remove(configFile);

  // // Open file for writing
  // File file = SPIFFS.open(configFile, FILE_WRITE);

  // if (!file)
  // {
  //   Serial.println("There was an error opening the file for writing");
  //   return;
  // }
  // if (file.print(json_data))
  // {
  //   Serial.println("File was written");
  // }
  // else
  // {
  //   Serial.println("File write failed");
  // }

  // file.close();
}

// Saves the configuration to a file
void saveConfig(const Config &t_config)
{
  // Delete existing file, otherwise the configuration is appended to the file
  //SPIFFS.remove(configFile);

  // Open file for writing
  File file = SPIFFS.open(configFile, FILE_WRITE);
  if (!file)
  {
    Serial.println("Failed to open file for reading");
    return;
  }

  // Allocate a temporary JsonDocument
  // Don't forget to change the capacity to match your requirements.
  // Use arduinojson.org/assistant to compute the capacity.
  StaticJsonDocument<256> doc;

  // Set the values in the document
  if (String(t_config.WiFi_ssid) != "")
    doc["wifi_ssid"] = t_config.WiFi_ssid;
  else
    doc["wifi_ssid"] = config.WiFi_ssid;

  if (String(t_config.WiFi_password) != "")
    doc["wifi_password"] = t_config.WiFi_password;
  else
    doc["wifi_password"] = config.WiFi_password;

  doc["wifi_mode"] = t_config.WiFi_Mode;

  if (String(t_config.Email_sender) != "")
    doc["email_sender"] = t_config.Email_sender;
  else
    doc["email_sender"] = config.Email_sender;

  if (String(t_config.Email_sender_password) != "")
    doc["email_sender_password"] = t_config.Email_sender_password;
  else
    doc["email_sender_password"] = config.Email_sender_password;

  if (String(t_config.Email_recipient) != "")
    doc["email_recipient"] = t_config.Email_recipient;
  else
    doc["email_recipient"] = config.Email_recipient;

  // //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
  // Serial.print("t_config.Time_to_send_email: ");
  // Serial.println(t_config.Time_to_send_email);
  // Serial.print("config.Time_to_send_email: ");
  // Serial.println(config.Time_to_send_email);

  // if (t_config.Time_to_send_email != 0)
  //   Serial.println("TRUE");
  // else
  //   Serial.println("FALSE");

  // //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
  if (t_config.Time_to_send_email != 0)
    doc["time_to_send_email"] = t_config.Time_to_send_email;
  else
    doc["time_to_send_email"] = config.Time_to_send_email;
  if (t_config.GMT_offset_sec != 0)
    doc["gmt_offset_sec"] = t_config.GMT_offset_sec;
  else
    doc["gmt_offset_sec"] = config.GMT_offset_sec;
  if (String(t_config.Time_server) != "")
    doc["time_server"] = t_config.Time_server;
  else
    doc["time_server"] = config.Time_server;
  if (t_config.Daylight_offset_sec != 0)
    doc["daylight_offset_sec"] = t_config.Daylight_offset_sec;
  else
    doc["daylight_offset_sec"] = config.Daylight_offset_sec;

  // Serialize JSON to file
  if (serializeJson(doc, file) == 0)
  {
    Serial.println(F("Failed to write to file"));
  }
  // Close the file
  file.close();
}

// Prints the content of a file to the Serial
void printConfFile()
{

  File file = SPIFFS.open(configFile);
  if (!file)
  {
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.println("File Content:");
  while (file.available())
  {
    Serial.write(file.read());
  }
  Serial.println("");
  file.close();
}
