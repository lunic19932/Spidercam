/*
 * Speedtimer.cpp
 *
 *  Created on: 29.06.2021
 *      Author: Luisn
 */

#include "StepperTimer.h"

StepperTimer::StepperTimer() {
	// TODO Auto-generated constructor stub

}

StepperTimer::~StepperTimer() {
	// TODO Auto-generated destructor stub
}

void StepperTimer::setDirRight(bool dir){
	if(dir!=dirRight){

	}
}

int StepperTimer::slowDownDuration(){
	int currentInterval=this->currentInterval;
	int slowDownDuration=currentInterval;
	while(accIndex>0){
		currentInterval=(currentInterval * (4 * accIndex + 1)) / (4 * currentInterval - 1);
		slowDownDuration+=currentInterval;
		accIndex--;
	}
	return slowDownDuration;
}



int StepperTimer::getAccelSteps(int intervallA, int intervallB){
	if(intervallA<intervallB){
		int tmp=intervallA;
		intervallA=intervallB;
		intervallB=tmp;
	}
	int accIndex=0;
	while(intervallA>intervallB){
		intervallA=intervallA- (2 * intervallA) / (4 * accIndex+ 1);
		accIndex++;
	}
	return accIndex;
}


void StepperTimer::setSpeed(float speed,int steps){
	switch(state){
	case idle:
		if(speed<maxStartInterval)
		break;
	}


}
