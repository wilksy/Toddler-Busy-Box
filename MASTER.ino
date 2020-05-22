
//Library includes
#include <Arduino.h>

//SoftSerial (Use secondary serial if possible)
#include <AltSoftSerial.h>
#include <CapacitiveSensor.h>
#include <Keypad.h>
#include "LCDIC2.h"
#include <Metro.h>
#include <SparkFunSX1509.h>
#include <TM1637Display.h>
#include <wavTrigger.h>
#include <Wire.h> // Include the I2C library (required)

unsigned long MasterTIMEOUT = 0;
const unsigned long TIMEOUTTIME = 60000;
int TIMEOUTISON = 0;
//Easter Egg steps
int Easter1On = 0;
char Easter1[] = {'*', '#', '1', '9', '8', '5'};
int EasterSteps = 0;

char ExitEaster[] = {'*', '#'};
int ExitEasterSteps = 0;

//Admin Mode
int AdminMode = 0;
char Admin[] = {'*', '*', '#', '#', '*', '*'};
int AdminSteps = 0;
int ExitAdminSteps;
//Buttons return Structure
struct ButtonData {
  int ControlBlock;
  char CharPressed;
  int State;
};

//Led Structure & Control Mapping

struct LedData { // 0 Main Board, 1 for IO1, 2 for IO2
  int Board;
  int Pin;
  int TurnOn;
  int TurnOff;
  int On; //0 or 1
  int BrightnessOverideStep;/// 1-4 not 0 for calc use
  int MaxBrightness;
  unsigned long OnMillis;
  unsigned long OnDuration;
};
//LED constants
//Surface Pins 0-15 (16 pins)
const int LedOFF = 255;
const int LedON = 192;
const int SurfacePins[] = {10, 14, 7, 0, 1, 15, 9, 8, 12, 2, 5, 6, 11, 13, 4, 3};
const int JoyStickLedsIO2[4] = {0, 1, 2, 3};
const int SurfaceColorDown[4] = {4, 6, 5, 4};

LedData SurfaceLEDS[16];
LedData SurfaceRowsLEDS[4];
LedData SurfaceColLEDS[4];
LedData ToggleLEDS[1];
LedData JoyLEDS[4];




///TO DO continue with mapping

const int buzzer = 56; //buzzer to arduino pin 9

//System state Options
//Master ButtonBlocker (start-up/menu/admin/game)
int MasterButtonBlock = 0; // start off blocked for startup routine



//Buttons and Switch States
unsigned long ButtonBigLeftlastDebounce = 0;
unsigned long ButtonBigRightlastDebounce = 0;
unsigned long ButtonBigdebounceDelay = 200;

int Toggle1LastState;
int Toggle2LastState;
int Toggle3LastState;
int Toggle4LastState;
unsigned long Toggle1LastDebounce = 0;
unsigned long Toggle2LastDebounce = 0;
unsigned long Toggle3LastDebounce = 0;
unsigned long Toggle4LastDebounce = 0;
unsigned long ToggledebounceDelay = 200;

int Switch1LastState;
int Switch2LastState;
int Switch3LastState;
int Switch4LastState;
unsigned long Switch1LastDebounce = 0;
unsigned long Switch2LastDebounce = 0;
unsigned long Switch3LastDebounce = 0;
unsigned long Switch4LastDebounce = 0;
unsigned long SwitchbounceDelay = 200;

unsigned long JoyStickUplastDebounce = 0;
unsigned long JoyStickDownlastDebounce = 0;
unsigned long JoyStickLeftlastDebounce = 0;
unsigned long JoyStickRightlastDebounce = 0;
unsigned long JoyStickbounceDelay = 200;

int CapOnOff = 1;
unsigned long CapButMode = 0;
unsigned long CapButProximityMin = 25;
unsigned long CapButProximityRightMin = 35;
unsigned long CapButRightLastState ;
unsigned long CapButLeftLastState ;
unsigned long CapButLeftlastDebounce = 0;
unsigned long CapButRightlastDebounce = 0;
unsigned long CapButdebounceDelay = 200;


