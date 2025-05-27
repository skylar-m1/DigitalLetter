// Arduino side - receives commands from rpi over serial and directly controls LEDs and message on 
// lcd screen
// Created by Skylar McDermott



#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int leds[] = {A0, A1, A2, A3, A4, A5, 6, 7, 8, 9};
String message = ""; // message to display
// functions
void waitForMessage();
void chaseLeds(int d=1000);
void messageReceived(int d=500);
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("hello, world!");
  for (int i = 0; i < 10; i++)
  {
    pinMode(leds[i], OUTPUT);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  //chaseLeds(100);
  waitForMessage();
}


void chaseLeds(int d=1000)
{
  for (int i = 0; i < 10; i++)
  {
    digitalWrite(leds[i], HIGH);
    delay(d);
    digitalWrite(leds[i], LOW);
  }
   for (int i = 10; i < 0; i--)
  {
    digitalWrite(leds[i], HIGH);
    delay(d);
    digitalWrite(leds[i], LOW);
  }
}
void messageReceived(int d=500)
{
   digitalWrite(leds[0], HIGH);
   digitalWrite(leds[9], HIGH);
   delay(d);
   digitalWrite(leds[0], LOW);
   digitalWrite(leds[9], LOW);
   delay(d);
   digitalWrite(leds[0], HIGH);
   digitalWrite(leds[9], HIGH);
   delay(d);
   digitalWrite(leds[0], LOW);
   digitalWrite(leds[9], LOW);
}


void waitForMessage()
{
  while (Serial.available() == 0) 
  {
    // idle led function goes here
    chaseLeds(100);
  }
  messageReceived();
  lcd.clear();
  message = Serial.readString();
  message.trim();
  lcd.print(message);

}
