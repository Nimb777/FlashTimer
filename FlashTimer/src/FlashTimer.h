#ifndef FLASH_TIMER_H

#define FLASH_TIMER_H

#include <Arduino.h>

enum CLICKTYPE { NONE, SINGLE, DOUBLE, LONG };
enum BUTTONSTATUS { I, P, W };

class FlashTimer {
public:
    FlashTimer(int pin, unsigned long longDelay, unsigned long doubleDelay);

    void update();
    CLICKTYPE getLastClick() const;
    void getTimers(unsigned long &pressDuration, unsigned long &doubleClickInterval, unsigned long &idleInterval) const;

    bool getButtonState() const; // Getter for BUTTONSTATE
    int getButtonPin() const; // Getter for buttonPin
    int getIndex() const;
    int getPosition() const;
    int getSingleClicks() const;
    int getDoubleClicks() const;
    int getLongClicks() const;
    unsigned long getHighTimer() const;
    unsigned long getLowTimer() const;
    unsigned long getOffTimer() const;
    unsigned long getTimer() const;

private:
    const int buttonPin;
    const unsigned long LONG_DELAY;
    const unsigned long DOUBLE_DELAY;

    bool BUTTONSTATE;
    bool LASTBUTTONSTATE;
    int SINGLE_CLICK;
    int DOUBLE_CLICK;
    int LONG_CLICK;
    int INDEX;
    int POS;

    unsigned long HIGH_TIMER;
    unsigned long LOW_TIMER;
    unsigned long OFF_TIMER;
    unsigned long TIMER;
    unsigned long TIMER0;
    unsigned long TIMER1;
    unsigned long TIMER2;

    BUTTONSTATUS CURRENTSTATE;
    CLICKTYPE lastClick;
};

#endif // FLASH_TIMER_H
