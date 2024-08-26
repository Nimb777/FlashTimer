#include <Arduino.h>
#include "FlashTimer.h"

FlashTimer flashTimer(0, 1000, 500); // Initialize with GPIO 0, long delay 1000ms, double delay 500ms

void setup() {
  Serial.begin(115200);
  pinMode(flashTimer.getButtonPin(), INPUT_PULLUP); // Ensure the pin is set to INPUT_PULLUP
}

void loop() {
  flashTimer.update(); // Update the state of the button

  // Example output for testing
  Serial.print("S:");
  Serial.print(flashTimer.getSingleClicks());
  Serial.print(" D:");
  Serial.print(flashTimer.getDoubleClicks());
  Serial.print(" L:");
  Serial.print(flashTimer.getLongClicks());
  Serial.print(" C:");
  switch (flashTimer.getLastClick()) {
    case SINGLE:
      Serial.print("S");
      break;
    case DOUBLE:
      Serial.print("D");
      break;
    case LONG:
      Serial.print("L");
      break;
    default:
      Serial.print("N");
      break;
  }

  // Display debug
  Serial.print(" B:");
  Serial.print(flashTimer.getButtonState());
  Serial.print(" P:");
  Serial.print(flashTimer.getPosition());
  Serial.print(" I:");
  Serial.print(flashTimer.getIndex());

  // Display LOW_TIMER, HIGH_TIMER, OFF_TIMER and TIMER
  unsigned long pressDuration, doubleClickInterval, idleInterval;
  flashTimer.getTimers(pressDuration, doubleClickInterval, idleInterval);

  Serial.print(" H:");
  Serial.print(doubleClickInterval);
  Serial.print(" L:");
  Serial.print(pressDuration);
  Serial.print(" O:");
  Serial.print(idleInterval);
  Serial.print(" T:");
  Serial.println(flashTimer.getTimer());

  delay(100); // Small delay to avoid excessive Serial output
}
