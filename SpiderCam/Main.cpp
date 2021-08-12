/*
 * Main.cpp
 *
 *  Created on: 04.07.2021
 *      Author: luisn
 */

#include "Arduino.h"
#include "SpiderCam.h"
#include "SynchronizedTimer.h"
#include "SerialApi.h"
#include "SynchTimerControl1.h"

//SerialApi messageHandler=SerialApi::getInstance();
SynchTimerControl1 con;
SpiderCam *spidercam;
String inputString;
bool isComplete;
String getValue(String data, char separator, int index) {
	int found = 0;
	int strIndex[] = { 0, -1 };
	int maxIndex = data.length() - 1;

	for (int i = 0; i <= maxIndex && found <= index; i++) {
		if (data.charAt(i) == separator || i == maxIndex) {
			found++;
			strIndex[0] = strIndex[1] + 1;
			strIndex[1] = (i == maxIndex) ? i + 1 : i;
		}
	}
	return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
void setup() {

	Settings settings;
	spidercam = new SpiderCam(8.7, 3, 16, settings);


}
void loop() {
	if (isComplete) {
		float speed = getValue(inputString, ';', 0).toFloat();
		float x = getValue(inputString, ';', 1).toFloat();
		float y = getValue(inputString, ';', 2).toFloat();
		float z = getValue(inputString, ';', 3).toFloat();
		spidercam->moveToPos(speed, x, y, z);
		Serial.print("Current: ");
		Serial.println(spidercam->getCurrentPos().toString());
		Serial.print("Target: ");
		Serial.println(spidercam->getTargetPos().toString());
		isComplete = false;
		inputString = "";
	}
}

ISR(TIMER1_COMPA_vect) {
	spidercam->coordinateMove();
}

void serialEvent() {

	while (Serial.available()) {
		// get the new byte:
		char inChar = (char) Serial.read();
		// add it to the inputString:
		inputString += inChar;
		// if the incoming character is a newline, set a flag so the main loop can
		// do something about it:
		if (inChar == '\n') {
			isComplete = true;
		}
	}

}
