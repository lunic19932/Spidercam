///*
// * SerialApi.h
// *
// *  Created on: 04.07.2021
// *      Author: Luisn
// */
//
//#ifndef SERIALAPI_H_
//#define SERIALAPI_H_
//#include "Arduino.h"
//#include "SpiderCam.h"
//#include "SynchronizedTimer.h"
//
//class SerialApi {
//public:
//	void init();
//	void handleMessage();
//	static SerialApi getInstance();
//
//	const String& getInputString() const;
//	void setInputString(const String &inputString);
//	bool isStringComplete() const;
//	void setStringComplete(bool stringComplete);
//	void setCam(const SpiderCam *cam) ;
//	void handleMessage(String message);
//private:
//	void handleSetting(String message);
//	void handleMoveTo(String message);
//	void handleMoveRelative(String message);
//	String getValue(String data, char separator, int index);
//	void executeAction(String command);
//	static SerialApi instance;
//	SerialApi();
//	String inputString;
//	bool stringComplete;
//	SpiderCam* cam;
//};
//
//#endif /* SERIALAPI_H_ */
