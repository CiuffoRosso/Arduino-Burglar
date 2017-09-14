// Read MainBtn

long debouncing_time = 15; //Debouncing Time in Milliseconds
volatile unsigned long last_micros;

void debounceInterrupt() {
  if((long)(micros() - last_micros) >= debouncing_time * 1000) {
    MainBtn_Click();
    last_micros = micros();
  }
}

// Read Line L1

char nCheckL1State = 0;
const char nCheckHigh = 10;
const char nCheckLow = -10;
bool L1StatePrev = false;

void readL1_Debouced()
{
  nCheckL1State += digitalRead(PIN_L1) ? 1 : -1;
  if (nCheckL1State > nCheckHigh) nCheckL1State = nCheckHigh;
  if (nCheckL1State < nCheckLow) nCheckL1State = nCheckLow;
  L1State = nCheckL1State > 0;

  if (L1StatePrev == 0 && L1State == 1) L1_OpenToClose();
  if (L1StatePrev == 1 && L1State == 0) L1_CloseToOpen();
  
  L1StatePrev = L1State;
}
