#include "Arduino.h"
#include "AdvancedButton.h"

unsigned int numPresses = 0u;
unsigned long lastTimeCountChanged = 0ul;
unsigned long timePressed = 0ul;
unsigned long timeReleased = 0ul;
unsigned long lengthPressed = 0ul;
AdvancedButton::AdvancedButton(int pin, bool defaultState = HIGH, bool pullup = true, int countMode = RISING, unsigned long debounceTime = 10ul, unsigned long toggleDelay = 50ul)
{
    this->pin = pin;
    this->defaultState = pullup ? HIGH : defaultState;
    this->countMode = countMode;
    this->debounceTime = debounceTime;
    this->toggleDelay = toggleDelay;
    pinMode(pin, pullup ? INPUT_PULLUP : INPUT);

    currentState = getState();
    previousState = currentState;
    previousDebounceState = currentState;
    currentDebounceState = currentState;

    lastTimeStateChanged = millis();
}

void AdvancedButton::press()
{
  count++;

  if(currentTime - lastTimeCountChanged < toggleDelay)
  {
    numPresses++;
  }
  else
  {
    numPresses = 1;
  }
  lastTimeCountChanged = currentTime;
}

bool AdvancedButton::getState() { return defaultState ? !digitalRead(pin) : digitalRead(pin); }
bool AdvancedButton::getDebounceState() { return currentDebounceState; }

unsigned int AdvancedButton::getCount(bool resetCount = false)
{
  unsigned int value = count;
  if(resetCount) {count = 0;}
  return value;
}

unsigned int AdvancedButton::getMultiPress()
{
  if(currentTime - lastTimeCountChanged > toggleDelay)
  {
    return numPresses;
  }
  else
  {
    return 0;
  }
}

unsigned long AdvancedButton::getLengthPressed(bool resetLengthPressed = true)
{
    unsigned int value = currentDebounceState ? (currentTime - timePressed) : lengthPressed;
    if(resetLengthPressed) {lengthPressed = 0;}
    return value;
}

bool AdvancedButton::getLongPress(unsigned long min, unsigned long max, bool hold = false)
{
  if(!(getDebounceState()^hold))
  {
    unsigned long l = getLengthPressed(false);
    if(l > min && l < max)
    {
      return true;
    }
  }
    return false;
  }

void AdvancedButton::update()
{
    currentState = getState();
    currentTime = millis();

    if(currentState != previousState)
    {
        previousState = currentState;
        lastTimeStateChanged = currentTime;
    }

    if(debounceTime < (currentTime - lastTimeStateChanged))
    {
        previousDebounceState = currentDebounceState;
        currentDebounceState = currentState;
    }

    if(currentDebounceState == true && previousDebounceState == false)
    {
        timePressed = currentTime;
        lengthPressed = 0;

        if(countMode == RISING || countMode == CHANGE)
        {
          press();
        }
    }

    if(currentDebounceState == false && previousDebounceState == true)
    {
        timeReleased = currentTime;
        lengthPressed = timeReleased - timePressed;

        if(countMode == FALLING || countMode == CHANGE)
        {
          press();
        }
    }
}
