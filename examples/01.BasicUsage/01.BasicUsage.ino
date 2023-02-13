///
/// This code is written and maintained by TechnoBro03.
///
/// This example shows basic usage of the library.
/// 
/// State, Debounce State, and Count are printed to Serial Monitor.
///

#include <AdvancedButton.h>

#define BUTTONPIN 0

/// Create AdvancedButton object, on pin 0
AdvancedButton button(BUTTONPIN);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  /// Must be called first every loop
  button.update();
  
  bool state = button.getState();
  bool debounceState = button.getDebounceState();
  unsigned int count = button.getCount();

  Serial.printf("State: %u. Debounce State: %u. Count: %u\n", state, debounceState, count);
}
