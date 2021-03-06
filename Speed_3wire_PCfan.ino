/* 
 * Measures the Speed(RPM) of a 3-wire PC fan with the Hall sensor on pin 2 
 * with a 10K pull-up resistor with 5V source. 
 * 
 * created by Leonardo Drews Montibeller
 * modified 10 Oct 2017
 * by Leonardo Drews Montibeller
 * 
 * This code is in the public domain.
 * 
 * https://github.com/ldmontibeller/RPM-with-Arduino/blob/master/Speed_3wire_PCfan.ino
 * 
 */
#include <math.h>
#define intPin 0 //interruption 0 is the same as digital pin 2
float FanSpeed = 0;
volatile unsigned long elapsedTimeInMicroseconds = 0;
int numberOfMagneticPoles = 2; //Number of magnetic poles that are measured by the Hall sensor.
 
void setup()
{ 
  Serial.begin(9600);
  attachInterrupt(intPin, readTime, FALLING);
}
 
void loop()
{ 
  noInterrupts();
  static unsigned long previousElapsedTime = 0;
  if (previousElapsedTime != elapsedTimeInMicroseconds){
    FanSpeed = (pow(elapsedTimeInMicroseconds,-1)*60000000.0)/numberOfMagneticPoles;
    Serial.print (FanSpeed, 3);
    Serial.print (" RPM\r\n");
    previousElapsedTime = elapsedTimeInMicroseconds;
    }
  else {
    Serial.print("0 RPM\r\n");
  }
  interrupts();
  delay(500);
}

void readTime()
{ 
  static unsigned long previousTimeInMicroseconds = 0;
  unsigned long thisTime = micros();
  elapsedTimeInMicroseconds = thisTime - previousTimeInMicroseconds;
  previousTimeInMicroseconds = thisTime;
}
