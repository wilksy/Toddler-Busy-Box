// Action Dictionary

//int CountdownPlaying = 0;
//int FM_NextAction =0;
//int FM_Advanced =0;
//int FM_TimeToAction = 5000;


// 0 press joy up
// 1 press joy down
// 2 press joy left
// 3 press joy right
// 4 press left button
// 5 press right right
// 6 press top switch
// 7 press bottom switch
// 8 press red
// 9 press yellow
// 10 press green
// 11 press blue
// 12 Press any keypad

// advanced

// 13 press 0
// 14 press 1
// 15 press 2
// 16 press 3
// 17 press 4
// 18 press 5
// 19 press 6
// 20 press 7
// 21 press 8
// 22 press 9

void FM_GetNextAction() {
  randomSeed(millis());
  int randNumber;
  int randNumber2;
  if (FM_Advanced == 0 ) { /// ignore individual keypresses if simple mode
    randNumber = random(13);
  }
  else {
    randNumber = random(13); // wa 23
  }

  FM_NextAction = randNumber;

  if (FM_Advanced != 0 && randNumber == 12 ) {
    //it's advanced so add another random number onto 12 from 1-10
    //we don't want to up weight numbers in keypad being selected.
    randNumber2 = random(10);

    FM_NextAction = FM_NextAction + randNumber2;
  }



  ///now we play the instruction
  switch (FM_NextAction) {
    case 0 :
      Voice_Press_the_Joystick(0);
      break;
    case 1 :
      Voice_Press_the_Joystick(1);
      break;
    case 2 :
      Voice_Press_the_Joystick(2);
      break;
    case 3 :
      Voice_Press_the_Joystick(3);
      break;
    case 4 :
      Voice_Press_the_button(0);
      break;
    case 5 :
      Voice_Press_the_button(1);
      break;
    case 6 :
      Voice_Turn_on_a_switch(0);
      break;
    case 7 :
      Voice_Turn_on_a_switch(1);
      break;
    case 8 :
      Voice_Press_the_button(2);
      break;
    case 9 :
      Voice_Press_the_button(3);
      break;
    case 10 :
      Voice_Press_the_button(4);
      break;
    case 11 :
      Voice_Press_the_button(5);
      break;
    case 12 :
      Voice_Press_keypad();
      break;
    case 13 :
      Voice_Press_number(0);
      break;
    case 14 :
      Voice_Press_number(1);
      break;
    case 15 :
      Voice_Press_number(2);
      break;
    case 16 :
      Voice_Press_number(3);
      break;
    case 17 :
      Voice_Press_number(4);
      break;
    case 18 :
      Voice_Press_number(5);
      break;
    case 19 :
      Voice_Press_number(6);
      break;
    case 20 :
      Voice_Press_number(7);
      break;
    case 21 :
      Voice_Press_number(8);
      break;
    case 22 :
      Voice_Press_number(9);
      break;

  }



}

void FM_Check_Action(int fm_action) {


  if (FM_NextAction == fm_action) {
    //correct
    FM_Score ++;
    display.setBrightness(0);
    display.showNumberDec(FM_Score, true);
    //wTrig.stopAllTracks();
    wTrig.trackPlayPoly(135);
    //next action
    FM_GetNextAction();
  }
  else
  {
    //wrong
    Serial.println(".wrong.");
    wTrig.stopAllTracks();
    wTrig.trackPlayPoly(134);
    //now restart the music
    FM_GameON = 0;

  }

}

void FM_Ticker() {
  int secondsleft = 30 - ((millis() - FM_TickMillis) / 1000);
  display2.setBrightness(0);
  display2.showNumberDec(secondsleft, true);

  if (secondsleft <= 1 ) {
    delay(3000); //block to stop a re-game
    FM_GameON = 0;
    FM_Score = 0;
  }


}
