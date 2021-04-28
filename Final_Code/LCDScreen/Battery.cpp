#include "Battery.h"

//#define MAX_VOLTAGE 3   // Considering voltage divider factor of 4, we have 12/4 = 3 V
#define MAX_VOLTAGE 2.875 // Our max voltage is 11.5, because a diode takes away 0.5 V. So 11.5/4 = 2.875 V. 
//Divide by 4 because Brandon has a voltage divider in order for the pin to safely receive the battery voltage without frying the pin. 

int calculateBatteryPercentage(int batteryPin)
{
  double voltage = (3.3/1023)*batteryPin; // convert the value read from the battery pin to a voltage

  // make sure the voltage is within the range 0 to 3 volts
  if(voltage >= (double)MAX_VOLTAGE)
  {
    voltage = (double)MAX_VOLTAGE;
  }
  if(voltage <= 0.0)
  {
    voltage = 0.0;
  }

  // convert the voltage reading to a percentage 
  double res = voltage/MAX_VOLTAGE;
  res *= 100;
  return (int)res;
    
}
