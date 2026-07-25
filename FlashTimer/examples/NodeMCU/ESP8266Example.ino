#include <Arduino.h>
#include "FlashTimer.h"

// ESP8266 (NodeMCU, WeMos D1) - using GPIO0 (D3) as button pin
FlashTimer flashTimer(0, 1000, 500);

void setup() {
  Serial.begin(115200);
  delay(500);
  pinMode(flashTimer.getButtonPin(), INPUT_PULLUP);
  Serial.println("\nNodeMCU (ESP8266) FlashTimer Example");
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
