#ifndef FLASH_TIMER_H

#define FLASH_TIMER_H

#include <Arduino.h>

/**
 * Click types reported by the library.
 */
enum class ClickType : uint8_t { NONE, SINGLE, DOUBLE, LONG };

/**
 * Internal button-state machine states:
 *  I - idle (waiting for press)
 *  P - pressed (measuring press duration)
 *  W - wait (after release; waiting for possible double-click)
 */
enum class ButtonStatus : uint8_t { I, P, W };

/**
 * FlashTimer
 * Small helper to detect single, double and long presses from a flash/button pin.
 *
 * Notes about single-click accounting:
 * - The implementation intentionally performs a double increment of the
 *   single-click counter in one of the W-state branches as a timing
 *   fail-safe. Because the code checks for a possible double-click before
 *   finalizing a single click, a second press that arrives during the
 *   execution/window timing could otherwise be missed. The double-increment
 *   preserves the user's click when loop/timing races occur. See
 *   FlashTimer.cpp for an inline explanation next to the W-state logic.
 */
class FlashTimer {
public:
    /**
     * Construct a FlashTimer tied to 'pin'.
     * longDelay: threshold (ms) to consider a press a LONG click.
     * doubleDelay: maximum interval (ms) between presses to count as DOUBLE.
     */
    FlashTimer(int pin, unsigned long longDelay, unsigned long doubleDelay);

    /** Run the state machine; call frequently from loop(). */
    void update();

    /** Return the last detected click type (NONE, SINGLE, DOUBLE, LONG). */
    ClickType getLastClick() const;

    /**
     * Retrieve timing diagnostics:
     * pressDuration  - duration of the last press (ms)
     * doubleClickInterval - measured interval used for double-click logic (ms)
     * idleInterval - time since last activity (ms)
     */
    void getTimers(unsigned long &pressDuration, unsigned long &doubleClickInterval, unsigned long &idleInterval) const;

    /** Return the raw button state (digitalRead result stored as bool). */
    bool getButtonState() const; // Getter for BUTTONSTATE

    /** Return the configured button pin. */
    int getButtonPin() const; // Getter for buttonPin

    int getIndex() const;
    int getPosition() const;

    /**
     * Number of single-clicks detected. Note: due to the intentional
     * timing fail-safe, a single detection path may increment this counter
     * by two to avoid losing a click during tight timing windows.
     */
    int getSingleClicks() const;

    int getDoubleClicks() const;
    int getLongClicks() const;
    unsigned long getHighTimer() const;
    unsigned long getLowTimer() const;
    unsigned long getOffTimer() const;
    unsigned long getTimer() const;

private:
    const int m_buttonPin;
    const unsigned long m_longDelay;
    const unsigned long m_doubleDelay;

    bool m_buttonState;
    bool m_lastButtonState;
    int m_singleClicks;
    int m_doubleClicks;
    int m_longClicks;
    int m_index;
    int m_pos;

    unsigned long m_highTimer;
    unsigned long m_lowTimer;
    unsigned long m_offTimer;
    unsigned long m_timer;
    unsigned long m_timer0;
    unsigned long m_timer1;
    unsigned long m_timer2;

    ButtonStatus m_currentState;
    ClickType lastClick;
};

#endif // FLASH_TIMER_H
