//Bank Map
//1 - Surface
//2 - Surface Rows
//3 - Surface Cols
//4 - JoyStick
//5 - Toggle
void LedOff(int Bank, int LED) {

  switch (Bank) {
    case 5 ://5 - Toggle
      ToggleLEDS[LED].TurnOn = 0;
      ToggleLEDS[LED].TurnOff = 1;
      ToggleLEDS[LED].OnDuration = 0;
      ToggleLEDS[LED].BrightnessOverideStep = 0;
      break;

    case 2 ://2 - SurfaceRows
      SurfaceRowsLEDS[LED].TurnOn = 0;
      SurfaceRowsLEDS[LED].TurnOff = 1;
      SurfaceRowsLEDS[LED].OnDuration = 0;
      SurfaceRowsLEDS[LED].BrightnessOverideStep = 0;
      break;

    case 3 ://3 - SurfaceCols
      SurfaceColLEDS[LED].TurnOn = 0;
      SurfaceColLEDS[LED].TurnOff = 1;
      SurfaceColLEDS[LED].OnDuration = 0;
      SurfaceColLEDS[LED].BrightnessOverideStep = 0;
      break;

    case 4 ://4 - JoyStik
      JoyLEDS[LED].TurnOn = 0;
      JoyLEDS[LED].TurnOff = 1;
      JoyLEDS[LED].OnDuration = 0;
      JoyLEDS[LED].BrightnessOverideStep = 0;
      break;


    case 1 ://Surface
      SurfaceLEDS[LED].TurnOn = 0;
      SurfaceLEDS[LED].TurnOff = 1;
      SurfaceLEDS[LED].OnDuration = 0;
      SurfaceLEDS[LED].BrightnessOverideStep = 0;
      break;

  }

}
void LedOn(int Bank, int LED, int Timed, unsigned long TimerLength) {

  switch (Bank) {
    case 5 ://5 - Toggle
      if (Timed == 0) {
        ToggleLEDS[LED].TurnOn = 1;
        ToggleLEDS[LED].OnDuration = 0;
      }
      else if (Timed != 0) {
        ToggleLEDS[LED].TurnOn = 1;
        ToggleLEDS[LED].OnDuration = TimerLength;
      }
      break;

    case 2 ://2 - SurfaceRows
      if (Timed == 0) {
        SurfaceRowsLEDS[LED].TurnOn = 1;
        SurfaceRowsLEDS[LED].OnDuration = 0;

      }
      else if (Timed != 0) {
        SurfaceRowsLEDS[LED].TurnOn = 1;
        SurfaceRowsLEDS[LED].OnDuration = TimerLength;
      }
      break;

    case 3 ://3 - SurfaceCols
      if (Timed == 0) {
        SurfaceColLEDS[LED].TurnOn = 1;
        SurfaceColLEDS[LED].OnDuration = 0;
      }
      else if (Timed != 0) {
        SurfaceColLEDS[LED].TurnOn = 1;
        SurfaceColLEDS[LED].OnDuration = TimerLength;
      }
      break;

    case 4 ://4 - JoyStik
      if (Timed == 0) {
        JoyLEDS[LED].TurnOn = 1;
        JoyLEDS[LED].OnDuration = 0;
      }
      else if (Timed != 0) {
        JoyLEDS[LED].TurnOn = 1;
        JoyLEDS[LED].OnDuration = TimerLength;
      }
      break;


    case 1 ://Surface
      if (Timed == 0) {
        SurfaceLEDS[LED].TurnOn = 1;
        SurfaceLEDS[LED].OnDuration = 0;
      }
      else if (Timed != 0) {
        SurfaceLEDS[LED].TurnOn = 1;
        SurfaceLEDS[LED].OnDuration = TimerLength;
      }
      break;

  }



}

