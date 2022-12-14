/*
  example1-BasicReadings

  This example shows the basic settings and functions for retrieving accelerometer
	data.
	Please refer to the header file for more possible settings, found here:
	..\SparkFun_KX13X_Arduino_Library\src\sfe_kx13x_defs.h

  Written by Elias Santistevan @ SparkFun Electronics, October 2022

	Product:

		https://www.sparkfun.com/products/17871

  Repository:

		https://github.com/sparkfun/SparkFun_KX13X_Arduino_Library

  SparkFun code, firmware, and software is released under the MIT 
	License	(http://opensource.org/licenses/MIT).
*/

#include <Wire.h>
#include "SparkFun_KX13X.h"

//SparkFun_KX132 kxAccel; 
SparkFun_KX134 kxAccel; // For the KX134, uncomment this and comment line above

outputData myData;   // Struct for the accelerometer's data

void setup() 
{
	
	Wire.begin();

	Serial.begin(115200);
  Serial.println("Welcome.");

	// Wait for the Serial monitor to be opened. 
  while(!Serial)
    delay(50);


  if( !kxAccel.begin() )
	{
    Serial.println("Could not communicate with the the KX13X. Freezing.");
    while(1);
	}

	Serial.println("Ready.");

	if( kxAccel.softwareReset() )
		Serial.println("Reset.");

	// Many settings for KX13X can only be                    														
	// applied when the accelerometer is powered down.                  														
	// However there are many that can be changed "on-the-fly"
	// check datasheet for more info, or the comments in the
	// "...regs.h" file which specify which can be changed when.
	kxAccel.enableAccel(false); 

  kxAccel.setRange(0x18);         // 16g Range
	kxAccel.enableDataEngine();     // Enables the bit that indicates data is ready.
	kxAccel.setOutputDataRate(1); // Default is 50Hz
	kxAccel.enableAccel();          

  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
}

double value = 0;
void loop() 
{
	kxAccel.getAccelData(&myData); 
	//X value
  analogWrite(0, myData.xData);
  //Y value
  analogWrite(1, myData.yData);
  //Z value
	analogWrite(2, myData.zData);
  delay(100); // Delay should be 1/ODR (Output Data Rate), default is 1/50ODR

}
