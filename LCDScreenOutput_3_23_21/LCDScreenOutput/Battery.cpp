#include "Battery.h"

#define MAX_VOLTAGE 6

int calculateBatteryPercentage(int batteryPin)
{
   return (batteryPin/MAX_VOLTAGE)*100; // Calculate the battery percentage
}
