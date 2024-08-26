#include "FlashTimer.h"

FlashTimer::FlashTimer(int pin, unsigned long longDelay, unsigned long doubleDelay)
    : buttonPin(pin), LONG_DELAY(longDelay), DOUBLE_DELAY(doubleDelay), BUTTONSTATE(true), LASTBUTTONSTATE(true),
      SINGLE_CLICK(0), DOUBLE_CLICK(0), LONG_CLICK(0), INDEX(0), POS(0), HIGH_TIMER(0), LOW_TIMER(0), 
      OFF_TIMER(0), TIMER(0), TIMER0(0), TIMER1(0), TIMER2(0), CURRENTSTATE(I), lastClick(NONE) {
    pinMode(buttonPin, INPUT_PULLUP);
}

void FlashTimer::update() {
    INDEX++;
    BUTTONSTATE = digitalRead(buttonPin);
    TIMER = millis();

    switch (CURRENTSTATE) {
    case I:
        POS = 0;
        if (BUTTONSTATE == LOW && LASTBUTTONSTATE == HIGH) {
            TIMER0 = TIMER;
            OFF_TIMER = TIMER - TIMER2;
            CURRENTSTATE = P;
        }
        break;

    case P:
        POS = 1;
        if ((TIMER - TIMER0) >= LONG_DELAY) {
            POS = 2;
        }
        if (BUTTONSTATE == HIGH) {
            TIMER1 = TIMER;
            LOW_TIMER = TIMER1 - TIMER0;

            if (LOW_TIMER >= LONG_DELAY) {
                LONG_CLICK++;
                lastClick = LONG;
                TIMER2 = TIMER;
                CURRENTSTATE = I;
            } else {
                CURRENTSTATE = W;
            }
        }
        break;

    case W:
        POS = 3;
        if (BUTTONSTATE == LOW && LASTBUTTONSTATE == HIGH) {
            HIGH_TIMER = TIMER - TIMER1;

            if (HIGH_TIMER <= DOUBLE_DELAY) {
                POS = 4;
                DOUBLE_CLICK++;
                lastClick = DOUBLE;
                TIMER2 = TIMER;
            } else {
                POS = 6;
                // Single click detected
                SINGLE_CLICK++;
                lastClick = SINGLE; // Set the last click type to SINGLE
                SINGLE_CLICK++;
                lastClick = SINGLE; // Set the last click type to SINGLE
            }

            CURRENTSTATE = I;
        } else if (BUTTONSTATE == HIGH && TIMER - TIMER1 > DOUBLE_DELAY) {
            POS = 5;
            SINGLE_CLICK++;
            lastClick = SINGLE;
            TIMER2 = TIMER;
            CURRENTSTATE = I;
        }
        break;
    }

    LASTBUTTONSTATE = BUTTONSTATE;
}

CLICKTYPE FlashTimer::getLastClick() const {
    return lastClick;
}

void FlashTimer::getTimers(unsigned long &pressDuration, unsigned long &doubleClickInterval, unsigned long &idleInterval) const {
    pressDuration = LOW_TIMER;
    doubleClickInterval = HIGH_TIMER;
    idleInterval = OFF_TIMER;
}

int FlashTimer::getButtonPin() const {
    return buttonPin;
}

bool FlashTimer::getButtonState() const {
    return BUTTONSTATE;
}

int FlashTimer::getIndex() const {
    return INDEX;
}

int FlashTimer::getPosition() const {
    return POS;
}

int FlashTimer::getSingleClicks() const {
    return SINGLE_CLICK;
}

int FlashTimer::getDoubleClicks() const {
    return DOUBLE_CLICK;
}

int FlashTimer::getLongClicks() const {
    return LONG_CLICK;
}

unsigned long FlashTimer::getHighTimer() const {
    return HIGH_TIMER;
}

unsigned long FlashTimer::getLowTimer() const {
    return LOW_TIMER;
}

unsigned long FlashTimer::getOffTimer() const {
    return OFF_TIMER;
}

unsigned long FlashTimer::getTimer() const {
    return TIMER;
}
