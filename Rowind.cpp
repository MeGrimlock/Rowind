
/*

	Rowind.h

	A library for using a Rowind wind sensor with a arduino

	Author: Jordan Springett
	GitHub: https://github.com/JSpringett

	This code is released under the terms of the LGPLv3 licence.
 */

#include "Rowind.h"
#include "Arduino.h"
#include "SoftwareSerial.h"

#define Null 0

//*******************************************************************************//
//  Constructor											 
//*******************************************************************************//
	

//=====================================================================
Rowind::Rowind(int rx, int tx)
	 : m_Serial(rx, tx) 
{ 
	m_Serial.begin(4800);
}


//*******************************************************************************//
//  Public Methods											 
//*******************************************************************************//


//=====================================================================
bool Rowind::IsFunctioning() {
	if(GetLine() != Null)
		return true;
	return false;
}

//=====================================================================
bool Rowind::GetData(float& direction, float& speed) {
	m_Serial.listen();
  	char* line = GetLine();

  	// Make sure nothing went wrong and that we have a valid line
  	if(line == Null) {
  		return false;
  	}

	// Parse line
	char *s = line;
	char *str;
	int i = 0;

	//  Splits the string into tokens whic hare seperated by ','. Returns null when at the end
	while ((str = strtok_r( s, ",", &s )) != NULL )
	{
		// Prints the token we are currently working on
        	//Serial.println(str);
		// Second token contains the windw direction
		if ( i == 1 )
		{
	          	// Inteprets the data as a floating point and then returns the wind direction as a double.
			direction = atof( str );

		// fourth token contains wind speed
		}else if ( i == 3 )
		 {
			speed = atof( str );
		}
		i++;
	}
}


//*******************************************************************************//
//  Private Methods											 
//*******************************************************************************//

//=====================================================================
char* Rowind::GetLine() {
	char line[80];
	bool gotData = false;
	float startTime = millis();

	// Search for the correct rowind data line.
	while(!gotData && startTime > millis() - TimeOut) {
		char c = m_Serial.read();
		delay(3);
		// Start of a rowind sentence
		if(c == '$') {
			int i = 0;

	        		// Reads a line
			while(c != '\n' & i < 80) {
				line[i] = c;
				c = m_Serial.read();
				delay(3);
				i++;
			}

			// Data we want starts with $IIMWV
			if(line[1] == 'I') {
				gotData = true;
			}
		}
	}

	if(!gotData) {
		return Null;
	}

	return line;
}