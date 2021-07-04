/*
 * Main.cpp
 *
 *  Created on: 04.07.2021
 *      Author: luisn
 */

#include "Arduino.h"
#include "SpiderCam.h"
#include "SynchronizedTimer.h"
SpiderCam spidercam;
void setup() {
	spidercam=SpiderCam();
}

void loop() {



}

ISR(TIMER1_COMPA_vect)
{
	char triggeredTimerFlag=SynchronizedTimer::coordinateTimer() ;
	for(int i=0;i<SynchronizedTimer::timerCount;i++){
		if(((1 << i) & triggeredTimerFlag)){
			spidercam.getAxis(i).makeStep();
		}
	}
}
