/* 
 * Measures the Speed(RPM) of two BLDC motors with the Hall sensors on pin 2 and 3 
 * with a 10K pull-up resistor with 5V source and 100nF capacitor to the GND for 
 * filtering. 
 * 
 * created by Leonardo Drews Montibeller
 * 08 Sep 2018
 * 
 * This code is in the public domain.
 * 
 * https://github.com/ldmontibeller/RPM-with-Arduino/
 * 
 */
#include <math.h>

#define PIN_BLDC_1 0 //interruption 0 is the same as digital pin 2
#define PIN_BLDC_2 1 //interruption 1 is the same as digital pin 3

float speed1 = 0.0;
float speed2 = 0.0;

volatile unsigned long elapsedTimeInMicroseconds1 = 0;
volatile unsigned long elapsedTimeInMicroseconds2 = 0;

/*Number of magnetic poles that are measured by the Hall sensor.
Some BLDC motors have more than 2 magnetic poles. */
int numberOfMagneticPoles1 = 2;
int numberOfMagneticPoles2 = 2; 
 
void setup()
{ 
  Serial.begin(9600);
  attachInterrupt(PIN_BLDC_1, readTime1, FALLING);
  attachInterrupt(PIN_BLDC_2, readTime2, FALLING);
}
 
void loop()
{ 
  bldc1();
  bldc2();
}

void bldc1()
{
  noInterrupts();
  static unsigned long previousElapsedTime = 0;
  if (previousElapsedTime != elapsedTimeInMicroseconds1){
    speed1 = (pow(elapsedTimeInMicroseconds1,-1)*60000000.0)/numberOfMagneticPoles1;
    Serial.print (speed1, 3);
    Serial.print (" RPM bldc 1   ");
    previousElapsedTime = elapsedTimeInMicroseconds1;
  }
  else {
    Serial.print("0 RPM bldc 1   ");
  }
  interrupts();
  delay(500); 
}

void bldc2()
{
  noInterrupts();
  static unsigned long previousElapsedTime = 0;
  if (previousElapsedTime != elapsedTimeInMicroseconds2){
    speed2 = (pow(elapsedTimeInMicroseconds2,-1)*60000000.0)/numberOfMagneticPoles2;
    Serial.print (speed2, 3);
    Serial.print (" RPM bldc 2\r\n");
    previousElapsedTime = elapsedTimeInMicroseconds2;
  }
  else {
    Serial.print("0 RPM bldc 2\r\n");
  }
  interrupts();
  delay(500);
}

void readTime1()
{ 
  static unsigned long previousTimeInMicroseconds = 0;
  
  unsigned long thisTime = micros();
  elapsedTimeInMicroseconds1 = thisTime - previousTimeInMicroseconds;
  previousTimeInMicroseconds = thisTime;
}

void readTime2()
{
  static unsigned long previousTimeInMicroseconds = 0;
  
  unsigned long thisTime = micros();
  elapsedTimeInMicroseconds2 = thisTime - previousTimeInMicroseconds;
  previousTimeInMicroseconds = thisTime;
}
