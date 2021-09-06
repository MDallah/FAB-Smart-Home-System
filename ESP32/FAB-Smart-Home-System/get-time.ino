void getLocalTime()
{
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
  }
  else
  {
    //Serial.println(&timeinfo, "%A, %d %B %Y %H:%M:%S");
    Serial.println(&timeinfo);
  }
}
