const int LED = 9;
const int PHOTORESISTOR = A0;

void setup()
{
  pinMode(LED,OUTPUT);
  pinMode(PHOTORESISTOR,INPUT);
  Serial.begin(9600);
  digitalWrite(LED, LOW);
}

void loop()
{
  int PHOTO_VALUE= analogRead(PHOTORESISTOR);
  Serial.println(PHOTO_VALUE);
  
  if (PHOTO_VALUE < 300){
    digitalWrite(LED,HIGH);
    delay(1000);
  }
  
  else {
  digitalWrite(LED,LOW);
  delay(1000);
  }
    
}
