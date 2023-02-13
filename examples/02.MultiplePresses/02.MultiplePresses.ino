///
/// This code is written and maintained by TechnoBro03.
///
/// This example shows how to use the getNumPresses() method.
/// 
/// Detect single, double, and multiple presses and print to Serial Monitor.
///

#include <AdvancedButton.h>

#define BUTTONPIN 0

/// Create button object, on pin 0
AdvancedButton button(BUTTONPIN);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  /// Must be called first every loop
  button.update();

  /// Store number of consecutive presses.
  unsigned int t = button.getNumPresses();

  if(t == 1)
  {
    Serial.printf("Button was pressed once\n");
  }
  if (t == 2)
  {
    Serial.printf("Button was double pressed\n");
  }
  if (t > 2)
  {
    Serial.printf("Button was pressed %u times\n", t);
  }
}
