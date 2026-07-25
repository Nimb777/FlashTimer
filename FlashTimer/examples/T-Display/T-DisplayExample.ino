#include <Arduino.h>
#include "FlashTimer.h"

// T-Display (ESP32 with small display) - using GPIO35 as button pin
FlashTimer flashTimer(35, 1000, 500);

void setup() {
  Serial.begin(115200);
  pinMode(flashTimer.getButtonPin(), INPUT_PULLUP);
  delay(1000);
  Serial.println("\nT-Display FlashTimer Example");
}

void loop() {
  flashTimer.update();

  Serial.print("S:");
  Serial.print(flashTimer.getSingleClicks());
  Serial.print(" D:");
  Serial.print(flashTimer.getDoubleClicks());
  Serial.print(" L:");
  Serial.print(flashTimer.getLongClicks());
  Serial.print(" C:");
  switch (flashTimer.getLastClick()) {
    case ClickType::SINGLE:
      Serial.print("S");
      break;
    case ClickType::DOUBLE:
      Serial.print("D");
      break;
    case ClickType::LONG:
      Serial.print("L");
      break;
    default:
      Serial.print("N");
      break;
  }

  Serial.print(" B:");
  Serial.print(flashTimer.getButtonState());
  Serial.print(" P:");
  Serial.print(flashTimer.getPosition());

  unsigned long pressDuration, doubleClickInterval, idleInterval;
  flashTimer.getTimers(pressDuration, doubleClickInterval, idleInterval);

  Serial.print(" H:");
  Serial.print(doubleClickInterval);
  Serial.print(" L:");
  Serial.print(pressDuration);
  Serial.println();

  delay(100);
}
