void ReturnMenu() {
  switch ( CurrentMenuControl ) {
    case 0 :
      lcd.clear();
      lcd.print("     Explore    ");
      break;
    case 1 :
      lcd.clear();
      lcd.print("    Surprise    ");
      break;
    case 2 :
      lcd.clear();
      lcd.print("   Make Music   ");
      break;
    case 3 :
      lcd.clear();
      lcd.print("  Simple Simon  ");
      break;
    case 4 :
      lcd.clear();
      lcd.print("  Mini  PacMan  ");
      break;
    case 5 :
      lcd.clear();
      lcd.print("  Follow  me  ");
      CountdownPlaying = 1;
      FM_GameON = 0;
      break;
    case 6 :
      lcd.clear();
      lcd.print("   The Wiggles  ");
      break;
    case 7 :
      lcd.clear();
      lcd.print("     Rocket     ");
       RocketMode = 0;
       RocketButtonFlash = 0;
       RocketCurrentStep =0;
      break;
    default:
      lcd.clear();
      lcd.print("      Empty     ");
      break;
  }

}


void ExitTimeout() {

  TIMEOUTISON = 0;
  MasterTIMEOUT = millis();

  lcd.setBacklight(true);
}

void CheckTimeout() {
  if ( Easter1On != 1 && AdminMode != 1 ) {
    if (millis() - MasterTIMEOUT >=  TIMEOUTTIME) {
      //screen saver
      ResetSurface();
      DigitDisplay1TimerOff = 0;
      DigitDisplay2TimerOff = 0;
      wTrig.stopAllTracks();
      wTrig.samplerateOffset(0);
      lcd.clear();
      lcd.setBacklight(false);
      display.clear();
      display2.clear();
      RocketButtonFlash = 0;
      TIMEOUTISON = 1;
    }
  }
}
void ResetSurface() {

  CurrentFindButton = 16; //set suprise trigger to start game

  wTrig.stopAllTracks();

  display.clear();
  display2.clear();

  //turn off all LEDS
  //surface
  for ( int i = 0; i <= 15; i++) {
    SurfaceLEDS[i].TurnOn = 0;
    SurfaceLEDS[i].OnDuration = 0;
    SurfaceLEDS[i].TurnOff = 1;
  }
  //surface rows
  SurfaceRowsLEDS[0].OnDuration = 0;
  SurfaceRowsLEDS[1].OnDuration = 0;
  SurfaceRowsLEDS[2].OnDuration = 0;
  SurfaceRowsLEDS[3].OnDuration = 0;
  SurfaceRowsLEDS[0].TurnOn = 0;
  SurfaceRowsLEDS[1].TurnOn = 0;
  SurfaceRowsLEDS[2].TurnOn = 0;
  SurfaceRowsLEDS[3].TurnOn = 0;
  SurfaceRowsLEDS[0].TurnOff = 1;
  SurfaceRowsLEDS[1].TurnOff = 1;
  SurfaceRowsLEDS[2].TurnOff = 1;
  SurfaceRowsLEDS[3].TurnOff = 1;
  //surface cols
  SurfaceColLEDS[0].OnDuration = 0;
  SurfaceColLEDS[1].OnDuration = 0;
  SurfaceColLEDS[2].OnDuration = 0;
  SurfaceColLEDS[3].OnDuration = 0;
  SurfaceColLEDS[0].TurnOn = 0;
  SurfaceColLEDS[1].TurnOn = 0;
  SurfaceColLEDS[2].TurnOn = 0;
  SurfaceColLEDS[3].TurnOn = 0;
  SurfaceColLEDS[0].TurnOff = 1;
  SurfaceColLEDS[1].TurnOff = 1;
  SurfaceColLEDS[2].TurnOff = 1;
  SurfaceColLEDS[3].TurnOff = 1;
  //joy
  JoyLEDS[0].OnDuration = 0;
  JoyLEDS[1].OnDuration = 0;
  JoyLEDS[2].OnDuration = 0;
  JoyLEDS[3].OnDuration = 0;
  JoyLEDS[0].TurnOn = 0;
  JoyLEDS[1].TurnOn = 0;
  JoyLEDS[2].TurnOn = 0;
  JoyLEDS[3].TurnOn = 0;
  JoyLEDS[0].TurnOff = 1;
  JoyLEDS[1].TurnOff = 1;
  JoyLEDS[2].TurnOff = 1;
  JoyLEDS[3].TurnOff = 1;



}

