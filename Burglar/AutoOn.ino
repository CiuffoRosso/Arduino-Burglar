bool OffActionInAutoOn = false;
bool InAutoOn = false;

void CheckAutoOn()
{
  bool autoOn = false;
  if (AutoOn_StartH > AutoOn_EndH && (now.hour() >= AutoOn_StartH || now.hour() < AutoOn_EndH)) autoOn = true;
  else if (AutoOn_StartH < AutoOn_EndH && (now.hour() >= AutoOn_StartH && now.hour() < AutoOn_EndH)) autoOn = true;
  InAutoOn = autoOn;

  if (!InAutoOn)
    OffActionInAutoOn = false;

  if (!mainState && InAutoOn && !OffActionInAutoOn)
  {
      delay(1000);
      mainState = true;
      MainState_On();
  }
}
