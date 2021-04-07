#include "Battery.h"

//#define MAX_VOLTAGE 3
#define MAX_VOLTAGE 2.875 // Our max voltage is 11.5, because a diode takes away 0.5 V. So 11.5/4 = 2.875 V

int calculateBatteryPercentage(int batteryPin)
{
  // not multiplying by 3 to make calculations easier
//  double volt = (MAX_VOLTAGE - (double)batteryPin)/MAX_VOLTAGE; 
//  volt *= 100;

  double voltage = (3.3/1023)*batteryPin;
  if(voltage >= 3.0)
  {
    voltage = 3.0;
  }
  if(voltage <= 0.0)
  {
    voltage = 0.0;
  }
  double res = voltage/MAX_VOLTAGE;
  res *= 100;
  return (int)res;
    
//  return (int)volt;
}