void AdminModeExit() {
  wTrig.stopAllTracks();
  lcd.clear();
  lcd.print("   Asher  1.0   ");

  display.clear();
  display2.clear();
  LastMenuControlPin = 8;
}

void AdminModeStartup() {
  lcd.clear();
  lcd.print("  Admin Mode  ");

  display.clear();
  display2.clear();
  wTrig.trackPlayPoly(158);

}
void Startup() {
  wTrig.trackPlayPoly(1);
  const int AnimAround[12] = {0, 1, 2, 3, 7, 11, 15, 14, 13, 12, 8, 4};


  int AminTrail[4];
  for (int lcnt = 0; lcnt < 16; lcnt++) {
    for (int cnt = 0; cnt < 12; cnt++) {
      //Lead LED
      int leadLed = AnimAround[cnt];
      SurfaceLEDS[leadLed].TurnOn = 1;
      SurfaceLEDS[leadLed].OnDuration = 50;

      AminTrail[4] = AminTrail[3];
      AminTrail[3] = AminTrail[2];
      AminTrail[2] = AminTrail[1];
      AminTrail[1] = AminTrail[0];
      AminTrail[0] = leadLed;

      SurfaceLEDS[AminTrail[4]].TurnOn = 1;
      SurfaceLEDS[AminTrail[4]].BrightnessOverideStep = 4;
      SurfaceLEDS[AminTrail[4]].OnDuration = 50;

      SurfaceLEDS[AminTrail[3]].TurnOn = 1;
      SurfaceLEDS[AminTrail[3]].BrightnessOverideStep = 3;
      SurfaceLEDS[AminTrail[3]].OnDuration = 50;

      SurfaceLEDS[AminTrail[2]].TurnOn = 1;
      SurfaceLEDS[AminTrail[2]].BrightnessOverideStep = 2;
      SurfaceLEDS[AminTrail[2]].OnDuration = 50;

      SurfaceLEDS[AminTrail[1]].TurnOn = 1;
      SurfaceLEDS[AminTrail[1]].BrightnessOverideStep = 1;
      SurfaceLEDS[AminTrail[1]].OnDuration = 50;



      ProcessLEDS();
      delay (50);
    }
  }


}//end scene




void EasterEggExit() {
  wTrig.stopAllTracks();
  lcd.clear();
  lcd.print("   Asher  1.0   ");
  lcd.setBacklight(true);
  analogWrite(2, 0);
  display.clear();
  display2.clear();
  LastMenuControlPin = 8;
}

void EasterEggStartup() {

  DigitDisplay1TimerOff = 0;
  DigitDisplay2TimerOff = 0;


  wTrig.stopAllTracks();
  wTrig.samplerateOffset(0);
  //turn off lcd
  lcd.clear();
  lcd.setBacklight(false);
  //turn off power button
  analogWrite(2, 0);
  display.clear();
  display2.clear();

  //Dramatic Pause
  delay (4000);

  //play jingle
  wTrig.trackPlayPoly(17);
  //wait for jingle to end
  delay (10000);
  //play the way i see it
  wTrig.trackPlayPoly(27);
  delay (4700);

  //play time machine on
  wTrig.trackPlayPoly(18);
  //flash stuff
  display2.showNumberDec(0000, true);
  display.showNumberDec(0000, true);
  lcd.setBacklight(true);
  delay (100);
  display2.setBrightness(0);
  display.setBrightness(0);
  lcd.setBacklight(false);

  delay (4000);
  display2.showNumberDec(0000, true);
  wTrig.trackPlayPoly(19);
  display2.setBrightness(0);
  display2.showNumberDec(1985, true);
  delay (500);
  display.showNumberDec(0000, true);
  wTrig.trackPlayPoly(19);
  display.setBrightness(0);
  display.showNumberDec(1955, true);
  delay (500);
  wTrig.trackPlayPoly(32);
  delay (3000);
  wTrig.trackPlayPoly(20);


}


