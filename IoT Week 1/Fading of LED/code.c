int leds[] = {11, 10, 9, 6, 5, 3};

void setup()
{
  for(int i = 0; i < 6; i++)
  {
    pinMode(leds[i], OUTPUT);
  }
}

void loop()
{
  for(int i = 0; i < 6; i++)
  {
    int repetitions;

    if(i % 2 == 0)
    {
      repetitions = 2;
    }
    else
    {
      repetitions = 1;
    }

    for(int j = 0; j < repetitions; j++)
    {
      // Fade in
      for(int b = 0; b <= 255; b++)
      {
        analogWrite(leds[i], b);
        delay(1);
      }

      // Fade out
      for(int b = 255; b >= 0; b--)
      {
        analogWrite(leds[i], b);
        delay(1);
      }
    }
  }
}
