void Init_pins() {


  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  // pins a input not specifically called as default state
  pinMode(54, INPUT_PULLUP); //Big Button Left
  pinMode(18, INPUT_PULLUP); //Big Button Right

  pinMode(66, INPUT_PULLUP); //Toggle 1
  pinMode(68, INPUT_PULLUP); //Toggle 2
  pinMode(69, INPUT_PULLUP); //Toggle 3
  pinMode(67, INPUT_PULLUP); //Toggle 4

  //Set current toggle states
  Toggle1LastState = digitalRead(66);
  Toggle2LastState = digitalRead(68);
  Toggle3LastState = digitalRead(69);
  Toggle4LastState = digitalRead(67);

  //Set IO Expander Switches

  io1.begin(0x3F); //need comms error check here
  io2.begin(0x71);

  io1.pinMode(4, INPUT_PULLUP); // Joy Up
  io1.pinMode(5, INPUT_PULLUP); // Joy Down
  io1.pinMode(6, INPUT_PULLUP); // Joy Left
  io1.pinMode(7, INPUT_PULLUP); // Joy Rigth

  io1.pinMode(12, INPUT_PULLUP); //Switch 1
  io1.pinMode(13, INPUT_PULLUP); //Switch 4
  io1.pinMode(14, INPUT_PULLUP); //Switch 2
  io1.pinMode(15, INPUT_PULLUP); //Switch 3

  Switch1LastState = io1.digitalRead(12);
  Switch2LastState = io1.digitalRead(14);
  Switch3LastState = io1.digitalRead(15);
  Switch4LastState = io1.digitalRead(13);

  //menu Control Pins

  for ( int i = 0; i <= 7; i++) {
    pinMode( MenuControlPins[i], INPUT);
    digitalWrite( MenuControlPins[i], HIGH); // turn on internal pullup resistor
  }

  //CapacitiveSensors
  CapRight.set_CS_AutocaL_Millis(0xFFFFFFFF);
  CapLeft.set_CS_AutocaL_Millis(0xFFFFFFFF);


  ///set LED pins status

  //Left to Right
  JoyLEDS[0].Board = 1;
  JoyLEDS[0].Pin = 0;
  JoyLEDS[0].MaxBrightness = 240;
  io1.pinMode(0, ANALOG_OUTPUT);
  JoyLEDS[1].Board = 1;
  JoyLEDS[1].Pin = 1;
  JoyLEDS[1].MaxBrightness = 240;
  io1.pinMode(1, ANALOG_OUTPUT);
  JoyLEDS[2].Board = 1;
  JoyLEDS[2].Pin = 2;
  JoyLEDS[2].MaxBrightness = 240;
  io1.pinMode(2, ANALOG_OUTPUT);
  JoyLEDS[3].Board = 1;
  JoyLEDS[3].Pin = 3;
  JoyLEDS[3].MaxBrightness = 240;
  io1.pinMode(3, ANALOG_OUTPUT);

  //Simples
  ToggleLEDS[0].Board = 0;
  ToggleLEDS[0].Pin = 7;
  ToggleLEDS[0].MaxBrightness = 50;
  pinMode(7, OUTPUT);

  //Top to Bottom
  SurfaceRowsLEDS[0].Board = 0;
  SurfaceRowsLEDS[0].Pin = 4;
  SurfaceRowsLEDS[0].MaxBrightness = 20;
  pinMode(4, OUTPUT);
  SurfaceRowsLEDS[1].Board = 0;
  SurfaceRowsLEDS[1].Pin = 6;
  SurfaceRowsLEDS[1].MaxBrightness = 20;
  pinMode(6, OUTPUT);
  SurfaceRowsLEDS[2].Board = 0;
  SurfaceRowsLEDS[2].Pin = 5;
  SurfaceRowsLEDS[2].MaxBrightness = 50;
  pinMode(5, OUTPUT);
  SurfaceRowsLEDS[3].Board = 0;
  SurfaceRowsLEDS[3].Pin = 3;
  SurfaceRowsLEDS[3].MaxBrightness = 5;
  pinMode(3, OUTPUT);

  //Left to Right
  SurfaceColLEDS[0].Board = 0;
  SurfaceColLEDS[0].Pin = 10;
  SurfaceColLEDS[0].MaxBrightness = 1;
  pinMode(10, ANALOG_OUTPUT);
  SurfaceColLEDS[1].Board = 0;
  SurfaceColLEDS[1].Pin = 12;
  SurfaceColLEDS[1].MaxBrightness = 1;
  pinMode(12, ANALOG_OUTPUT);
  SurfaceColLEDS[2].Board = 0;
  SurfaceColLEDS[2].Pin = 9;
  SurfaceColLEDS[2].MaxBrightness = 1;
  pinMode(9, ANALOG_OUTPUT);
  SurfaceColLEDS[3].Board = 0;
  SurfaceColLEDS[3].Pin = 11;
  SurfaceColLEDS[3].MaxBrightness = 1;
  pinMode(11, ANALOG_OUTPUT);


  //surface pins

  SurfaceLEDS[0].Board = 2;
  SurfaceLEDS[0].Pin = SurfacePins[0];
  SurfaceLEDS[0].MaxBrightness = 192;
  io2.pinMode(SurfacePins[0], ANALOG_OUTPUT);

  SurfaceLEDS[1].Board = 2;
  SurfaceLEDS[1].Pin = SurfacePins[1];
  SurfaceLEDS[1].MaxBrightness = 192;
  io2.pinMode(SurfacePins[1], ANALOG_OUTPUT);

  SurfaceLEDS[2].Board = 2;
  SurfaceLEDS[2].Pin = SurfacePins[2];
  SurfaceLEDS[2].MaxBrightness = 192;
  io2.pinMode(SurfacePins[2], ANALOG_OUTPUT);

  SurfaceLEDS[3].Board = 2;
  SurfaceLEDS[3].Pin = SurfacePins[3];
  SurfaceLEDS[3].MaxBrightness = 192;
  io2.pinMode(SurfacePins[3], ANALOG_OUTPUT);


  //yellow
  SurfaceLEDS[4].Board = 2;
  SurfaceLEDS[4].Pin = SurfacePins[4];
  SurfaceLEDS[4].MaxBrightness = 150;
  io2.pinMode(SurfacePins[4], ANALOG_OUTPUT);

  SurfaceLEDS[5].Board = 2;
  SurfaceLEDS[5].Pin = SurfacePins[5];
  SurfaceLEDS[5].MaxBrightness = 150;
  io2.pinMode(SurfacePins[5], ANALOG_OUTPUT);

  SurfaceLEDS[6].Board = 2;
  SurfaceLEDS[6].Pin = SurfacePins[6];
  SurfaceLEDS[6].MaxBrightness = 150;
  io2.pinMode(SurfacePins[6], ANALOG_OUTPUT);

  SurfaceLEDS[7].Board = 2;
  SurfaceLEDS[7].Pin = SurfacePins[7];
  SurfaceLEDS[7].MaxBrightness = 150;
  io2.pinMode(SurfacePins[7], ANALOG_OUTPUT);

  //green
  SurfaceLEDS[8].Board = 2;
  SurfaceLEDS[8].Pin = SurfacePins[8];
  SurfaceLEDS[8].MaxBrightness = 225;
  io2.pinMode(SurfacePins[8], ANALOG_OUTPUT);

  SurfaceLEDS[9].Board = 2;
  SurfaceLEDS[9].Pin = SurfacePins[9];
  SurfaceLEDS[9].MaxBrightness = 225;
  io2.pinMode(SurfacePins[9], ANALOG_OUTPUT);

  SurfaceLEDS[10].Board = 2;
  SurfaceLEDS[10].Pin = SurfacePins[10];
  SurfaceLEDS[10].MaxBrightness = 225;
  io2.pinMode(SurfacePins[10], ANALOG_OUTPUT);

  SurfaceLEDS[11].Board = 2;
  SurfaceLEDS[11].Pin = SurfacePins[11];
  SurfaceLEDS[11].MaxBrightness = 192;
  io2.pinMode(SurfacePins[11], ANALOG_OUTPUT);

  //blue

  SurfaceLEDS[12].Board = 2;
  SurfaceLEDS[12].Pin = SurfacePins[12];
  SurfaceLEDS[12].MaxBrightness = 192;
  io2.pinMode(SurfacePins[12], ANALOG_OUTPUT);

  SurfaceLEDS[13].Board = 2;
  SurfaceLEDS[13].Pin = SurfacePins[13];
  SurfaceLEDS[13].MaxBrightness = 192;
  io2.pinMode(SurfacePins[13], ANALOG_OUTPUT);

  SurfaceLEDS[14].Board = 2;
  SurfaceLEDS[14].Pin = SurfacePins[14];
  SurfaceLEDS[14].MaxBrightness = 192;
  io2.pinMode(SurfacePins[14], ANALOG_OUTPUT);

  SurfaceLEDS[15].Board = 2;
  SurfaceLEDS[15].Pin = SurfacePins[15];
  SurfaceLEDS[15].MaxBrightness = 192;
  io2.pinMode(SurfacePins[15], ANALOG_OUTPUT);









}
