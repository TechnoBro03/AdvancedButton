///
/// This code is written and maintained by TechnoBro03.
///
/// This header file serves as the detailed documentation
///     for the AdvancedButton library.
///

#pragma once

#include <Arduino.h>

class AdvancedButton {

    private:

        ///
        /// User Defined Variables
        ///
        int pin;
        bool defaultState;
        int signalMode;
        unsigned long debounceDelay;
        unsigned long signalDelay;
        ///
        /// User Accessible Variables
        ///
        unsigned int count;
        unsigned int numPresses;
        bool currentState;
        bool currentDebounceState;
        unsigned long lengthPressed;
        ///
        /// Internal
        ///
        bool previousState;
        unsigned long lastTimeStateChanged;
        bool previousDebounceState;
        unsigned long currentTime;
        unsigned long timePressed;
        unsigned long timeReleased;
        unsigned long timeSignaled;
        void signal();

    public:

        ///
        /// Constructor.
        ///
        /// \param pin Arduino pin connected to button.
        /// \param defaultState Logic level of button when not pressed (HIGH or LOW).
        /// \param pullup Usage of internal pull-up resistor.
        /// \param signalMode When to increment count and numPresses. Change in Button state (pressed or unpressed), NOT logic level. (FALLING, RISING, CHANGE).
        /// \param debounceDelay Time delay to remove ripple signal.
        /// \param signalDelay Time allowed between consecutive signals.
        ///
        AdvancedButton(int pin, int signalMode = RISING, bool defaultState = HIGH, bool internalPullup = true, unsigned long debounceDelay = 10ul, unsigned long signalDelay = 250ul);

        ///
        /// Returns current state of button.
        ///
        /// \return true if pressed, false otherwise.
        ///
        bool getState();

        ///
        /// Returns current state of button, with debounce.
        ///
        /// \return true if pressed, false otherwise.
        ///
        bool getDebounceState();

        ///
        /// Returns total number of times button has been signaled.
        ///
        /// \param resetCount If true, count is set to 0.
        ///
        /// \return number of times toggled.
        ///
        unsigned int getCount(bool resetCount = false);

        ///
        /// Returns number of consecutive singals (signalMode).
        ///
        /// A consecutive signal is any time a signal occurs within 'signalDelay'ms of the previous.
        ///
        /// \param resetNumPresses If true, and a value other than 0 is returned, numPresses is set to 0.
        ///
        /// \return Number of presses. 0 is returned if the button is still being pressed repeatedly
        ///     ('signalDelay'ms need to pass without a press)
        ///
        unsigned int getNumPresses(bool resetNumPresses = false);

        ///
        /// Returns length button has been, or was previously, pressed.
        ///
        /// \param resetLengthPressed If true, lengthPressed is set to 0.
        ///
        /// \return Length pressed. If button is still being pressed, the elapsed time pressed is returned.
        ///
        unsigned long getLengthPressed(bool resetLengthPressed = false);

        ///
        /// Determines if the button was pressed for a given length of time.
        ///
        /// \param min Minimum time button must be pressed.
        /// \param max Maximum time button can be pressed.
        /// \param pressed If false, button must NOT be pressed to return true. If true, button must be pressed to return true.
        /// \param resetLongPress If true, and this function returns true, lengthPressed is set to 0 (next call will return false unless button is pressed again).
        ///
        /// \return true if length falls within the given time interval, false otherwise.
        ///
        bool getLongPress(unsigned long min, unsigned long max, bool pressed = false, bool resetLongPress = true);
        
        ///
        /// Must be called first to use any method other than getState().
        ///
        void update();
};
