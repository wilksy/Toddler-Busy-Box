void Digits(int Dis1ON, int Dis2ON, int Dis1DIG, int Dis2DIG, int Dig1Leading, int Dig2Leading, unsigned long Dig1Timeroff, unsigned long Dig2Timeroff) {

  if (Dis1ON == 0) {
    display.clear();
  }

  if (Dis2ON == 0) {
    display2.clear();
  }
  //DigitDisplay1Millis

  if (Dis1ON == 1 ) {
    Serial.println("hi");
    display.setBrightness(0);
    if (Dig1Leading == 1) {
      display.showNumberDec(Dis1DIG, true);
    }
    else
    {
      display.showNumberDec(Dis1DIG, false);
    }
  }



  if (Dis2ON == 1 ) {
    display2.setBrightness(0);
    if (Dig2Leading == 1) {
      display2.showNumberDec(Dis2DIG, true);
    }
    else
    {
      display2.showNumberDec(Dis2DIG, false);
    }
  }

  //Dig1Timeroff, unsigned long Dig2Timeroff) {

  if (Dig1Timeroff != 0) {
    DigitDisplay1TimerOff = Dig1Timeroff ;
    DigitDisplay1Millis = millis();
  }
  if (Dig2Timeroff != 0) {
    DigitDisplay2TimerOff = Dig2Timeroff ;
    DigitDisplay2Millis = millis();
  }


}
