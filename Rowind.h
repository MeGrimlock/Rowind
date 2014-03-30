
/*

	Rowind.h

	A library for using a Rowind wind sensor with a arduino

	Author: Jordan Springett
	GitHub: https://github.com/JSpringett

	This code is released under the terms of the LGPLv3 licence.
 */

#ifndef Included_Rowind_H
#define Included_Rowind_H

#include "Arduino.h"
#include "SoftwareSerial.h"

class Rowind {
public:
	Rowind(int rx, int tx);

	/**
	 * Determines if the Rowind is functioning correctly.
	 * @return Returns true if the rowind is working correctly.
	 */
	bool IsFunctioning();

	/**
	 * Sets the wind direction into two specified variables.
	 * @param direction 	Direction of the wind in relation to the boat.
	 * @param speed    	Speed of the wind.
	 * @return 		Returns false if something went wrong and the data is invalid.
	 */
	bool GetData(float& direction, float& speed);
private:
	/**
	 * Returns the correct NMEA string to get the wind data from.  This function can
	 * timeout and return a null pointer if its unable to get any data.
	 * @return Pointer to the correct line, delete after use.
	 */
	char * GetLine();

	//*******************************************************************************//
	// Member Fields               											 
	//*******************************************************************************//
private:
	SoftwareSerial m_Serial;		// Allows the library to read data from the Rowind.
	int TimeOut;				// The max amount of time to wait around for valid
						// data before giving up in milliseconds.
};

#endif