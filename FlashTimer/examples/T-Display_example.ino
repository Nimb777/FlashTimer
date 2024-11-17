
#include <Arduino.h>
#include <TFT_eSPI.h>
#include "FlashTimer.h"
#include <User_Setups/Setup25_TTGO_T_Display.h>

//#include <User_Setups/Setup137_LilyGo_TDisplay_RP2040.h>  // Setup file for Lilygo T-Display RP2040 (ST7789 on SPI bus with 135x240 TFT)

TFT_eSPI tft = TFT_eSPI(); // Create an instance of the TFT_eSPI class

FlashTimer FlashTimer(0, 1000, 500); // GPIO 0 (D3), Long delay 1000ms, Double delay 500ms

void setup() {
    Serial.begin(115200);
    Serial.println("Setup started");
    tft.init();
    tft.setRotation(3); // Adjust rotation as needed

    tft.fillScreen(TFT_RED); // Fill screen with red color
    delay(100); // Wait for 2 seconds
    tft.fillScreen(TFT_GREEN); // Fill screen with green color
    delay(100); // Wait for 2 seconds
    tft.fillScreen(TFT_BLUE); // Fill screen with blue color
    delay(100); // Wait for 2 seconds
    tft.fillScreen(TFT_WHITE); // Fill screen with white color

    tft.drawRect(0, 0, 240, 135, TFT_BLUE);
    tft.setTextColor(TFT_PURPLE, TFT_WHITE);
    tft.setTextSize(3);
    tft.setCursor(10, 10);
    tft.print("FlashTimer");
    tft.setCursor(60, 98);
    tft.print("By Nimb777");
    delay(2000); // Wait for 2 seconds
    tft.fillScreen(TFT_BLACK); // Fill screen with black color
    tft.setTextColor(TFT_PURPLE, TFT_BLACK);

    Serial.println("Setup completed");
}

void loop() {
    FlashTimer.update();

    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(3);
    tft.setCursor(0, 0);
    tft.print("S:");
    tft.print(FlashTimer.getSingleClicks());
    tft.print(" D:");
    tft.print(FlashTimer.getDoubleClicks());
    tft.print(" L:");
    tft.print(FlashTimer.getLongClicks());
    tft.setCursor(0, 27);
    tft.print("I:");
    tft.print(FlashTimer.getIndex());
    tft.print(" B:");
    tft.print(FlashTimer.getButtonState());
    tft.setCursor(0, 55);
    tft.print("H:");
    tft.print(FlashTimer.getHighTimer());
    tft.print(" L:");
    tft.print(FlashTimer.getLowTimer());
    tft.print(" P:");
    tft.print(FlashTimer.getPosition());
    tft.setCursor(0, 83);
    tft.print("O:");
    tft.print(FlashTimer.getOffTimer());
    tft.setCursor(0, 111);
    tft.print("T:");
    tft.print(FlashTimer.getTimer());

    delay(20);
    Serial.println("Loop running");
}