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
    return dgState;
  }
  if (var == "TEMP")
  {
    Serial.println(temperature);
    return getTemperature();
  }
  return String();
}
