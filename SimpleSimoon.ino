void SimonGameLoop () {

  //const int SS_MAX_LEVEL = 100;
  //int SS_sequence[SS_MAX_LEVEL];
  //int SS_your_sequence[SS_MAX_LEVEL];
  //int SS_level = 1;
  //int SS_velocity = 1000;


  if (SS_level == 1)
    SS_generate_sequence();//generate a sequence;

  if (SS_level != 1) //If start button is pressed or you're winning //digitalRead(A4) == LOW || SS_level != 1
  {
    //SS_show_sequence();    //show the sequence
    //SS_get_sequence();     //wait for your sequence
  }
}

void SS_generate_sequence() // Make the random sequence for level
{
  randomSeed(millis());

  for (int i = 0; i < SS_MAX_LEVEL; i++)
  {
    SS_sequence[i] = random(2, 6);
  }
}
