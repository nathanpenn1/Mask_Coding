#include "Battery.h"

#define MAX_VOLTAGE 1023

int calculateBatteryPercentage(int batteryPin)
{
  // not multiplying by 3 to make calculations easier
  double volt = (MAX_VOLTAGE - (double)batteryPin)/MAX_VOLTAGE; 
  volt *= 100;
    
  return (int)volt;
}
