///
/// This code is written and maintained by TechnoBro03.
///

#include <Arduino.h>
#include <AdvancedButton.h>

unsigned int numPresses = 0u;
unsigned long timePressed = 0ul;
unsigned long timeReleased = 0ul;
unsigned long lengthPressed = 0ul;
AdvancedButton::AdvancedButton(int pin, int countMode, bool defaultState, bool internalPullup, unsigned long debounceDelay, unsigned long pressDelay)
{
    this->pin = pin;
    this->defaultState = internalPullup ? HIGH : defaultState;
    this->countMode = countMode;
    this->debounceDelay = debounceDelay;
    this->pressDelay = pressDelay;
    pinMode(pin, internalPullup ? INPUT_PULLUP : INPUT);

    currentState = getState();
    previousState = currentState;
    previousDebounceState = currentState;
    currentDebounceState = currentState;

    lastTimeStateChanged = millis();
}

bool AdvancedButton::getState() { return defaultState ? !digitalRead(pin) : digitalRead(pin); }
bool AdvancedButton::getDebounceState() { return currentDebounceState; }

unsigned int AdvancedButton::getCount(bool resetCount)
{
  unsigned int value = count;
  if(resetCount) {count = 0;}
  return value;
}

unsigned int AdvancedButton::getNumPresses(bool resetNumPresses)
{
  /// Wait to make sure all presses are finished.
  if(currentTime - timePressed > pressDelay)
  {
    unsigned int value = numPresses;
    if(resetNumPresses) {numPresses = 0;}
    return value;
  }
  return 0;
}

unsigned long AdvancedButton::getLengthPressed(bool resetLengthPressed)
{
    unsigned int value = currentDebounceState ? (currentTime - timePressed) : lengthPressed;
    if(resetLengthPressed) {lengthPressed = 0;}
    return value;
}

bool AdvancedButton::getLongPress(unsigned long min, unsigned long max, bool pressed, bool resetLongPress)
{
  if(!(getDebounceState()^pressed))
  {
    unsigned long l = getLengthPressed();
    if(min < l && l <= max)
    {
      getLengthPressed(resetLongPress);
      return true;
    }
  }
    return false;
  }

void AdvancedButton::update()
{
    currentState = getState();
    currentTime = millis();

    /// Check state change.
    if(currentState != previousState)
    {
        previousState = currentState;
        lastTimeStateChanged = currentTime;
    }

    /// Change debounce state.
    if(debounceDelay < (currentTime - lastTimeStateChanged))
    {
        previousDebounceState = currentDebounceState;
        currentDebounceState = currentState;
    }

    /// If button is RISING.
    if(currentDebounceState == true && previousDebounceState == false)
    {
        if(countMode == RISING || countMode == CHANGE)
        {
          count++;
        }

        if(currentTime - timePressed < pressDelay)
        {
          numPresses++;
        }
        else
        {
          numPresses = 1;
        }
        timePressed = currentTime;
        lengthPressed = 0;
    }

    /// If button is FALLING.
    if(currentDebounceState == false && previousDebounceState == true)
    {
        timeReleased = currentTime;
        lengthPressed = timeReleased - timePressed;

        if(countMode == FALLING || countMode == CHANGE)
        {
          count++;
        }
    }
}
