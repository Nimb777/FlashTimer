#include <Arduino.h>
#include "FlashTimer.h"

// Arduino (ATmega328P, Uno, Nano) - using digital pin 2 (INT0)
FlashTimer flashTimer(2, 1000, 500);

void setup() {
  Serial.begin(9600); // Arduino Uno uses 9600 by default
  pinMode(flashTimer.getButtonPin(), INPUT_PULLUP);
  Serial.println(F("Arduino FlashTimer Example"));
}

void loop() {
  flashTimer.update();

  Serial.print(F("S:"));
  Serial.print(flashTimer.getSingleClicks());
  Serial.print(F(" D:"));
  Serial.print(flashTimer.getDoubleClicks());
  Serial.print(F(" L:"));
  Serial.print(flashTimer.getLongClicks());
  Serial.print(F(" C:"));
  switch (flashTimer.getLastClick()) {
    case ClickType::SINGLE:
      Serial.print(F("S"));
      break;
    case ClickType::DOUBLE:
      Serial.print(F("D"));
      break;
    case ClickType::LONG:
      Serial.print(F("L"));
      break;
    default:
      Serial.print(F("N"));
      break;
  }

  Serial.print(F(" B:"));
  Serial.print(flashTimer.getButtonState());
  Serial.print(F(" P:"));
  Serial.print(flashTimer.getPosition());

  unsigned long pressDuration, doubleClickInterval, idleInterval;
  flashTimer.getTimers(pressDuration, doubleClickInterval, idleInterval);

  Serial.print(F(" H:"));
  Serial.print(doubleClickInterval);
  Serial.print(F(" L:"));
  Serial.print(pressDuration);
  Serial.println();

  delay(100);
}