const int MenuControlPins[] = {47, 37, 41, 49, 45, 51, 43, 39};


int SurfaceState[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};




int LastMenuControlPin = 8; ///force a non existent menu item to produce a menu click (and update display)
int CurrentMenuControl;
unsigned long MenuLastBounce = 0;
unsigned long MenuBounceDelay = 200;

char CurrentLCDText[17] = "   Asher  1.0   ";

//-------Keypad Stuff
const byte SurfaceRows = 4;
const byte SurfaceColumns = 4;
const byte KeyPadRows = 4;
const byte KeyPadColumns = 3;
char SurfaceChars[SurfaceRows][SurfaceColumns] = { // Map Chars to button matrix
  {'1', '2', '3', '4'},
  {'5', '6', '7', '8'},
  {'9', 'a', 'b', 'c'},
  {'d', 'e', 'f', 'g'}
};
char KeyPadChars[KeyPadRows][KeyPadColumns] = { // Map Chars to button matrix
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte SurfaceRowPins[SurfaceRows] = {22, 24, 26, 28}; //connect to the row pinouts of the Surface
byte SurfaceColumnPins[SurfaceColumns] = {30, 32, 34, 36}; //connect to the column pinouts of the Surface
byte KeyPadRowPins[KeyPadRows] = {33, 23, 25, 29}; //connect to the row pinouts of the keypad
byte KeyPadColumnPins[KeyPadColumns] = {31, 35, 27}; //connect to the column pinouts of the keypad

//Create keypad and button surface objects
Keypad keypad = Keypad( makeKeymap(SurfaceChars), SurfaceRowPins, SurfaceColumnPins, SurfaceRows,  SurfaceColumns); // Surface
Keypad keypad2 = Keypad( makeKeymap(KeyPadChars), KeyPadRowPins, KeyPadColumnPins, KeyPadRows, KeyPadColumns ); // Keypad

//IO Expander SC1509 Objects
SX1509 io1;
SX1509 io2;

//configure capacitive sensors
CapacitiveSensor   CapRight = CapacitiveSensor(16, 13);
CapacitiveSensor   CapLeft = CapacitiveSensor(64, 63);

//LCD Screen
LCDIC2 lcd(0x27, 16, 2);
unsigned long LCDTimeOutToMenu = 0;
unsigned long LCDTimeOutToMenuMillies = 0;

//digits Display
#define CLK 40 //left
#define DIO 38
#define CLK2 44 //right
#define DIO2 42
//Digits Objects
TM1637Display display(CLK, DIO);
TM1637Display display2(CLK2, DIO2);
unsigned long DigitDisplay1TimerOff = 0;
unsigned long DigitDisplay2TimerOff = 0;
unsigned long DigitDisplay1Millis = 0;
unsigned long DigitDisplay2Millis = 0;

//audio board
wavTrigger wTrig;

int MasterVolume = -10; //-70 to +4.


//Game Varaibles

String Animals[16] = {"    Elephant    ", "       Hen      ", "    Dinosaur    ", "       Cat      ", "       Cow      ", "       Dog      ", "      Frog      ", "      Horse     ", "       Owl      ", "     Monkey     ", "       Pig      ", "     Cockrel     ", "      Seal      ", "      Duck      ", "      Sheep     ", "     Donkey     "};

int CurrentFindButton = 16; //fake value to initite a new find

//Simple Simon Vars
const int SS_MAX_LEVEL = 100;
int SS_sequence[SS_MAX_LEVEL];
int SS_your_sequence[SS_MAX_LEVEL];
int SS_level = 1;
int SS_velocity = 1000;

//Sequencer Var
int SequencerIsOn = 0;
unsigned long SeqMasterTempo = 100;
unsigned long SeqPreviousTick = 0;
int SeqCurrentStep = 0;
int SeqMode = 0; //0 = notes, 1 = drums
int SeqNotes[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int SeqDrums[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int SampleBank = 0;
int DrumBank = 0;

//Mini Pac Man vars

int Pac_Speed = 1000;
int Pac_StartPos = 0;
int Pac_Direction = 0; //0 = left 1 = right, 2 = down, 3 = up
int Pac_GhostPosition = 0;
int Pac_WalkTick = 0; // 0/1 flipflop
int Pac_LoopOn = 0; // master Loop control
unsigned long Pac_TickMillis  = 0;

///test
char gWTrigVersion[VERSION_STRING_LEN];
int  gNumTracks;

//followme
int CountdownPlaying = 0;
int FM_NextAction = 0;
int FM_Advanced = 1;
int FM_Countdown = 30000;
unsigned long FM_TickMillis  = 0;
int FM_Score = 0;
int FM_GameON = 0;




void setup() {
  Serial.begin(9600); // Debug Serial, REMOVE WHEN LIVE

  //POWER LED
  analogWrite(2, 1);

  //Reset Digits
  //display.setBrightness(0, false);
  //display2.setBrightness(0, false);
  display.clear();
  display2.clear();

  //Audio Board start
  wTrig.start();
  wTrig.masterGain(MasterVolume);
  //ensure everythig is idle
  wTrig.stopAllTracks();

  wTrig.samplerateOffset(0);

  //wTrig.setReporting(true); //test
  //delay(100);

  //if (wTrig.getVersion(gWTrigVersion, VERSION_STRING_LEN)) {
  //  Serial.print(gWTrigVersion);

  //}
  //else{
  //Serial.print("WAV Trigger response not available");
  //}



  //analogWrite(8, 192); //turn on power light
  //Pins have static status - Set Mode Now
  Init_pins();
  // Start Up Sound



  //Initial LCD Status
  lcd.begin();
  lcd.print(CurrentLCDText);

  Startup();
  MasterButtonBlock = 0; //Ready for standard use (scenes are auto blocking anyway)



}

void loop() {
  //Master Control Loop
  ScanButtons();
  ProcessLEDS();
  CheckTimeout();

  //run Sequencer loop
  if (SequencerIsOn == 1 && TIMEOUTISON != 1) {
    Sequencer();
  }
  //run pac man loop
  if (Pac_LoopOn == 1 && TIMEOUTISON != 1) {
    PacManLoop();
  }

  if (FM_GameON == 1 && TIMEOUTISON != 1) {
    FM_Ticker();
  }


}

ButtonData ButtonEvent(ButtonData ReturnButons) { //All Input Events


  ////This is effectivley the master control loop/fuction as most games run on a button/control press
  ////a few games require their own loops which are run if required in the LOOP() function

  MasterTIMEOUT = millis(); //reset timeout;

  if (TIMEOUTISON == 1) {
    //recover from time out
    ExitTimeout();
    ReturnMenu();
  }

  String message = (String)"Event " + ReturnButons.ControlBlock  + "," + ReturnButons.CharPressed + "," + ReturnButons.State;
  Serial.println(message);


  // this is also used as a master, menu change process
  if (ReturnButons.ControlBlock == 7 && Easter1On != 1 && AdminMode != 1 ) {
    //reset surface on menu change
    if (ReturnButons.State != 2 ) { //turn of sequencer loop
      SequencerIsOn = 0;
    }
    if (ReturnButons.State != 4) { // turn off pacman loop
      Pac_LoopOn = 0;
    }
    //always reset surface on menu change
    ResetSurface();
    ProcessLEDS();

    //deal with the Capacative buttons
    if (ReturnButons.State == 2 || ReturnButons.State == 3 || ReturnButons.State == 4 || ReturnButons.State == 5) {
      CapOnOff = 0;
    }
    else
    {
      CapOnOff = 1;
    }

    //deal with countdown loop
    if (ReturnButons.State != 5) {
      FM_GameON = 0;
    }

    if (ReturnButons.State == 2 ) {
      SeqUpdateLeds();// if we are returning to an old session ( or do i clear on exit???)
    }

  }





  //Master Input Handler

  //Admin Mode is on!!

  //EasterEgg mode is on!!

  if (AdminMode == 1) {
    //keypad volume change
    Serial.println("in admin");
    if (ReturnButons.ControlBlock == 2) {
      Serial.println(MasterVolume);
      switch (ReturnButons.State) {
        case 11: //0
          MasterVolume = -70;
          wTrig.masterGain(MasterVolume);
          wTrig.trackPlayPoly(43);
          break;
        case 1:
          MasterVolume = -60;
          wTrig.masterGain(MasterVolume);
          wTrig.trackPlayPoly(34);
          break;
        case 2:
          MasterVolume = -50;
          wTrig.masterGain(MasterVolume);
          wTrig.trackPlayPoly(35);
          break;
        case 3:
          MasterVolume = -40;
          wTrig.masterGain(MasterVolume);
          wTrig.trackPlayPoly(36);
          break;
        case 4:
          MasterVolume = -30;
          wTrig.masterGain(MasterVolume);
          wTrig.trackPlayPoly(37);
          break;
        case 5:
          MasterVolume = -20;
          wTrig.masterGain(MasterVolume);
          wTrig.trackPlayPoly(38);
          break;
        case 6:
          MasterVolume = -15;
          wTrig.masterGain(MasterVolume);
          wTrig.trackPlayPoly(39);
          break;
        case 7:
          MasterVolume = -10;
          wTrig.masterGain(MasterVolume);
          wTrig.trackPlayPoly(40);
          break;
        case 8:
          MasterVolume = -5;
          wTrig.masterGain(MasterVolume);
          wTrig.trackPlayPoly(41);
          break;
        case 9:
          MasterVolume = 0;
          wTrig.masterGain(MasterVolume);
          wTrig.trackPlayPoly(42);
          break;

      }

    }
    //put more admin handling here
  }

  if (Easter1On == 1) {
    if (ReturnButons.ControlBlock == 4) {
      wTrig.trackPlayPoly(19);
    }
    if (ReturnButons.ControlBlock == 3) {
      wTrig.trackPlayPoly(18);
    }
    if (ReturnButons.ControlBlock == 2) {
      wTrig.trackPlayPoly(22);
    }
    if (ReturnButons.ControlBlock == 5) {
      wTrig.trackPlayPoly(21);
    }
    if (ReturnButons.ControlBlock == 6) {
      if (ReturnButons.CharPressed == 'u') {
        wTrig.trackPlayPoly(24);
        ///up to 88
        for ( int i = 0; i <= 88; i++) {
          display.showNumberDec(i, false);
          display2.showNumberDec(i, false);
          delay(5);
        }
        delay (1000);
        wTrig.trackPlayPoly(19);
        display2.showNumberDec(1955, true);
        display.showNumberDec(2012, true);
      }

      if (ReturnButons.CharPressed == 'd') {
        wTrig.trackPlayPoly(33);
      }
    }
    if (ReturnButons.ControlBlock == 1) {
      int randNumber = random(0, 6);
      int BFSoundboard[] = {23, 26, 27, 28, 29, 30, 31};
      wTrig.trackPlayPoly(BFSoundboard[randNumber]);
    }


  }


  if (Easter1On != 1 && AdminMode != 1) {
    //menu Handler
    if (ReturnButons.ControlBlock == 7) {
      wTrig.trackPlayPoly(14);//ping
      CurrentMenuControl = ReturnButons.State;
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
          wTrig.trackPlayPoly(97);//play PacMan Start
          break;
        case 5 :
          lcd.clear();
          lcd.print("    Follow me    ");
          CountdownPlaying = 1;

          FM_GameON = 0;
          break;
        case 6 :
          lcd.clear();
          lcd.print("   The Wiggles  ");
          break;
        default:
          lcd.clear();
          lcd.print("      Empty     ");
          break;
      }
    }


    ///----------------GAME ONE START----------------
    ///-------------------Explore------------------
    ///Simple button response with noise, no interaction or logic (bit like me)

    if (CurrentMenuControl == 0) {




      // Keypad plays a phome DTMF tone
      if (ReturnButons.ControlBlock == 2) {
        if (ReturnButons.State == 11 || ReturnButons.State == 10 || ReturnButons.State == 12) {
          wTrig.trackPlayPoly(130)  ;
        }
        else
        {
          if (ReturnButons.State != 10 || ReturnButons.State != 12) {
            wTrig.trackPlayPoly(ReturnButons.State + 120);// ( +1)
            Digits(1, 1, ReturnButons.State, ReturnButons.State, 0, 0, 2000, 2000);
          }
        }
      }

      // switches

      if (ReturnButons.ControlBlock == 5) {
        if (ReturnButons.State == 1) {
          wTrig.trackPlayPoly(63);
        }
        else {
          wTrig.trackPlayPoly(64);
        }
        if (ReturnButons.CharPressed == '1') {
          SurfaceColLEDS[0].TurnOn = 1;
          SurfaceColLEDS[0].OnDuration = 500;
        }
        if (ReturnButons.CharPressed == '2') {
          SurfaceColLEDS[1].TurnOn = 1;
          SurfaceColLEDS[1].OnDuration = 500;
        }
        if (ReturnButons.CharPressed == '3') {
          SurfaceColLEDS[2].TurnOn = 1;
          SurfaceColLEDS[2].OnDuration = 500;
        }
        if (ReturnButons.CharPressed == '4') {
          SurfaceColLEDS[3].TurnOn = 1;
          SurfaceColLEDS[3].OnDuration = 500;
        }
      }

      //toggle switches
      if (ReturnButons.ControlBlock == 4) {
        if (ReturnButons.State == 1) {
          wTrig.trackPlayPoly(61);
          ToggleLEDS[0].TurnOn = 1;
          ToggleLEDS[0].OnDuration = 250;
        }
        else {
          wTrig.trackPlayPoly(62);
          ToggleLEDS[0].TurnOn = 1;
          ToggleLEDS[0].OnDuration = 250;
        }
      }
      //Big Buttons
      if (ReturnButons.ControlBlock == 3) {
        //hijakckin this to test voice control
        if (ReturnButons.CharPressed == '1') {
          wTrig.trackPlayPoly(101);
        }
        if (ReturnButons.CharPressed == 'R') {
          wTrig.trackPlayPoly(102);
        }
      }

      //Capacitive Buttons - FIX!!!!
      //if (ReturnButons.ControlBlock == 8) {
      // if (ReturnButons.CharPressed == 'l') {
      // wTrig.trackPlayPoly(103);
      //}
      //if (ReturnButons.CharPressed == 'r') {
      //wTrig.trackPlayPoly(104);
      //}
      //}



      // start of surface read and animal noise playback
      if (ReturnButons.ControlBlock == 1) {
        lcd.clear();
        lcd.setCursor(false);
        lcd.print(Animals[ReturnButons.State]);
        LCDTimeOutToMenu = 25000; //one second lcd time out
        LCDTimeOutToMenuMillies = millis();

        //add a quick surface led flash
        SurfaceLEDS[ReturnButons.State].TurnOn = 1;
        SurfaceLEDS[ReturnButons.State].OnDuration = 1000;

        //play "a"
        //wTrig.trackPlaySolo(140);
        //delay(250);
        //play animal name
        int AnimaltoPlay = ReturnButons.State + 142;
        wTrig.trackPlaySolo(AnimaltoPlay);
        delay (750);
        //play soundslike
        wTrig.trackPlaySolo(141);
        delay(1000);
        //play animal noise
        AnimaltoPlay = ReturnButons.State + 81;  //Animal wavs start as position 81
        wTrig.trackPlaySolo(AnimaltoPlay);






      }

      //JoyStick Reads direction an blinks led

      if (ReturnButons.ControlBlock == 6) {
        switch ( ReturnButons.State ) {
          case 0 ://up
            wTrig.trackPlayPoly(105);
            JoyLEDS[0].TurnOn = 1;
            JoyLEDS[0].OnDuration = 1000;
            break;
          case 1 : //down
            wTrig.trackPlayPoly(106);
            JoyLEDS[1].TurnOn = 1;
            JoyLEDS[1].OnDuration = 1000;
            break;
          case 2 ://left
            wTrig.trackPlayPoly(107);
            JoyLEDS[2].TurnOn = 1;
            JoyLEDS[2].OnDuration = 1000;
            break;
          case 3 ://right
            wTrig.trackPlayPoly(108);
            JoyLEDS[3].TurnOn = 1;
            JoyLEDS[3].OnDuration = 1000;
            break;
        }
      }




    }
    ///----------------GAME ONE END----------------
    ///----------------------------------------------


    ///----------------GAME TWO START----------------
    ///-------------------Surprise------------------
    ///Catch the surface light, with noise.

    if (CurrentMenuControl == 1) {

      if (CurrentFindButton == 16) {
        //get new random with seed
        unsigned long seed = millis();
        randomSeed(seed);
        CurrentFindButton = random(16);
        //turn light on
        SurfaceLEDS[CurrentFindButton].TurnOn = 1;
      }

      //button pressed
      if ((ReturnButons.ControlBlock == 1) && (ReturnButons.State == CurrentFindButton)) {
        int oldbutton = CurrentFindButton;

        //pressbutton YAY!!!
        wTrig.trackPlayPoly(15);

        //light another
        unsigned long seed = millis();
        randomSeed(seed);
        CurrentFindButton = random(16);
        //turn light on
        SurfaceLEDS[CurrentFindButton].TurnOn = 1;

        if (CurrentFindButton != oldbutton) {
          SurfaceLEDS[oldbutton].TurnOn = 0;
          SurfaceLEDS[oldbutton].TurnOff = 1;
          SurfaceLEDS[oldbutton].OnDuration = 0;
        }

      }


    }



    ///----------------GAME TWO END----------------
    ///----------------------------------------------

    ///----------------GAME THREE Start----------------
    ///---------------------Sequencer----------------------
    if (CurrentMenuControl == 2) {
      //Turn Sequencer Loop on/off
      if (CurrentMenuControl == 2 && SequencerIsOn == 0 ) {
        SequencerIsOn = 1;
        SeqPreviousTick = millis();
      }

      //handle sequence input, mape surface press to note maps

      //check what mode we are in
      if (SeqMode == 0) {
        if (ReturnButons.ControlBlock == 1) { //main buttom press
          int SeqTempBut  = ReturnButons.State;
          if (SeqNotes[SeqTempBut] == 0) {
            SeqNotes[SeqTempBut] = 1;
          }
          else
          {
            SeqNotes[SeqTempBut] = 0;
          }
          SeqUpdateLeds();
        }
      }
      if (SeqMode == 1) {
        if (ReturnButons.ControlBlock == 1) { //main buttom press
          int SeqTempBut  = ReturnButons.State;
          if (SeqDrums[SeqTempBut] == 0) {
            SeqDrums[SeqTempBut] = 1;
          }
          else
          {
            SeqDrums[SeqTempBut] = 0;
          }
          SeqUpdateLeds();
        }
      }

      //change seq mode
      if (ReturnButons.ControlBlock == 3) {
        if (ReturnButons.CharPressed == '1') {
          SeqMode = 0;
          SeqUpdateLeds();
        }
        if (ReturnButons.CharPressed == 'R') {
          SeqMode = 1;
          SeqUpdateLeds();
        }
      }

      //change samplebanks
      //int SampleBank = 0;
      //int DrumBank =0;
      if (ReturnButons.ControlBlock == 2) {
        if (ReturnButons.State <= 3) {
          if (SeqMode == 0) {
            SampleBank = ReturnButons.State - 1;
          }
          if (SeqMode == 1) {
            DrumBank = ReturnButons.State - 1;
          }
        }
      }
      //implement Drum Banks - get drum samples !!!


      //tempo
      //Temp and control for sequencer
      int tempint = 0;
      if (ReturnButons.ControlBlock == 6) {
        Serial.println(ReturnButons.State);
        switch ( ReturnButons.State ) {
          case 0 ://up
            SeqMasterTempo = SeqMasterTempo + 10;
            if  (SeqMasterTempo >= 500) {
              SeqMasterTempo = 500;
            }
            tempint = int(SeqMasterTempo);
            display2.setBrightness(0);
            display2.showNumberDec(tempint, true);
            break;
          case 1 :
            SeqMasterTempo = SeqMasterTempo - 10;
            if  (SeqMasterTempo <= 50) {
              SeqMasterTempo = 50;
            }
            tempint = int(SeqMasterTempo);
            display2.setBrightness(0);
            display2.showNumberDec(tempint, true);

            break;
        }
      }





    }    ///----------------GAME THREE END----------------
    ///----------------------------------------------


    ///----------------GAME Four  Start----------------

    if (CurrentMenuControl == 4) {

      //Turn Pac Loop Loop on/off
      if (CurrentMenuControl == 4 && Pac_LoopOn  == 0 ) {
        Pac_LoopOn  = 1;
        Pac_TickMillis = millis();
      }
    }
    //int Pac_Speed = 1000;
    //int Pac_StartPos = 0;
    //int Pac_Direction = 0; //0 = left 1 = right, 2 = down, 3 = up
    //int Pac_GhostPosition = 0;
    //int Pac_WalkTick = 0; // 0/1 flipflop
    //int Pac_LoopOn = 0; // master Loop control
    //unsigned long Pac_TickMillis  =0;
    ///----------------GAME Four END----------------
    ///----------------------------------------------




    ///----------------GAME five Start----------------
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
    if (CurrentMenuControl == 5) {
      //decode input into action codes

      if (FM_GameON == 0 && ReturnButons.ControlBlock != 7) {
        //any button will start game
        //now start the music
        if (ReturnButons.ControlBlock == 3) {
          display2.setBrightness(0);
          display2.showNumberDec(0000, true);
          display.setBrightness(0);
          display.showNumberDec(0000, true);
          wTrig.trackPlayPoly(139);

          FM_TickMillis = millis();
          FM_GameON = 1;
          FM_GetNextAction();
        }
        //Reset Scores etc
      }
      else {
        //game is ON!!!!
        //joystick
        int FM_NewAction  = 99;
        if (ReturnButons.ControlBlock == 6) {
          switch (ReturnButons.State) {
            case 0 :
              FM_NewAction = 0;
              break;
            case 1 :
              FM_NewAction = 1;
              break;
            case 2 :
              FM_NewAction = 2;
              break;
            case 3 :
              FM_NewAction = 3;
              break;
          }
        }
        //left Right Buttons
        if (ReturnButons.ControlBlock == 3) {
          if  (ReturnButons.CharPressed == '1') {
            FM_NewAction = 4;
          }
          else
          {
            FM_NewAction = 5;
          }
        }
        //Toggle
        if (ReturnButons.ControlBlock == 4) {
          FM_NewAction = 6;
        }
        //switches
        if (ReturnButons.ControlBlock == 5) {
          FM_NewAction = 7;
        }
        // surface colors
        if (ReturnButons.ControlBlock == 1) {
          switch (ReturnButons.State) {
            case 0 :
              FM_NewAction = 8;
              break;
            case 1 :
              FM_NewAction = 8;
              break;
            case 2 :
              FM_NewAction = 8;
              break;
            case 3 :
              FM_NewAction = 8;
              break;
            case 4 :
              FM_NewAction = 9;
              break;
            case 5 :
              FM_NewAction = 9;
              break;
            case 6 :
              FM_NewAction = 9;
              break;
            case 7 :
              FM_NewAction = 9;
              break;
            case 8 :
              FM_NewAction = 10;
              break;
            case 9 :
              FM_NewAction = 10;
              break;
            case 10 :
              FM_NewAction = 10;
              break;
            case 11 :
              FM_NewAction = 10;
              break;
            case 12 :
              FM_NewAction = 11;
              break;
            case 13 :
              FM_NewAction = 11;
              break;
            case 14 :
              FM_NewAction = 11;
              break;
            case 15 :
              FM_NewAction = 11;
              break;

          }
        }

        //keypad decode
        if (ReturnButons.ControlBlock == 2) {
          if (FM_Advanced == 0) {
            FM_NewAction = 12;
          }
          else
          {
            //full numpad decode State
            switch (ReturnButons.State) {
              case 11 :
                FM_NewAction = 13;
                break;
              case 1 :
                FM_NewAction = 14;
                break;
              case 2 :
                FM_NewAction = 15;
                break;
              case 3 :
                FM_NewAction = 16;
                break;
              case 4 :
                FM_NewAction = 17;
                break;
              case 5 :
                FM_NewAction = 18;
                break;
              case 6 :
                FM_NewAction = 19;
                break;
              case 7 :
                FM_NewAction = 20;
                break;
              case 8 :
                FM_NewAction = 21;
                break;
              case 9 :
                FM_NewAction = 22;
                break;
            }
            if (FM_NextAction == 12) {
              FM_NewAction = 12; //check for generic check in advance mode
            }

          }

        }

        ///send action code to function
        if (FM_NewAction != 99) {
          FM_Check_Action(FM_NewAction);
        }

      }//this end if GAME IS ON BLOCK
    }
    ///----------------GAME five END----------------
  }

  ///----------------GAME Six Start ----------------
  if (CurrentMenuControl == 6) {
    //decode input into action codes

    if (ReturnButons.ControlBlock == 1) {
      int WSongtoPlay = 165 + ReturnButons.State;
      wTrig.stopAllTracks();
      wTrig.trackPlaySolo(WSongtoPlay);
    }

    if (ReturnButons.ControlBlock == 3) {
      wTrig.stopAllTracks();

    }

  }
  ///----------------GAME Six END----------------

  ///End Master Game Handlers







  //Easter egg and Admin mode Handler

  //exit easter mode
  if (ReturnButons.ControlBlock == 2 && Easter1On == 1) {
    if (ReturnButons.CharPressed ==  ExitEaster[ExitEasterSteps]) {
      //button matches current step
      ExitEasterSteps++;
    }
    else
    {
      //reset
      ExitEasterSteps = 0;
    }
    if (ExitEasterSteps == 2) {
      Easter1On = 0;
      EasterSteps = 0;
      ExitEasterSteps = 0;
      EasterEggExit();
    }

  }

  //enter easter mode
  if (ReturnButons.ControlBlock == 2 && Easter1On == 0) {
    if (ReturnButons.CharPressed ==  Easter1[EasterSteps]) {
      //button matches current step
      EasterSteps++;

    }
    else
    {
      //reset
      EasterSteps = 0;
    }
    if (EasterSteps == 6) {
      Easter1On = 1;
      EasterSteps = 0;
      ResetSurface();
      EasterEggStartup();
    }
  }
  //end Easter Egg

  //start Admin mode Handler

  //exit Admin Mode
  if (ReturnButons.ControlBlock == 2 && AdminMode == 1) {
    if (ReturnButons.CharPressed ==  ExitEaster[ExitAdminSteps]) {
      //button matches current step
      ExitAdminSteps++;
    }
    else
    {
      //reset
      ExitAdminSteps = 0;
    }
    if (ExitAdminSteps == 2) {
      AdminMode = 0;
      AdminSteps = 0;
      ExitAdminSteps = 0;
      AdminModeExit();
    }

  }

  //enter admin mode
  if (ReturnButons.ControlBlock == 2 &&  AdminMode == 0) {
    if (ReturnButons.CharPressed ==  Admin[AdminSteps]) {
      //button matches current step
      AdminSteps++;

    }
    else
    {
      //reset
      AdminSteps = 0;
    }
    if (AdminSteps == 6) {
      AdminMode = 1;
      AdminSteps = 0;
      ResetSurface();
      AdminModeStartup();
    }
  }
  //end admin Mode

}