void ProcessLEDS() {

  unsigned long LEDPcurrentMillis = millis();

  //Hijack LEDProccess for digitls display turn off
  if (DigitDisplay1TimerOff != 0 ) {
    if (millis() - DigitDisplay1Millis >=  DigitDisplay1TimerOff) {
      display.clear();

      DigitDisplay1TimerOff = 0;
    }
  }
  if (DigitDisplay2TimerOff != 0 ) {
    if (millis() - DigitDisplay2Millis >=  DigitDisplay2TimerOff) {
      display2.clear();

      DigitDisplay2TimerOff = 0;
    }
  }


  ///end Digits turn off


  //deal with the easy toggle LED
  // ON
  if (ToggleLEDS[0].TurnOn == 1) {
    ToggleLEDS[0].TurnOn = 0;
    if (ToggleLEDS[0].OnDuration == 0) {
      analogWrite(ToggleLEDS[0].Pin, ToggleLEDS[0].MaxBrightness);
    }
    else if (ToggleLEDS[0].OnDuration != 0) {
      ToggleLEDS[0].OnMillis = millis();
      analogWrite(ToggleLEDS[0].Pin, ToggleLEDS[0].MaxBrightness);
    }
    ToggleLEDS[0].On = 1;
  }

  ///deal with the Main surface
  for (int cnt = 0; cnt < 16; cnt++) {




    if (SurfaceLEDS[cnt].TurnOn == 1) {
      SurfaceLEDS[cnt].TurnOn = 0;
      if (SurfaceLEDS[cnt].OnDuration == 0) {
        io2.analogWrite(SurfaceLEDS[cnt].Pin, SurfaceLEDS[cnt].MaxBrightness);
      }
      else if (SurfaceLEDS[cnt].OnDuration != 0) {
        SurfaceLEDS[cnt].OnMillis = millis();
      }
      //deal with brightness
      if (SurfaceLEDS[cnt].BrightnessOverideStep != 0) {
        int Tempb;// =INT(E6+((255-E6)/5)*F4)
        Tempb = SurfaceLEDS[cnt].MaxBrightness + ((255 - SurfaceLEDS[cnt].MaxBrightness) / 5) * SurfaceLEDS[cnt].BrightnessOverideStep;
        io2.analogWrite(SurfaceLEDS[cnt].Pin, Tempb);
      }
      if (SurfaceLEDS[cnt].BrightnessOverideStep == 0) {
        io2.analogWrite(SurfaceLEDS[cnt].Pin, SurfaceLEDS[cnt].MaxBrightness);
      }
    }
    SurfaceLEDS[cnt].On = 1;
  }


  ///deal with the joystick LEDS
  for (int cnt = 0; cnt < 4; cnt++) {
    if (JoyLEDS[cnt].TurnOn == 1) {
      JoyLEDS[cnt].TurnOn = 0;
      if (JoyLEDS[cnt].OnDuration == 0) {
        io1.analogWrite(JoyLEDS[cnt].Pin, JoyLEDS[cnt].MaxBrightness);
      }
      else if (JoyLEDS[cnt].OnDuration != 0) {
        JoyLEDS[cnt].OnMillis = millis();
        io1.analogWrite(JoyLEDS[cnt].Pin, JoyLEDS[cnt].MaxBrightness);
      }
      JoyLEDS[cnt].On = 1;
    }
  }

  ///deal with the Surface Rows
  for (int cnt = 0; cnt < 4; cnt++) {

    if (SurfaceRowsLEDS[cnt].TurnOn == 1) {
      SurfaceRowsLEDS[cnt].TurnOn = 0;
      if (SurfaceRowsLEDS[cnt].OnDuration == 0) {
        analogWrite(SurfaceRowsLEDS[cnt].Pin, SurfaceRowsLEDS[cnt].MaxBrightness);
      }
      else if (SurfaceRowsLEDS[cnt].OnDuration != 0) {
        SurfaceRowsLEDS[cnt].OnDuration;
        SurfaceRowsLEDS[cnt].OnMillis = millis();


        analogWrite(SurfaceRowsLEDS[cnt].Pin, SurfaceRowsLEDS[cnt].MaxBrightness);
      }
      SurfaceRowsLEDS[cnt].On = 1;
    }
  }

  ///deal with the Surface Cols
  for (int cnt = 0; cnt < 4; cnt++) {

    if (SurfaceColLEDS[cnt].TurnOn == 1) {
      SurfaceColLEDS[cnt].TurnOn = 0;
      if (SurfaceColLEDS[cnt].OnDuration == 0) {
        analogWrite(SurfaceColLEDS[cnt].Pin, SurfaceColLEDS[cnt].MaxBrightness);
      }
      else if (SurfaceColLEDS[cnt].OnDuration != 0) {
        SurfaceColLEDS[cnt].OnDuration;
        SurfaceColLEDS[cnt].OnMillis = millis();


        analogWrite(SurfaceColLEDS[cnt].Pin, SurfaceColLEDS[cnt].MaxBrightness);
      }
      SurfaceColLEDS[cnt].On = 1;
    }
  }










  // ------------OFFs

  // toggle
  if (ToggleLEDS[0].TurnOff == 1) {
    ToggleLEDS[0].TurnOn = 0;
    ToggleLEDS[0].TurnOff = 0;
    ToggleLEDS[0].OnDuration = 0;
    ToggleLEDS[0].BrightnessOverideStep = 0;
    analogWrite(ToggleLEDS[0].Pin, 0);
  }

  if (ToggleLEDS[0].On == 1 && ToggleLEDS[0].OnDuration != 0) {
    if (millis() - ToggleLEDS[0].OnMillis >=  ToggleLEDS[0].OnDuration) {

      ToggleLEDS[0].TurnOn = 0;
      ToggleLEDS[0].TurnOff = 0;
      ToggleLEDS[0].OnDuration = 0;
      ToggleLEDS[0].BrightnessOverideStep = 0;
      analogWrite(ToggleLEDS[0].Pin, 0);
    }
  }
  //Surface off
  for (int cnt = 0; cnt < 16; cnt++) {

    if (SurfaceLEDS[cnt].TurnOff == 1) {
      SurfaceLEDS[cnt].TurnOn = 0;
      SurfaceLEDS[cnt].TurnOff = 0;
      SurfaceLEDS[cnt].OnDuration = 0;
      SurfaceLEDS[cnt].BrightnessOverideStep = 0;
      io2.analogWrite(SurfaceLEDS[cnt].Pin, 255);
    }
    if (SurfaceLEDS[cnt].On == 1 && SurfaceLEDS[cnt].OnDuration != 0) {
      if (millis() - SurfaceLEDS[cnt].OnMillis >=  SurfaceLEDS[cnt].OnDuration) {
        SurfaceLEDS[cnt].TurnOn = 0;
        SurfaceLEDS[cnt].TurnOff = 0;
        SurfaceLEDS[cnt].OnDuration = 0;
        SurfaceLEDS[cnt].BrightnessOverideStep = 0;
        io2.analogWrite(SurfaceLEDS[cnt].Pin, 255);
      }
    }
  }

  //Joystick off
  for (int cnt = 0; cnt < 4; cnt++) {

    if (JoyLEDS[cnt].TurnOff == 1) {
      JoyLEDS[cnt].TurnOn = 0;
      JoyLEDS[cnt].TurnOff = 0;
      JoyLEDS[cnt].OnDuration = 0;
      io1.analogWrite(JoyLEDS[cnt].Pin, 255);
    }
    if (JoyLEDS[cnt].On == 1 && JoyLEDS[cnt].OnDuration != 0) {
      if (millis() - JoyLEDS[cnt].OnMillis >=  JoyLEDS[cnt].OnDuration) {
        JoyLEDS[cnt].TurnOn = 0;
        JoyLEDS[cnt].TurnOff = 0;
        JoyLEDS[cnt].OnDuration = 0;
        io1.analogWrite(JoyLEDS[cnt].Pin, 255);
      }
    }
  }

  //Surface rows off
  for (int cnt = 0; cnt < 4; cnt++) {

    if (SurfaceRowsLEDS[cnt].TurnOff == 1) {
      SurfaceRowsLEDS[cnt].TurnOn = 0;
      SurfaceRowsLEDS[cnt].TurnOff = 0;
      SurfaceRowsLEDS[cnt].OnDuration = 0;
      analogWrite(SurfaceRowsLEDS[cnt].Pin, 0);
    }
    if (SurfaceRowsLEDS[cnt].On == 1 && SurfaceRowsLEDS[cnt].OnDuration != 0) {
      if (millis() - SurfaceRowsLEDS[cnt].OnMillis >=  SurfaceRowsLEDS[cnt].OnDuration) {
        SurfaceRowsLEDS[cnt].TurnOn = 0;
        SurfaceRowsLEDS[cnt].TurnOff = 0;
        SurfaceRowsLEDS[cnt].OnDuration = 0;
        analogWrite(SurfaceRowsLEDS[cnt].Pin, 0);
      }
    }
  }
  //Surface Cols off
  for (int cnt = 0; cnt < 4; cnt++) {

    if (SurfaceColLEDS[cnt].TurnOff == 1) {
      SurfaceColLEDS[cnt].TurnOn = 0;
      SurfaceColLEDS[cnt].TurnOff = 0;
      SurfaceColLEDS[cnt].OnDuration = 0;
      analogWrite(SurfaceColLEDS[cnt].Pin, 0);
    }
    if (SurfaceColLEDS[cnt].On == 1 && SurfaceColLEDS[cnt].OnDuration != 0) {
      if (millis() - SurfaceColLEDS[cnt].OnMillis >=  SurfaceColLEDS[cnt].OnDuration) {
        SurfaceColLEDS[cnt].TurnOn = 0;
        SurfaceColLEDS[cnt].TurnOff = 0;
        SurfaceColLEDS[cnt].OnDuration = 0;
        analogWrite(SurfaceColLEDS[cnt].Pin, 0);
      }
    }
  }

  ///Deal with and LCD Timesout in LEDLoop
  if (LCDTimeOutToMenu != 0) {
    if (millis() - LCDTimeOutToMenuMillies >=  LCDTimeOutToMenu) {
      LCDTimeOutToMenu = 0;
      LCDTimeOutToMenuMillies = 0;
      ReturnMenu();
    }
  }


  //end processLEDS

}
