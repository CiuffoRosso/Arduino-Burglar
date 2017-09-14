void CheckSirenStatus()
{
  if (swSiren.getState())
  {
    if (!Siren.get())
    {
      Serial.println("Siren ON");
      Siren.on();
      LedSiren.on();
    }
    else
    {
      if (swSiren.getInterval() > (SirenLength * 1000))
      {
        swSiren.stop();
        Siren.off();
        Serial.println("Siren OFF");
      }
    }
  }
}
