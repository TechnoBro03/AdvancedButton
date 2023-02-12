#pragma once

#include <Arduino.h>

class AdvancedButton {

    private:

        /**
         * User Defined Variables
         */
        int pin; // Input pin
        bool defaultState; // When not pressed, input pin is HIGH or LOW.
        int countMode; // When button is "toggled".
        unsigned long debounceTime; // Time delay to remove unwanted noise.
        unsigned long toggleDelay; // Time allowed between multiple toggles.

        /**
         * User accessable Variables (get)
         */
        unsigned int count; // Total number of toggles.
        unsigned int numPresses; // Number of consecutive toggles.
        bool currentState; // Current state of button, without debounce.
        bool currentDebounceState; // Current state of button, with debounce.
        unsigned long lengthPressed; // Length button has been, or was previously, pressed.

        /**
         * Internal
         */
        unsigned long lastTimeCountChanged;
        bool previousState;
        unsigned long lastTimeStateChanged;
        bool previousDebounceState;
        unsigned long currentTime;
        unsigned long timePressed;
        unsigned long timeReleased;
        void press();

    public:

        /**
         * Constructor.
         *
         * @param pin Arduino pin connected to button.
         * @param defaultState Logic level of button when not pressed (HIGH or LOW).
         * @param pullup Usage of internal pullup resistor.
         * @param countMode When the button is "toggled." Button state, NOT logic level; pressed / unpressed. (FALLING, RISING, CHANGE).
         * @param debounceTime Time delay to remove unwanted noise.
         * @param toggleDelay Time allowed between consecutive toggles.
         */
        AdvancedButton(int pin, bool defaultState = HIGH, bool pullup = true, int countMode = RISING, unsigned long debounceTime = 10ul, unsigned long toggleDelay = 50ul);

        /**
         * Returns current state of button.
         *
         * @return true if pressed, false otherwise.
         */
        bool getState();

        /**
         * Returns current state of button, with debounce.
         *
         * @return true if pressed, false otherwise.
         */
        bool getDebounceState();

        /**
         * Returns total number of times button has been toggled.
         *
         * @param resetCount If true, after calling this function, count is reset.
         *
         * @return number of times toggled.
         */
        unsigned int getCount(bool resetCount = false);

        /**
         * Returns number of consecutive toggles.
         *
         * A consecutive toggle is any time a toggle (countMode) occurs within toggleDelay ms of the previous.
         *
         * @return number of consecutive toggles. If 0, not enough time has passed (toggleDelay)
         *   to determine if toggling action has finished.
         */
        unsigned int getMultiPress();

         /**
         * Returns length button has been, or was previously, pressed.
         *
         * @param resetLengthPressed If true, after calling this function, lengthPressed is reset.
         *
         * @return Length pressed. If button is still being pressed, the elapsed time pressed is returned.
         */
        unsigned long getLengthPressed(bool resetLengthPressed = true);

        /**
         * Determines if length pressed falls within given time interval.
         *
         * @param min Minimun time button must be pressed.
         * @param max Maximum time button can be pressed.
         * @param hold If false, button must be released to return true. If true, button must be pressed to return true.
         *
         * @return true if length falls within time interval, false otherwise.
         */
        bool getLongPress(unsigned long min, unsigned long max, bool hold = false);
        
        /**
         * Must be called to use any method other than getState().
         */
        void update();
};
