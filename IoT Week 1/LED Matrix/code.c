int rows[4] = {2,3,4,5};
int cols[4] = {6,7,8,9};

byte G[4][4] =
{
  {1,1,1,0},
  {1,0,0,0},
  {1,0,1,1},
  {0,1,0,1}
};

void setup()
{
  for(int i=0;i<4;i++)
  {
    pinMode(rows[i], OUTPUT);
    pinMode(cols[i], OUTPUT);
  }
}

void displayPattern(byte pattern[4][4], int duration)
{
  unsigned long startTime = millis();

  while(millis() - startTime < duration)
  {
    for(int r=0;r<4;r++)
    {
      for(int c=0;c<4;c++)
      {
        if(pattern[r][c] == 1)
        {

          digitalWrite(rows[r], LOW);
          digitalWrite(cols[c], HIGH);

          delay(1);

          digitalWrite(rows[r], HIGH);
          digitalWrite(cols[c], LOW);
        }
      }
    }
  }
}

void loop()
{
  displayPattern(G, 1000);
}