void RocketMode0() {
  //play star trek
  Serial.print("scene 0");
    wTrig.trackPlayPoly(183); 
     wTrig.trackGain(183, -10);
  delay (8583);
  RocketMode = 1;

}
void RocketMode1() {
  //play star trek
  Serial.print("scene 0");
  wTrig.trackPlayPoly(182); 
  wTrig.trackGain(182, -10); // Background 1
  wTrig.trackLoop(182, 1);
  wTrig.trackPlayPoly(184);
    wTrig.trackGain(184, -10);// Background 2
  wTrig.trackLoop(184, 1);
 
  RocketMode = 2;
  RocketButtonFlash =1;

}

void RocketMode3() {
//1096 -10 ///hard coded wav times beacause i probable screwed up the tx wireing on the wav trigger
//754 -9
//880 - 8
//934 -7
//988 - 6
//1185 -5
//1311 4
//1419 -3
//1393 - 2
//709 - 1
//880 -9
//1868 - end
  //stop all
  RocketMode = 4;
  wTrig.stopAllTracks();
  RocketButtonFlash =0; // turn offy the flashy
  //ResetSurface();
  //start countdown
  wTrig.trackPlayPoly(193); 
  wTrig.trackGain(193, 10);
  RocketTakeOffFlashy(10);
  //stop 
  //delay(1096);
  delay(800);
  Digits(1, 1, 10, 10, 4, 4, 750, 750);
  RocketTakeOffFlashy(9);
    delay(754);
  Digits(1, 1, 9, 9, 4, 4, 750, 750);
  RocketTakeOffFlashy(8);
    delay(880);
  Digits(1, 1, 8, 8, 4, 4, 750, 750);
  RocketTakeOffFlashy(7);
    delay(934);
  Digits(1, 1, 7, 7, 4, 4, 750, 750);
  RocketTakeOffFlashy(6);
    delay(988);
  Digits(1, 1, 6, 6, 4, 4, 750, 750);
  RocketTakeOffFlashy(5);
    delay(1185);
  Digits(1, 1, 5, 5, 4, 4, 750, 750);
  RocketTakeOffFlashy(4);
    delay(1311);
  Digits(1, 1, 4, 4, 4, 4, 750, 750);
  RocketTakeOffFlashy(3);
    delay(1419);
  Digits(1, 1, 3, 3, 4, 4, 750, 750);
  RocketTakeOffFlashy(2);
    delay(1393);
  Digits(1, 1, 2, 2, 4, 4, 750, 750);
  RocketTakeOffFlashy(1);
    delay(709);
  Digits(1, 1, 1, 1, 4, 4, 750, 750);
  RocketTakeOffFlashy(0);
    delay(880);
    RocketButtonFlash =1;
    //displayliftoff 
    display2.setSegments(TM_LIFT);
    display.setSegments(TM_OFF);
 // Digits(1, 1, 0, 0, 4, 4, 750, 750); // .ift off
  delay (1300);
    wTrig.trackPlayPoly(185);
 wTrig.trackGain(185, -5);// Background 2
  wTrig.trackLoop(185, 1);
RocketCurrentStep = 7;


  
  
  
}

void RocketMode4() {
  
  ResetSurface();
  RocketButtonFlash =0;
  wTrig.trackPlayPoly(218);
  delay(2500);
    wTrig.trackPlayPoly(217);
   wTrig.trackLoop(217, 1);   
    wTrig.trackPlayPoly(200);
    delay (5616);
   wTrig.trackPlayPoly(201);
    delay (5205);

RocketMode = 5;
  
}
