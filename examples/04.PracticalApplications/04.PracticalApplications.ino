///
/// This code is written and maintained by TechnoBro03.
///
/// This example shows a more advanced usage of the button.
/// 
/// Detect different patterns of presses
///

#include <AdvancedButton.h>

#define BUTTONPIN 0

/// Create button object, on pin 0. countMode = CHANGE, defaultState = LOW, internalPullup = false, debounceDelay = 5ms, pressDelay = 500ms.
AdvancedButton button(BUTTONPIN, CHANGE, LOW, false, 5ul, 500ul);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  /// Must be called first every loop.
  button.update();

  //////////////////////////////
  /// Tap once, then press and hold for two seconds.
  //////////////////////////////

  doublePressAndHold();

  ////////////////////////////////
  /// Hold for two seconds then double tap.
  ////////////////////////////////

  holdThenDoubleTap();
}

void doublePressAndHold()
{
  if(button.getNumPresses() == 2)
  {
    if(button.getLongPress(2000, 3000, true))
    {
      Serial.println("Button was tapped, then pressed and held for at least two seconds");
      button.getNumPresses(true); /// Resets numPresses so this block only runs once.
    }
  }    
}


void holdThenDoubleTap()
{
  static unsigned long t = 0;
  if(button.getLongPress(2000, 5000, false))
  {
    t = millis();
  }
  if(button.getNumPresses() == 2 && millis() - t < 1250) /// 1250ms accounts for time after initial release, double tapping, and pressDelay.
  {
    Serial.println("Button was held for two seconds, then double tapped");    
    button.getNumPresses(true); /// Resets numPresses so this block only runs once.
  }
}
