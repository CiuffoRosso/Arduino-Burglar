void setupRTC()
{
  Serial.println("RTC Initializing");
#ifdef AVR
  Wire.begin();
#else
  Wire1.begin(); // Shield I2C pins connect to alt I2C bus on Arduino Due
#endif
  Rtc.begin();

  if (!Rtc.begin())
  {
    Serial.println("RTC not found!");
  }
  else
  {
    Serial.println("RTC Initialized");
    
    //following line sets the RTC to the date & time this sketch was compiled
    //DateTime dtNow=DateTime(F(__DATE__), F(__TIME__));
    //dtNow = dtNow - TimeSpan(0, 1, 0, 0); // if set in DayLightSaving
    //Rtc.adjust(dtNow); 
     
    delay(500);
  }
}

void readDateTime() {
  now = CorrectDayLightSaving(Rtc.now());
  printDateTime(now);
}

void printDateTime(DateTime dt) {
  // "dd/MM/yyyy HH.mm.ss"

  Serial.print(dt.day());
  Serial.print('/');
  Serial.print(dt.month());
  Serial.print('/');
  Serial.print(dt.year());
  Serial.print(" ");
  Serial.print(dt.hour());
  Serial.print(':');
  Serial.print(dt.minute());
  Serial.print(':');
  Serial.println(dt.second());
}

StopWatch swRTC;
bool readDateTimeEveryNSec(int nSec) {
  if (!swRTC.getState() || (swRTC.getState() && swRTC.getInterval() > (nSec * 1000)))
  {
    swRTC.stop();
    readDateTime();
    swRTC.start();
    return true;
  }
  return false;
}

#define DayLightSaving_BaseAddress 1464   //AT24C32 EEPROM DayLightSaving addresses base

byte IsInDayLightSaving_LastHour = 25;
bool IsInDayLightSaving_LastValue = false;
bool IsInDayLightSaving(DateTime dt)
{
  if (dt.hour() != IsInDayLightSaving_LastHour)
  {
    DateTime dtDayLightStart (dt.year(), 3, EEPROM1024.read(DayLightSaving_BaseAddress + (dt.year() - 2000) * 2), 2, 0, 0 );
    DateTime dtDayLightEnd (dt.year(), 10, EEPROM1024.read(DayLightSaving_BaseAddress + 1 + (dt.year() - 2000) * 2), 2, 0, 0 );

    IsInDayLightSaving_LastHour = dt.hour();
    IsInDayLightSaving_LastValue = !(((dtDayLightStart - dt).totalseconds() > 0) || ((dt - dtDayLightEnd).totalseconds() > 0));
  }
  return IsInDayLightSaving_LastValue;
}

DateTime CorrectDayLightSaving(DateTime dt)
{
  if (IsInDayLightSaving(dt))
    return dt + TimeSpan(0, 1, 0, 0);
  else
    return dt;
}



