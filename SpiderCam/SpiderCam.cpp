// Do not remove the include below
#include "SpiderCam.h"
#include "SynchronizedTimer.h"

SpiderCam::SpiderCam(float startX, float startY, float startZ,
		Settings settings) :
		settings(settings), progressMove(0), waitingForMove(false), savedSpeed(
				0) {
	Serial.begin(9600);
	Serial.println("\n");
	Vec3d tmpVec = Vec3d(startX, startY, startZ);
	posBegin = tmpVec;
	posCurrent = tmpVec;
	target = tmpVec;
	moveVector = Vec3d();
	savedPos = Vec3d();
	for (int i = 0; i < axisNum; i++) {
		axis[i] = new Axis(settings, i);
		axis[i]->setPosStepper(axis[i]->calculateSteps(tmpVec));
	}
	updateSettings(settings);

}

SpiderCam::~SpiderCam() {

}

void SpiderCam::executeMove(int steps[axisNum], float speed, Vec3d target) {
	posBegin = posCurrent;
	this->target = target;
	moveVector = target - posCurrent;
	for (int i = 0; i < axisNum; i++) {
		axis[i]->setStep(steps[i]);
	}
	this->speed = speed;
	int interval = ((1.0/speed) * settings.rotationPerStep)*timerControll.preScalerCompensation;
Serial.println(interval);
	timerControll.startTimer(interval, steps);
	waitingForMove = false;

}

void SpiderCam::moveToPos(float speed, float x, float y, float z) {
	Vec3d posBegin = posCurrent;
	Vec3d target = Vec3d(x, y, z);
	Vec3d moveVector = target - posCurrent;
	TimerState state = timerControll.getState();
	int steps[axisNum];
	bool changeDir = false;
	for (int i = 0; i < axisNum; i++) {
		steps[i] = axis[i]->calculateSteps(target);
		changeDir |= axis[i]->getDir() == steps[i] / abs(steps[i]);
		steps[i]=1/settings.rotationPerStep;
		Serial.println(steps[i]);
	}
	if ((state == TimerState::runInterval) ||(state == TimerState::longInterval) || (!changeDir)) {
		executeMove(steps, speed, target);
	} else {
		savedSpeed = speed;
		savedPos = target;
		timerControll.setTargetInterval(timerControll.accelStartInterval);
		waitingForMove = true;
		Serial.print("ChangeDir: ");
		Serial.println(changeDir);
		Serial.print("State: ");
		Serial.println(state);
		Serial.print("LongInterval: ");
		Serial.println(longInterval);
		Serial.print("StateBool: ");
		Serial.println((state == TimerState::longInterval));
		Serial.print("Bool: ");
		Serial.println((!changeDir) || state == longInterval);
	}
}

void SpiderCam::moveToSavedPos() {
	if (timerControll.getState() == longInterval) {
		TIMER1_INTERRUPTS_OFF

		int steps[axisNum];
		for (int i = 0; i < axisNum; i++) {
			steps[i] = axis[i]->calculateSteps(savedPos);
		}

		executeMove(steps, savedSpeed, savedPos);
		waitingForMove = false;
	}
}

Vec3d SpiderCam::getCurrentPos() {
	return posCurrent;
}

Axis* SpiderCam::getAxis(int axisIndex) {
	return axis[axisIndex];
}

void SpiderCam::updateSettings(Settings settings) {
	this->settings = settings;
	for (int i = 0; i < axisNum; i++) {
		axis[i]->updateSetting(settings);
	}
}
void SpiderCam::coordinateMove() {
	if (waitingForMove) {
		moveToSavedPos();
	}
	byte moveFlag = timerControll.tik();
	for (int i = 0; i < axisNum; i++) {
		if (moveFlag & 1 << i) {
			axis[i]->makeStep();
		}
	}

	progressMove = timerControll.getProgress();
	Vec3d progressVec = moveVector.multiply(progressMove);
	posCurrent = posBegin + progressVec;

	if (timerControll.getProgress() >= 1) {
		posCurrent = target;
	}
}

Vec3d SpiderCam::getTargetPos() {
	return target;
}
