#include <Arduino.h>
#include <EncoderButton.h>
#include <PushButton.h>
#include <LiquidCrystal.h>
int kp = 50;

const int rs = 8, en = 7, d4 = A3, d5 = A4, d6 = A2, d7 = A1;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define sensorPin A0
#define fanPin 3
#define heaterPin 6
#define readswitchPin 5
#define led 13
#define encoderbuttonPin 4
#define zerocrossPin 2
#define encoderpina 9
#define encoderpinb 10

EncoderButton eb1(encoderpina, encoderpinb);
PushButton encbutton(encoderbuttonPin);
int mintime = 3000;
int maxtime = 8500;
int mintemp = 200;
int maxtemp = 450;
int temp = 350;
float avgtemp = 0;
int res = 100;
int rawtemp = 0;
int threshold = 20;
int sensorval = 0;
int pos = 0;
int fanspeed = 50;
int fanpower = 200;
int minspeed = 10;
int minpwm = 120;
int maxpwm = 255;
int error = 0;
int errormargin = 5;
int heaterpower = 0;
bool readswitch = false;
bool heaterstate = false;

bool issettingtemp = false;

void zerocross();
void lcdprint();
void onEb1Encoder(EncoderButton &eb)
{
  Serial.println(eb.position());
  pos += eb.increment();
  // lcd.clear();
}

void setup()
{
  pinMode(fanPin, OUTPUT);
  pinMode(heaterPin, OUTPUT);
  pinMode(readswitchPin, INPUT);
  pinMode(sensorPin, INPUT);
  pinMode(led, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(zerocrossPin), zerocross, RISING);
  encbutton.setActiveLogic(HIGH);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("HOT AIR STATION");
  lcd.setCursor(0, 1);
  lcd.print("By: Afnan Yusuf");
  delay(2000);
  lcd.clear();
  eb1.setEncoderHandler(onEb1Encoder);
}

void loop()
{
  eb1.update();
  encbutton.update();
  readswitch = digitalRead(readswitchPin);
  rawtemp = analogRead(sensorPin);
  if (rawtemp < 55)
  {
    rawtemp = 55;
  }
  if (rawtemp > 140)
  {
    rawtemp = 140;
  }
  sensorval = map(rawtemp, 55, 140, mintemp, maxtemp);
  fanpower = map(fanspeed, 0, 100, minpwm, maxpwm);
  // heaterpower = map(temp, mintemp, maxtemp, 8500, 1500);

  if (issettingtemp == true)
  {
    temp = pos * 5;
    if (temp > maxtemp)
    {
      temp = maxtemp;
      pos = maxtemp / 5;
    }
    if (temp < mintemp)
    {
      temp = mintemp;
      pos = mintemp / 5;
    }
  }
  else
  {
    fanspeed = pos * 5;
    if (fanspeed > 100)
    {
      fanspeed = 100;
      pos = 100 / 5;
    }
    if (fanspeed < minspeed)
    {
      fanspeed = minspeed;
      pos = minspeed / 5;
    }
  }

  if (encbutton.isClicked())
  {
    eb1.resetPosition();
    lcd.clear();
    if (issettingtemp == true)
    {
      issettingtemp = false;
      pos = fanspeed / 5;
    }
    else
    {
      issettingtemp = true;
      pos = temp / 5;
    }
  }
  if (readswitch == true || analogRead(sensorPin) > threshold)
  {
    analogWrite(fanPin, fanpower);
  }
  else
  {
    analogWrite(fanPin, 0);
  }

  
  if (readswitch == true)
  {
    error = temp - sensorval;
    if(error > errormargin){
      attachInterrupt(digitalPinToInterrupt(zerocrossPin), zerocross, RISING);
      heaterpower = (maxtime -(constrain(error * kp, mintime, maxtime)));
      heaterstate = true;

  }else{
      detachInterrupt(digitalPinToInterrupt(zerocrossPin));
      digitalWrite(heaterPin, LOW);
      heaterstate = false;
  }
  }else{
      detachInterrupt(digitalPinToInterrupt(zerocrossPin));
      digitalWrite(heaterPin, LOW);
      heaterstate = false;
  }

  lcdprint();
}
void zerocross()
{
  delayMicroseconds(heaterpower); // read AD1
  digitalWrite(heaterPin, HIGH);
  delayMicroseconds(50);
  digitalWrite(heaterPin, LOW);
}
void lcdprint()
{
  lcd.setCursor(0, 0);
  lcd.print("TEMP:");
  lcd.setCursor(5, 0);
  lcd.print(temp);
  lcd.setCursor(9, 0);
  lcd.print("FAN:");
  lcd.setCursor(13, 0);
  lcd.print(fanspeed);
  lcd.setCursor(0, 1);
  lcd.print("CTMP:");
  lcd.setCursor(5, 1);
  lcd.print(sensorval);
  lcd.setCursor(9, 1);
  lcd.print("HP:");
  lcd.setCursor(12, 1);
  lcd.print(analogRead(sensorPin));
  lcd.setCursor(15, 1);
  lcd.print("%");
}