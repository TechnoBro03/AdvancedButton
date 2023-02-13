///
/// This code is written and maintained by TechnoBro03.
///
/// This example shows how to use the detect presses of diffent lengths.
/// 
/// Detect short and long presses, as well as hold detection.
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

  /// First method. Not ideal, a lot of code.
  method1();

  /// Second method. Ideal, very little code.
  method2();
}

void method1()
{
  /// Store length pressed
  unsigned long t = button.getLengthPressed();

  if(0 < t && t <= 250 && button.getDebounceState() == false)
  {
    Serial.printf("Method 1: Button was short pressed\n");
  }

  if (250 < t && t <= 1000 && button.getDebounceState() == false)
  {
    Serial.printf("Method 1: Button was long pressed\n");
  }

  if (1000 < t && t <= 5000 && button.getDebounceState() == true)
  {
    Serial.printf("Method 1: Button is being held\n");
  }  
}

void method2()
{
  if(button.getLongPress(0, 250))
  {
    Serial.printf("Method 2: Button was short pressed\n\n");    
  }

  if(button.getLongPress(250, 1000))
  {
    Serial.printf("Method 2: Button was long pressed\n\n");    
  }
  
  if(button.getLongPress(1000, 5000, true))
  {
    Serial.printf("Method 2: Button is being held\n\n");
  }
}
