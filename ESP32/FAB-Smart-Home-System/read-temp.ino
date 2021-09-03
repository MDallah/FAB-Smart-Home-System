String readTemperature()
{
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  // Read temperature as Celsius (the default)
  temperature = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  //float temperature = dht.readTemperature(true);
  // Check if any reads failed and exit early (to try again).
  if (isnan(temperature))
  {
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  }
  else
  {
    Serial.print("Temp: ");
    Serial.println(temperature);
    // The ideal Server room temperature is between 18 °C und 24 °C
    // Dangerous operating temperatures will be anything over 30°C
    // While something like 27°C will likely also be acceptable.
    //******************************************
    // TODO if (temperature > 30 && !emailSent)
    if (temperature > 24 && !emailSent)
    //******************************************
    {
      sendEmail();
    }
    return String(temperature);
  }
}
