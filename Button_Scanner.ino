void ScanButtons() {

  if (MasterButtonBlock == 1) {
    return;
  }


  //Control Block Codes
  //1 = Main Surface
  //2 = Keypad
  //3 = Big Buttons
  //4 = Toggle switches
  //5 = Switches
  //6 = JoyStick
  //7 = Menu
  //8 =Capacative Sensors

  int reading;
  //Main Surface Check
  char SurfaceButton = keypad.getKey();
  if (SurfaceButton) {
    ButtonData abut;
    abut.ControlBlock = 1;
    abut.CharPressed = SurfaceButton;
    switch (SurfaceButton) {
      case '1':
        abut.State = 0;
        break;
      case '2':
        abut.State = 1;
        break;
      case '3':
        abut.State = 2;
        break;
      case '4':
        abut.State = 3;
        break;
      case '5':
        abut.State = 4;
        break;
      case '6':
        abut.State = 5;
        break;
      case '7':
        abut.State = 6;
        break;
      case '8':
        abut.State = 7;
        break;
      case '9':
        abut.State = 8;
        break;
      case 'a':
        abut.State = 9;
        break;
      case 'b':
        abut.State = 10;
        break;
      case 'c':
        abut.State = 11;
        break;
      case 'd':
        abut.State = 12;
        break;
      case 'e':
        abut.State = 13;
        break;
      case 'f':
        abut.State = 14;
        break;
      case 'g':
        abut.State = 15;
        break;
    }
    //update surface switch state (if needed) -manage later
    if (SurfaceState[abut.State] == 0) {
      SurfaceState[abut.State] = 1;
    }
    else
    {
      SurfaceState[abut.State] = 0;
    }

    ButtonEvent(abut);
  }
  //Keypad Check
  char keypadButton = keypad2.getKey();
  if (keypadButton) {
    ButtonData abut;
    abut.ControlBlock = 2;
    abut.CharPressed = keypadButton;
    switch (keypadButton) {
      case '1':
        abut.State = 1;
        break;
      case '2':
        abut.State = 2;
        break;
      case '3':
        abut.State = 3;
        break;
      case '4':
        abut.State = 4;
        break;
      case '5':
        abut.State = 5;
        break;
      case '6':
        abut.State = 6;
        break;
      case '7':
        abut.State = 7;
        break;
      case '8':
        abut.State = 8;
        break;
      case '9':
        abut.State = 9;
        break;
      case '*':
        abut.State = 10;
        break;
      case '0':
        abut.State = 11;
        break;
      case '#':
        abut.State = 12;
        break;
    }
    ButtonEvent(abut);;
  }

  //Big Buttons Check
  reading = digitalRead(54);
  if ((reading  == 0) && ((millis() - ButtonBigLeftlastDebounce) > ButtonBigdebounceDelay)) {
    ButtonBigLeftlastDebounce = millis();
    ButtonData abut;
    abut.ControlBlock = 3;
    abut.CharPressed = '1';
    abut.State = 1;
    ButtonEvent(abut);
  }
  reading = digitalRead(18);
  if ((reading  == 0) && ((millis() - ButtonBigRightlastDebounce) > ButtonBigdebounceDelay)) {
    ButtonBigRightlastDebounce = millis();
    ButtonData abut;
    abut.ControlBlock = 3;
    abut.CharPressed = 'R';
    abut.State = 1;
    ButtonEvent(abut);
  }

  //Toggle States

  reading = digitalRead(66);
  if ((reading  != Toggle1LastState) && ((millis() - Toggle1LastDebounce) > ToggledebounceDelay)) {
    Toggle1LastDebounce = millis();
    Toggle1LastState = reading ;
    ButtonData abut;
    abut.ControlBlock = 4;
    abut.CharPressed = '1';
    abut.State = reading;
    ButtonEvent(abut);
  }

  reading = digitalRead(68);
  if ((reading  != Toggle2LastState) && ((millis() - Toggle2LastDebounce) > ToggledebounceDelay)) {
    Toggle2LastDebounce = millis();
    Toggle2LastState = reading ;
    ButtonData abut;
    abut.ControlBlock = 4;
    abut.CharPressed = '2';
    abut.State = reading;
    ButtonEvent(abut);
  }

  reading = digitalRead(69);
  if ((reading  != Toggle3LastState) && ((millis() - Toggle3LastDebounce) > ToggledebounceDelay)) {
    Toggle3LastDebounce = millis();
    Toggle3LastState = reading ;
    ButtonData abut;
    abut.ControlBlock = 4;
    abut.CharPressed = '3';
    abut.State = reading;
    ButtonEvent(abut);
  }

  reading = digitalRead(67);
  if ((reading  != Toggle4LastState) && ((millis() - Toggle4LastDebounce) > ToggledebounceDelay)) {
    Toggle4LastDebounce = millis();
    Toggle4LastState = reading ;
    ButtonData abut;
    abut.ControlBlock = 4;
    abut.CharPressed = '4';
    abut.State = reading;
    ButtonEvent(abut);
  }

  //Switch States

  reading = io1.digitalRead(12);
  if ((reading  != Switch1LastState) && ((millis() - Switch1LastDebounce) > SwitchbounceDelay)) {
    Switch1LastDebounce = millis();
    Switch1LastState = reading ;
    ButtonData abut;
    abut.ControlBlock = 5;
    abut.CharPressed = '1';
    abut.State = reading;
    ButtonEvent(abut);
  }

  reading = io1.digitalRead(14);
  if ((reading  != Switch2LastState) && ((millis() - Switch2LastDebounce) > SwitchbounceDelay)) {
    Switch2LastDebounce = millis();
    Switch2LastState = reading ;
    ButtonData abut;
    abut.ControlBlock = 5;
    abut.CharPressed = '2';
    abut.State = reading;
    ButtonEvent(abut);
  }

  reading = io1.digitalRead(15);
  if ((reading  != Switch3LastState) && ((millis() - Switch3LastDebounce) > SwitchbounceDelay)) {
    Switch3LastDebounce = millis();
    Switch3LastState = reading ;
    ButtonData abut;
    abut.ControlBlock = 5;
    abut.CharPressed = '3';
    abut.State = reading;
    ButtonEvent(abut);
  }

  reading = io1.digitalRead(13);
  if ((reading  != Switch4LastState) && ((millis() - Switch4LastDebounce) > SwitchbounceDelay)) {
    Switch4LastDebounce = millis();
    Switch4LastState = reading ;
    ButtonData abut;
    abut.ControlBlock = 5;
    abut.CharPressed = '4';
    abut.State = reading;
    ButtonEvent(abut);
  }

  //Joystick
  reading = io1.digitalRead(4); // up
  if ((reading  == 0) && ((millis() - JoyStickUplastDebounce) > JoyStickbounceDelay)) {
    JoyStickUplastDebounce = millis();
    ButtonData abut;
    abut.ControlBlock = 6;
    abut.CharPressed = 'u';
    abut.State = 0;
    ButtonEvent(abut);
  }

  reading = io1.digitalRead(5); // down
  if ((reading  == 0) && ((millis() - JoyStickDownlastDebounce) > JoyStickbounceDelay)) {
    JoyStickDownlastDebounce = millis();
    ButtonData abut;
    abut.ControlBlock = 6;
    abut.CharPressed = 'd';
    abut.State = 1;
    ButtonEvent(abut);
  }

  reading = io1.digitalRead(6); // left
  if ((reading  == 0) && ((millis() - JoyStickLeftlastDebounce) > JoyStickbounceDelay)) {
    JoyStickLeftlastDebounce = millis();
    ButtonData abut;
    abut.ControlBlock = 6;
    abut.CharPressed = 'l';
    abut.State = 2;
    ButtonEvent(abut);
  }

  reading = io1.digitalRead(7); // right
  if ((reading  == 0) && ((millis() - JoyStickRightlastDebounce) > JoyStickbounceDelay)) {
    JoyStickRightlastDebounce = millis();
    ButtonData abut;
    abut.ControlBlock = 6;
    abut.CharPressed = 'r';
    abut.State = 3;
    ButtonEvent(abut);
  }

  //Menu Control

  for ( int i = 0; i <= 7; i++) {
    int val = digitalRead( MenuControlPins[i] ); // look at a rotary switch input
    if ((i != LastMenuControlPin) && ((millis() - MenuLastBounce) > MenuBounceDelay))
      if ( val == LOW ) { // it's selected

        ButtonData abut;
        abut.ControlBlock = 7;
        abut.CharPressed = '0';
        abut.State = i;
        ButtonEvent(abut);
        LastMenuControlPin = i;
        MenuLastBounce = millis();
      }
  }

  //capacative test (may need to move to a faster loop, or it's own looks. this may slow this loop down.
  if (CapOnOff == 1) {

    reading = CapRight.capacitiveSensor(30);


    if (CapButMode == 0) {
      int Proxreading;
      if ((reading  > 500) && ((millis() - CapButRightlastDebounce) > CapButdebounceDelay)) {
        CapButRightlastDebounce = millis();
        Proxreading = 6;
        CapButRightLastState = Proxreading;
        ButtonData abut;
        abut.ControlBlock = 8;
        abut.CharPressed = 'r';
        abut.State = Proxreading;
        ButtonEvent(abut);
      }
    }
    if (CapButMode == 1) { //cap mode one is not just NEAR
      int Proxreading;

      if ((reading  > 50) && ((millis() - CapButRightlastDebounce) > CapButdebounceDelay)) { //higher cap for right test
        Proxreading = 6;
        //if (reading > 200) {
        //Proxreading = 6;
        //}
        //else if (reading > 100) {
        //Proxreading = 5;
        //}
        //else if (reading > 50) {
        //Proxreading = 4;
        //}
        //else if (reading > 40) {
        //Proxreading = 3;
        //}
        //else if (reading > 30) {
        //Proxreading = 2;
        //}
        //else  {
        //Proxreading = 1;
        //}

        CapButRightLastState = Proxreading;
        CapButRightlastDebounce = millis();
        ButtonData abut;
        abut.ControlBlock = 8;
        abut.CharPressed = 'r';
        abut.State = reading ;//Proxreading;
        ButtonEvent(abut);
      }
    }

    reading = CapLeft.capacitiveSensor(30);

    if (CapButMode == 0) {
      int Proxreading;
      if ((reading  > 300) && ((millis() - CapButLeftlastDebounce) > CapButdebounceDelay)) {
        CapButLeftlastDebounce = millis();
        Proxreading = 6;
        CapButLeftLastState = Proxreading;
        ButtonData abut;
        abut.ControlBlock = 8;
        abut.CharPressed = 'l';
        abut.State = Proxreading;
        ButtonEvent(abut);
      }
    }
    if (CapButMode == 1) { //cap mode one is not just NEAR
      int Proxreading;

      if ((reading  > 90) && ((millis() - CapButLeftlastDebounce) > CapButdebounceDelay)) {

        //if (reading > 200) {
        //Proxreading = 6;
        //}
        //else if (reading > 100) {
        //Proxreading = 5;
        //}
        //else if (reading > 50) {
        //Proxreading = 4;
        // }
        //else if (reading > 40) {
        //Proxreading = 3;
        //}
        //else if (reading > 30) {
        //Proxreading = 2;
        //}
        //else  {
        //Proxreading = 1;
        //}

        CapButLeftLastState = Proxreading;
        CapButLeftlastDebounce = millis();
        ButtonData abut;
        abut.ControlBlock = 8;
        abut.CharPressed = 'l';
        abut.State = reading;//Proxreading;
        ButtonEvent(abut);
      }
    }

  }
  //end cap button

}
