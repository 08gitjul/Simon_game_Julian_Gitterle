#include <Arduino.h>
#include "helper.h"
#define TASTER1 5
#define TASTER2 4
#define TASTER3 3
#define TASTER4 2
#define LED1 6 // Rot
#define LED2 7 // Gelb
#define LED3 8 // Grün
#define LED4 9 // Blau
#define RANDOM_PIN A0
#define DB_TIME 20
#define LONGPRESS_TIME 1000

uint8_t led_list[4] = {LED1, LED2, LED3, LED4};
uint8_t button_list[4] = {TASTER1, TASTER2, TASTER3, TASTER4};
bool flanken_list[4];
uint8_t press_order[100];

struct game;
game settings1;

struct lamps;
lamps led;

void setup()
{
  Serial.begin(57600);
  pinMode(TASTER1, INPUT);
  pinMode(TASTER2, INPUT);
  pinMode(TASTER3, INPUT);
  pinMode(TASTER4, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  randomSeed(analogRead(RANDOM_PIN));

  for (int i = 0; i < 100; i++)
  {
    press_order[i] = random(0, 4);
  }
  Serial.println("Start");
  settings1.init(button_list, DB_TIME, press_order);
  led.init(led_list, press_order, settings1.pressed_right);
}

void loop()
{
  // Serial.print("\r");
  // Serial.print(digitalRead(TASTER1));
  // Serial.print(digitalRead(TASTER2));
  // Serial.print(digitalRead(TASTER3));
  // Serial.print(digitalRead(TASTER4));
  // digitalWrite(LED1, HIGH);
  // digitalWrite(LED2, HIGH);
  // digitalWrite(LED3, HIGH);
  // digitalWrite(LED4, HIGH);
  led.poll();
  settings1.poll();
}
