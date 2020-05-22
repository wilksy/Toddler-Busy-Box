void Sequencer() {

  //is it time for a note change
  if (millis() - SeqPreviousTick >=  SeqMasterTempo) {
    SeqPreviousTick = millis();

    SeqCurrentStep++;

    if (SeqCurrentStep >= 4) {
      SeqCurrentStep = 0;
    }

    //process step lights
    for (int seqcnt = 0; seqcnt < 4; seqcnt++) {
      if (seqcnt == SeqCurrentStep) {
        SurfaceColLEDS[seqcnt].TurnOn = 1;
      }
      else
      {
        SurfaceColLEDS[seqcnt].TurnOff = 1;
      }
    }



    //Serial.println(SeqCurrentStep);

    ///process and play samples

    //NOTES!!

    //pepare sample bank startig point
    int SeqSamplePointer = 0;
    if (SampleBank == 0) {
      SeqSamplePointer = 72;
    }
    if (SampleBank == 1) {
      SeqSamplePointer = 76;
    }
    if (SampleBank == 2) {
      SeqSamplePointer = 80;
    }

    if (SeqNotes[SeqCurrentStep] == 1) {
      wTrig.trackPlayPoly(SeqSamplePointer);
    }
    if (SeqNotes[SeqCurrentStep + 4] == 1) {
      wTrig.trackPlayPoly(SeqSamplePointer - 1);
    }
    if (SeqNotes[SeqCurrentStep + 8] == 1) {
      wTrig.trackPlayPoly(SeqSamplePointer - 2);
    }
    if (SeqNotes[SeqCurrentStep + 12] == 1) {
      wTrig.trackPlayPoly(SeqSamplePointer - 3);
    }
    //drums
    if (SeqDrums[SeqCurrentStep] == 1) {
      wTrig.trackPlayPoly(65);
    }
    if (SeqDrums[SeqCurrentStep + 4] == 1) {
      wTrig.trackPlayPoly(66);
    }
    if (SeqDrums[SeqCurrentStep + 8] == 1) {
      wTrig.trackPlayPoly(67);
    }
    if (SeqDrums[SeqCurrentStep + 12] == 1) {
      wTrig.trackPlayPoly(68);
    }




  }

}

void SeqUpdateLeds() {

  if (SeqMode == 0) {
    for (int seqcnt = 0; seqcnt < 16; seqcnt++) {
      if (SeqNotes[seqcnt] == 1) {
        SurfaceLEDS[seqcnt].BrightnessOverideStep = 4;
        SurfaceLEDS[seqcnt].TurnOn = 1;
      }
      else
      {
        SurfaceLEDS[seqcnt].TurnOff = 1;
      }
    }
  }

  if (SeqMode == 1) {
    for (int seqcnt = 0; seqcnt < 16; seqcnt++) {
      if (SeqDrums[seqcnt] == 1) {
        SurfaceLEDS[seqcnt].BrightnessOverideStep = 4;
        SurfaceLEDS[seqcnt].TurnOn = 1;
      }
      else
      {
        SurfaceLEDS[seqcnt].TurnOff = 1;
      }
    }
  }

}
