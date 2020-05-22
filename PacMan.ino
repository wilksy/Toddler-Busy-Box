void PacManLoop() {
  //Serial.println("in");
  //deal with pacman loop sounds
  if (millis() - Pac_TickMillis >=  Pac_Speed) {
    Pac_TickMillis = millis();
    if (Pac_WalkTick == 0) {
      Pac_WalkTick = 1;
      wTrig.trackPlayPoly(98);
    }
    else
    {
      Pac_WalkTick = 0;
      wTrig.trackPlayPoly(99);
    }

  }

  //int Pac_Speed = 1000;
  //int Pac_StartPos = 0;
  //int Pac_Direction = 0; //0 = left 1 = right, 2 = down, 3 = up
  //int Pac_GhostPosition = 0;
  //int Pac_WalkTick = 0; // 0/1 flipflop
  //int Pac_LoopOn = 0; // master Loop control
  //unsigned long Pac_TickMillis  =0;


}
