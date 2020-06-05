void RocketFlashyFlash() {
  //Flash the surface buttons randomonly while on

  if (RocketMode == 1 || RocketMode == 2 ) {
    if (millis() - RocketFlashMillies > 100) {
      RocketrandNumber = random(15);
      int Radnomtimer = random(750);
      RocketFlashMillies = millis();
      SurfaceLEDS[RocketrandNumber + 1].TurnOn = 1;
      SurfaceLEDS[RocketrandNumber + 1].OnDuration = Radnomtimer;

    }
  }


  if (RocketMode == 4 ) {
    if (millis() - RocketFlashMillies > 300) {
      RocketFlashMillies = millis();
      //RocketFlashTakeoffStep
      
      switch (RocketFlashTakeoffStep) {
        case 1:
          //RocketFlashTakeoffStep = 1;
          LedOff(1, 0);
          LedOff(1, 1);
          LedOff(1, 2);
          LedOff(1, 3);
          LedOff(1, 4);
          LedOff(1, 5);
          LedOff(1, 6);
          LedOff(1, 7);
          LedOff(1, 8);
          LedOff(1, 9);
          LedOff(1, 10);
          LedOff(1, 11);      

          
          SurfaceLEDS[12].TurnOn = 1; SurfaceLEDS[12].OnDuration = 0;
          SurfaceLEDS[13].TurnOn = 1; SurfaceLEDS[13].OnDuration = 0;
          SurfaceLEDS[14].TurnOn = 1; SurfaceLEDS[14].OnDuration = 0;
          SurfaceLEDS[15].TurnOn = 1; SurfaceLEDS[15].OnDuration = 0;
          ProcessLEDS();
          break;

        case 2:
         // RocketFlashTakeoffStep = 2;
          LedOff(1, 0);
          LedOff(1, 1);
          LedOff(1, 2);
          LedOff(1, 3);
          LedOff(1, 4);
          LedOff(1, 5);
          LedOff(1, 6);
          LedOff(1, 7);
          LedOff(1, 12);
          LedOff(1, 13);
          LedOff(1, 14);
          LedOff(1, 15);

          SurfaceLEDS[8].TurnOn = 1; SurfaceLEDS[8].OnDuration = 0;
          SurfaceLEDS[9].TurnOn = 1; SurfaceLEDS[9].OnDuration = 0;
          SurfaceLEDS[10].TurnOn = 1; SurfaceLEDS[10].OnDuration = 0;
          SurfaceLEDS[11].TurnOn = 1; SurfaceLEDS[11].OnDuration = 0;
                
           ProcessLEDS();
          break;

        case 3:
          //RocketFlashTakeoffStep = 3;
          LedOff(1, 0);
          LedOff(1, 1);
          LedOff(1, 2);
          LedOff(1, 3);
          LedOff(1, 12);
          LedOff(1, 13);
          LedOff(1, 14);
          LedOff(1, 15);
          LedOff(1, 8);
          LedOff(1, 9);
          LedOff(1, 10);
          LedOff(1, 11);
          
          SurfaceLEDS[4].TurnOn = 1; SurfaceLEDS[4].OnDuration = 0;
          SurfaceLEDS[5].TurnOn = 1; SurfaceLEDS[5].OnDuration = 0;
          SurfaceLEDS[6].TurnOn = 1; SurfaceLEDS[6].OnDuration = 0;
          SurfaceLEDS[7].TurnOn = 1; SurfaceLEDS[7].OnDuration = 0;
           ProcessLEDS();
          break;

        case 4:
          //RocketFlashTakeoffStep = 0;

          LedOff(1, 12);
          LedOff(1, 13);
          LedOff(1, 14);
          LedOff(1, 15);
          LedOff(1, 4);
          LedOff(1, 5);
          LedOff(1, 6);
          LedOff(1, 7);
          LedOff(1, 8);
          LedOff(1, 9);
          LedOff(1, 10);
          LedOff(1, 11);
          
          SurfaceLEDS[0].TurnOn = 1; SurfaceLEDS[0].OnDuration = 0;
          SurfaceLEDS[1].TurnOn = 1; SurfaceLEDS[1].OnDuration = 0;
          SurfaceLEDS[2].TurnOn = 1; SurfaceLEDS[2].OnDuration = 0;
          SurfaceLEDS[3].TurnOn = 1; SurfaceLEDS[3].OnDuration = 0;
             ProcessLEDS();
          break;

      }
    }

    RocketFlashTakeoffStep = RocketFlashTakeoffStep +1;

    if (RocketFlashTakeoffStep >= 5) {RocketFlashTakeoffStep =1;}
    Serial.println( RocketFlashTakeoffStep);
    
  }
  



}

void RocketTakeOffFlashy(int countdown) {
  switch (countdown) {
    case 10:
      SurfaceLEDS[1].TurnOn = 1; SurfaceLEDS[1].OnDuration = 0;
      SurfaceLEDS[2].TurnOn = 1; SurfaceLEDS[2].OnDuration = 0;
      SurfaceLEDS[5].TurnOn = 1; SurfaceLEDS[5].OnDuration = 0;
      SurfaceLEDS[6].TurnOn = 1; SurfaceLEDS[6].OnDuration = 0;
      SurfaceLEDS[9].TurnOn = 1; SurfaceLEDS[9].OnDuration = 0;
      SurfaceLEDS[10].TurnOn = 1; SurfaceLEDS[10].OnDuration = 0;
      SurfaceLEDS[13].TurnOn = 1; SurfaceLEDS[13].OnDuration = 0;
      SurfaceLEDS[14].TurnOn = 1; SurfaceLEDS[14].OnDuration = 0;
      SurfaceLEDS[12].TurnOn = 1; SurfaceLEDS[12].OnDuration = 0;
      SurfaceLEDS[15].TurnOn = 1; SurfaceLEDS[15].OnDuration = 0;
      ProcessLEDS();
      break;
    case 9:
      LedOff(1, 1);

      ProcessLEDS();
      break;
    case 8:
      LedOff(1, 2);

      ProcessLEDS();
      break;
    case 7:
      LedOff(1, 5);
      SurfaceLEDS[6].TurnOff = 0;
      ProcessLEDS();
      break;
    case 6:
      LedOff(1, 6);

      ProcessLEDS();
      break;
    case 5:
      LedOff(1, 9);

      ProcessLEDS();
      break;
    case 4:
      LedOff(1, 10);

      ProcessLEDS();
      break;
    case 3:
      LedOff(1, 12);

      ProcessLEDS();
      break;
    case 2:
      LedOff(1, 13);

      ProcessLEDS();
      break;
    case 1:
      LedOff(1, 14);

      ProcessLEDS();
      break;
    case 0:
      LedOff(1, 15);

      ProcessLEDS();
      break;
  }
}
