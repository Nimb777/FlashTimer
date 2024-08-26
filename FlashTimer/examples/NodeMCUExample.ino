#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>
#include "FlashTimer.h"

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 12, /* data=*/ 14, /* reset=*/ U8X8_PIN_NONE);

FlashTimer FlashTimer(0, 1000, 500); // GPIO 0 (D3), Long delay 1000ms, Double delay 500ms

void setup() {
    Serial.begin(115200);
    u8g2.begin();

    u8g2.clearBuffer();
    u8g2.drawFrame(0, 0, 128, 64);
    u8g2.setFont(u8g2_font_7x14B_tr);
    u8g2.setCursor(4, 13);
    u8g2.print("NodeMCU 0.96 OLED flash");
    u8g2.setCursor(4, 30);
    u8g2.print("Flash Button Click");
    u8g2.setCursor(4, 43);
    u8g2.print("Double and long");
    u8g2.setCursor(4, 57);
    u8g2.print("press counter:");

    u8g2.drawLine(0, 15, 128, 15);
    u8g2.drawLine(0, 16, 128, 16);

    u8g2.sendBuffer();
}

void loop() {
    FlashTimer.update();

    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_7x14B_tr);
    u8g2.drawStr(0, 10, "S:");
    u8g2.setCursor(16, 10);
    u8g2.print(FlashTimer.getSingleClicks());
    u8g2.drawStr(45, 10, "D:");
    u8g2.setCursor(61, 10);
    u8g2.print(FlashTimer.getDoubleClicks());
    u8g2.drawStr(90, 10, "L:");
    u8g2.setCursor(106, 10);
    u8g2.print(FlashTimer.getLongClicks());
    u8g2.drawLine(0, 15, 128, 15);
    u8g2.drawLine(0, 16, 128, 16);
    u8g2.drawStr(0, 31, "B:");
    u8g2.setCursor(16, 31);
    u8g2.print(FlashTimer.getButtonState());
    u8g2.drawStr(30, 31, "P:");
    u8g2.setCursor(46, 31);
    u8g2.print(FlashTimer.getPosition());
    u8g2.drawStr(61, 31, "I:");
    u8g2.setCursor(77, 31);
    u8g2.print(FlashTimer.getIndex());
    u8g2.drawStr(0, 47, "H:");
    u8g2.setCursor(16, 47);
    u8g2.print(FlashTimer.getHighTimer());
    u8g2.drawStr(45, 47, "T:");
    u8g2.setCursor(61, 47);
    u8g2.print(FlashTimer.getTimer());
    u8g2.drawStr(0, 62, "L:");
    u8g2.setCursor(16, 62);
    u8g2.print(FlashTimer.getLowTimer());
    u8g2.drawStr(50, 62, "O:");
    u8g2.setCursor(66, 62);
    u8g2.print(FlashTimer.getOffTimer());
    u8g2.sendBuffer();

    delay(50);
}