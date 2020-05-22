
//button
// 0 = left
// 1 = right
// 2 red
// 3 = yellow
// 4 = green
// 5 = blue


void Voice_Press_the_button(int VBut) {

  wTrig.trackPlayPoly(131); // press the
  delay (800); //length of Press the

  int offset = 100;

  switch (VBut) {
    case 0 :
      wTrig.trackPlayPoly(107);
      delay (576 - offset);
      break;
    case 1 :
      wTrig.trackPlayPoly(108);
      delay (629 - offset);
      break;
    case 2 :
      Serial.println(".said red");

      wTrig.trackPlayPoly(118);
      delay (604 - offset);
      break;
    case 3 :
      Serial.println(".said yello");
      wTrig.trackPlayPoly(120);
      delay (712 - offset);
      break;
    case 4 :
      Serial.println(".said green");
      wTrig.trackPlayPoly(119);
      delay (739 - offset);
      break;
    case 5 :
      Serial.println(".said blue");
      wTrig.trackPlayPoly(117);
      delay (578 - offset);
      break;
  }
  wTrig.trackPlayPoly(113);
}

void Voice_Press_number(int Vnum) {

  wTrig.trackPlayPoly(111); // press number
  delay (784); //length of Press the

  int offset = 100;

  switch (Vnum) {
    case 0 :
      wTrig.trackPlayPoly(130);
      delay (900 - offset);
      break;
    case 1 :
      wTrig.trackPlayPoly(121);
      delay (400 - offset);
      break;
    case 2 :
      wTrig.trackPlayPoly(122);
      delay (400 - offset);
      break;
    case 3 :
      wTrig.trackPlayPoly(123);
      delay (400 - offset);
      break;
    case 4 :
      wTrig.trackPlayPoly(124);
      delay (400 - offset);
      break;
    case 5 :
      wTrig.trackPlayPoly(125);
      delay (400 - offset);
      break;
    case 6 :
      wTrig.trackPlayPoly(126);
      delay (400 - offset);
      break;
    case 7 :
      wTrig.trackPlayPoly(127);
      delay (400 - offset);
      break;
    case 8 :
      wTrig.trackPlayPoly(128);
      delay (400 - offset);
      break;
    case 9 :
      wTrig.trackPlayPoly(129);
      delay (400 - offset);
      break;
  }
  //wTrig.trackPlayPoly(115); Remove "on the Keypad"
}

void Voice_Press_the_Joystick(int Vjoy) {

  // 0 up, 1 down, 2 left, 3 right

  wTrig.trackPlayPoly(110); // press the
  delay (491); //length of Press the

  int offset = 50;

  switch (Vjoy) {
    case 0 :
      wTrig.trackPlayPoly(105);
      delay (576 - offset);
      break;
    case 1 :
      wTrig.trackPlayPoly(106);
      delay (629 - offset);
      break;
    case 2 :
      wTrig.trackPlayPoly(107);
      delay (576 - offset);
      break;
    case 3 :
      wTrig.trackPlayPoly(108);
      delay (629 - offset);
      break;
    case 4 :
      wTrig.trackPlayPoly(120);
      delay (739 - offset);
      break;
  }
  //wTrig.trackPlayPoly(109); //on the joystivk
}

void Voice_Turn_on_a_switch(int tb) {
  // 0 top//1 bottom

  if (tb == 0) {
    wTrig.trackPlayPoly(132); // press the
  }
  else
  {
    wTrig.trackPlayPoly(133); // press the
  }
}
void Voice_Press_keypad() {
  wTrig.trackPlayPoly(138); // press the

}
