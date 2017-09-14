////////////////////////////////////////////////////////////////////////////////////////////////
//
//  ARDUINO BURGLAR
//
//  For more info:
//  https://github.com/CiuffoRosso/Arduino-Burglar
//
//  Licensed under GNU GPL-3.0
//
////////////////////////////////////////////////////////////////////////////////////////////////

#define SirenLength      120  // Siren timespan in seconds

#define AutoOn_StartH     21  // Hour (included) of start AutoOn
#define AutoOn_EndH        3  // Hour (excluded) of end AutoOn

// PINOUT
#define PIN_MainBtn        2
#define PIN_L1             3
#define PIN_Siren          4
#define PIN_Led_MainState  8
#define PIN_Led_Siren      9
#define PIN_Led_L1        10

////////////////////////////////////////////////////////////////////////////////////////////////

#include <Wire.h>
#include <RTClib.h>
#include <EEPROM.h>
#include <AT24C1024.h>
#include <DigitalOut.h>
#include <StopWatch.h>

DigitalOut LedMainState(PIN_Led_MainState, LOW);
DigitalOut LedL1(PIN_Led_L1, LOW);
DigitalOut LedSiren(PIN_Led_Siren, LOW);
DigitalOut Siren(PIN_Siren, LOW);

DigitalOut GNDTemp(11, LOW); // Temporary GND
DigitalOut GNDTemp2(6, LOW); // Temporary GND

bool L1State = false;

RTC_DS3231 Rtc;
DateTime now;
StopWatch swSiren;
bool mainState = false;

void setup() {
  Serial.begin(9600);  
  pinMode(PIN_L1, INPUT_PULLUP);
  pinMode(PIN_MainBtn, INPUT_PULLUP);
  setupRTC();
  readDateTimeEveryNSec(1);
  attachInterrupt(0, debounceInterrupt, RISING);
}

void loop() {
  readL1_Debouced();
  LedL1.set(L1State);
  CheckSirenStatus();

  if(readDateTimeEveryNSec(60))
    CheckAutoOn();
  
  delay(10);
}

