#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x26, 16, 2);

Servo gateServo;

// Pins
const int buttonOn = 2;
const int buttonOff = 3;

const int buzzerPin = 4;

const int redPin = 5;
const int greenPin = 6;
const int bluePin = 7;

const int statusLed = 8;

const int servoPin = 9;

const int trigPin = 10;
const int echoPin = 11;

const int alarmLed = 13;

const int potPin = A0;
const int ldrPin = A1;
const int tempPin = A2;

bool systemEnabled = true;

void setup()
{
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("SMART HOME");
  delay(2000);

  pinMode(buttonOn, INPUT_PULLUP);
  pinMode(buttonOff, INPUT_PULLUP);

  pinMode(buzzerPin, OUTPUT);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(statusLed, OUTPUT);
  pinMode(alarmLed, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  gateServo.attach(servoPin);

  lcd.clear();
}

void loop()
{
  // ON Button
  if(digitalRead(buttonOn) == LOW)
  {
    systemEnabled = true;
    delay(200);
  }

  // OFF Button
  if(digitalRead(buttonOff) == LOW)
  {
    systemEnabled = false;
    delay(200);
  }

  if(!systemEnabled)
  {
    digitalWrite(statusLed, LOW);
    digitalWrite(alarmLed, LOW);
    digitalWrite(buzzerPin, LOW);

    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 255);

    lcd.setCursor(0,0);
    lcd.print("SYSTEM OFF     ");
    lcd.setCursor(0,1);
    lcd.print("Press ON Btn   ");

    return;
  }

  digitalWrite(statusLed, HIGH);

  // Potentiometer
  int potValue = analogRead(potPin);
  int servoAngle = map(potValue, 0, 1023, 0, 180);

  gateServo.write(servoAngle);

  // LDR
  int lightValue = analogRead(ldrPin);

  // TMP36 Temperature
  int sensorValue = analogRead(tempPin);

  float voltage = sensorValue * (5.0 / 1023.0);

  float temperature = (voltage - 0.5) * 100.0;

  // Ultrasonic
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  float distance = duration * 0.034 / 2.0;

  bool alarm = false;

  // Alarm Conditions
  if(temperature > 35)
  {
    alarm = true;
  }

  if(distance < 20)
  {
    alarm = true;
  }

  // RGB + Alarm Logic
  if(alarm)
  {
    analogWrite(redPin, 255);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);

    digitalWrite(buzzerPin, HIGH);
    digitalWrite(alarmLed, HIGH);
  }
  else
  {
    analogWrite(redPin, 0);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 0);

    digitalWrite(buzzerPin, LOW);
    digitalWrite(alarmLed, LOW);
  }

  // LCD Display
  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.print((int)temperature);
  lcd.print("C D:");
  lcd.print((int)distance);
  lcd.print("   ");

  lcd.setCursor(0,1);
  lcd.print("L:");
  lcd.print(lightValue);
  lcd.print(" S:");
  lcd.print(servoAngle);
  lcd.print("   ");

  // Serial Monitor
  Serial.print("Temp: ");
  Serial.print(temperature);

  Serial.print(" Light: ");
  Serial.print(lightValue);

  Serial.print(" Distance: ");
  Serial.print(distance);

  Serial.print(" Servo: ");
  Serial.println(servoAngle);

  delay(300);
}
