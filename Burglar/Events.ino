void MainBtn_Click()
{
  mainState = !mainState;
  if (mainState)
    MainState_On();
  else
    MainState_Off();
}

void MainState_On()
{
  LedSiren.off();
  LedMainState.on();

  Serial.println("Burglar activated");

  if (!L1State)
    L1_CloseToOpen();
}

void MainState_Off()
{
  LedMainState.off();

  if (InAutoOn)
    OffActionInAutoOn = true;

  if (swSiren.getState())
    swSiren.stop();

  Serial.println("Burglar deactivated");
}

void L1_OpenToClose()
{
  Serial.println("Line closed");
}

void L1_CloseToOpen()
{
  Serial.println("Line opened");
  if (mainState)
    if (!swSiren.getState())
      swSiren.start();
}
