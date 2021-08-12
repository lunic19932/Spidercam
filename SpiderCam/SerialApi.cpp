///*
// * SerialApi.cpp
// *
// *  Created on: 04.07.2021
// *      Author: Luisn
// */
//
//#include "SerialApi.h"
//#include "Settings.h"
//const String& SerialApi::getInputString() const {
//	return inputString;
//}
//
//void SerialApi::setInputString(const String &inputString) {
//	this->inputString = inputString;
//}
//
//bool SerialApi::isStringComplete() const {
//	return stringComplete;
//}
//
//void SerialApi::setStringComplete(bool stringComplete) {
//	this->stringComplete = stringComplete;
//}
//
//void SerialApi::setCam(const SpiderCam *cam) {
//	this->cam = cam;
//}
//void serialEvent() {
//	String inputString;
//	bool isComplete;
//	while (Serial.available()) {
//		// get the new byte:
//		char inChar = (char) Serial.read();
//		// add it to the inputString:
//		inputString += inChar;
//		// if the incoming character is a newline, set a flag so the main loop can
//		// do something about it:
//		if (inChar == '\n') {
//			isComplete = true;
//		}
//	}
//	SerialApi::getInstance().setInputString(inputString);
//	SerialApi::getInstance().setStringComplete(isComplete);
//}
//
//void SerialApi::init() {
//	Serial.begin(9600);
//	inputString.reserve(200);
//	stringComplete = false;
//}
//
//void SerialApi::handleMessage() {
//	if (stringComplete) {
//		executeAction(inputString);
//		inputString = "";
//		stringComplete = false;
//	}
//}
//
//SerialApi SerialApi::getInstance() {
//
//	return instance;
//
//}
//
//void SerialApi::executeAction(String command) {
//}
//
//String SerialApi::getValue(String data, char separator, int index) {
//	int found = 0;
//	int strIndex[] = { 0, -1 };
//	int maxIndex = data.length() - 1;
//
//	for (int i = 0; i <= maxIndex && found <= index; i++) {
//		if (data.charAt(i) == separator || i == maxIndex) {
//			found++;
//			strIndex[0] = strIndex[1] + 1;
//			strIndex[1] = (i == maxIndex) ? i + 1 : i;
//		}
//	}
//
//	return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
//}
//void SerialApi::handleMessage(String message) {
//	int i = 0;
//	String bodyString;
//	String tmpString;
//	int type = getValue(message, ';', i++).toInt();
//	switch (type) {
//	case 0: //settings
//		handleSetting(message);
//		break;
//	case 1: //moveTo
//		handleMoveTo(message);
//		break;
//	case 2: //moveTo
//		handleMoveRelative(message);
//		break;
//	}
//
//}
//
//void SerialApi::handleSetting(String message) {
//	struct Settings setting;
//		setting.aAxisSuspension_x = getValue(message, ';', 1).toDouble();
//		setting.aAxisSuspension_y = getValue(message, ';', 2).toDouble();
//		setting.aAxisSuspension_z = getValue(message, ';', 3).toDouble();
//		setting.bAxisSuspension_x = getValue(message, ';', 4).toDouble();
//		setting.bAxisSuspension_y = getValue(message, ';', 5).toDouble();
//		setting.bAxisSuspension_z = getValue(message, ';', 6).toDouble();
//		setting.cAxisSuspension_x = getValue(message, ';', 7).toDouble();
//		setting.cAxisSuspension_y = getValue(message, ';', 8).toDouble();
//		setting.cAxisSuspension_z = getValue(message, ';', 9).toDouble();
//		setting.dAxisSuspension_x = getValue(message, ';', 10).toDouble();
//		setting.dAxisSuspension_y = getValue(message, ';', 11).toDouble();
//		setting.dAxisSuspension_z = getValue(message, ';', 12).toDouble();
//		setting.maxSpeed = getValue(message, ';', 13).toDouble();
//		setting.rotationPerStep = getValue(message, ';', 14).toDouble();
//		setting.winchRadius= getValue(message, ';', 15).toDouble();
//}
//
//void SerialApi::handleMoveTo(String message) {
//}
//
//void SerialApi::handleMoveRelative(String message) {
//}
//
//SerialApi::SerialApi() :
//		inputString(""), stringComplete(false), cam(NULL) {
//}
