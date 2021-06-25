// Do not remove the include below
#include "SpiderCam.h"

#include "PinDefinition.h"

struct stepperInfo {
	// externally defined parameters
	float acceleration;
	volatile unsigned long minStepInterval; // ie. max speed, smaller is faster
	void (*dirFunc)(int);
	void (*stepFunc)();

	// derived parameters
	unsigned int startInterval; // step interval for first step, determines acceleration
	long stepPosition; // current position of stepper (total of all movements taken so far)

	// per movement variables (only changed once per movement)
	volatile int dir; // current direction of movement, used to keep track of position
	volatile unsigned int totalSteps; // number of steps requested for current movement
	volatile bool movementDone = false; // true if the current movement has been completed (used by main program to wait for completion)
	volatile unsigned int rampUpStepCount; // number of steps taken to reach either max speed, or half-way to the goal (will be zero until this number is known)
	volatile unsigned long estStepsToSpeed; // estimated steps required to reach max speed
	volatile unsigned long estTimeForMove; // estimated time (interrupt ticks) required to complete movement
	volatile unsigned long rampUpStepTime;
	volatile float speedScale; // used to slow down this motor to make coordinated movement with other motors

	// per iteration variables (potentially changed every interrupt)
	volatile unsigned int accIndex; // index in acceleration curve, used to calculate next interval
	volatile float currentDelay;                      // current interval length
	volatile unsigned long scaledDelay;              // above variable truncated
	volatile unsigned int stepCount; // number of steps completed in current movement
};

void xStep() {
	X_STEP_HIGH
	X_STEP_LOW
}
void xDir(int dir) {
	digitalWrite(X_DIR_PIN, dir);
}

void yStep() {
	Y_STEP_HIGH
	Y_STEP_LOW
}
void yDir(int dir) {
	digitalWrite(Y_DIR_PIN, dir);
}

void zStep() {
	Z_STEP_HIGH
	Z_STEP_LOW
}
void zDir(int dir) {
	digitalWrite(Z_DIR_PIN, dir);
}

void e0Step() {
	E0_STEP_HIGH
	E0_STEP_LOW
}
void e0Dir(int dir) {
	digitalWrite(E0_DIR_PIN, dir);
}

void e1Step() {
	E1_STEP_HIGH
	E1_STEP_LOW
}
void e1Dir(int dir) {
	digitalWrite(E1_DIR_PIN, dir);
}
void resetStepper(volatile stepperInfo &si) {
	si.startInterval = si.acceleration;
	si.currentDelay = si.startInterval;
	si.scaledDelay = si.currentDelay;
	si.stepCount = 0;
	si.accIndex = 0;
	si.rampUpStepCount = 0;
	si.movementDone = false;
	si.speedScale = 1;

	float a = si.minStepInterval / (float) si.startInterval;
	a *= 0.676;

	float m = ((a * a - 1) / (-2 * a));
	float n = m * m;

	si.estStepsToSpeed = n;
}

#define NUM_STEPPERS 6

volatile stepperInfo steppers[NUM_STEPPERS];

void setup() {

	noInterrupts();
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;

	OCR1A = 1000;                             // compare value
	TCCR1B |= (1 << WGM12);                   // CTC mode
	TCCR1B |= ((1 << CS11) | (1 << CS10));    // 64 prescaler
	interrupts();

	steppers[0].dirFunc = e1Dir;
	steppers[0].stepFunc = e1Step;
	steppers[0].acceleration = 1000;
	steppers[0].minStepInterval = 50;

	steppers[1].dirFunc = e0Dir;
	steppers[1].stepFunc = e0Step;
	steppers[1].acceleration = 1000;
	steppers[1].minStepInterval = 50;

	steppers[3].dirFunc = xDir;
	steppers[3].stepFunc = xStep;
	steppers[3].acceleration = 1000;
	steppers[3].minStepInterval = 50;

	steppers[4].dirFunc = yDir;
	steppers[4].stepFunc = yStep;
	steppers[4].acceleration = 1000;
	steppers[4].minStepInterval = 50;

	steppers[5].dirFunc = zDir;
	steppers[5].stepFunc = zStep;
	steppers[5].acceleration = 1000;
	steppers[5].minStepInterval = 50;
}

volatile byte remainingSteppersFlag = 0;

float getDurationOfAcceleration(volatile stepperInfo &s,
		unsigned int numSteps) {
	float d = s.startInterval;
	float totalDuration = 0;
	for (unsigned int n = 1; n < numSteps; n++) {
		d = d - (2 * d) / (4 * n + 1);
		totalDuration += d;
	}
	return totalDuration;
}

void prepareMovement(int whichMotor, long steps) {
	volatile stepperInfo &si = steppers[whichMotor];
	si.dirFunc(steps < 0 ? HIGH : LOW);
	si.dir = steps > 0 ? 1 : -1;
	si.totalSteps = abs(steps);
	resetStepper(si);

	remainingSteppersFlag |= (1 << whichMotor);

	unsigned long stepsAbs = abs(steps);

	if ((2 * si.estStepsToSpeed) < stepsAbs) {
		// there will be a period of time at full speed
		unsigned long stepsAtFullSpeed = stepsAbs - 2 * si.estStepsToSpeed;
		float accelDecelTime = getDurationOfAcceleration(si,
				si.estStepsToSpeed);
		si.estTimeForMove = 2 * accelDecelTime
				+ stepsAtFullSpeed * si.minStepInterval;
	} else {
		// will not reach full speed before needing to slow down again
		float accelDecelTime = getDurationOfAcceleration(si, stepsAbs / 2);
		si.estTimeForMove = 2 * accelDecelTime;
	}
}

volatile byte nextStepperFlag = 0;

void setNextInterruptInterval() {

	bool movementComplete = true;

	unsigned long mind = 999999;
	for (int i = 0; i < NUM_STEPPERS; i++) {
		if (((1 << i) & remainingSteppersFlag)
				&& steppers[i].scaledDelay < mind) {
			mind = steppers[i].scaledDelay;
		}
	}

	nextStepperFlag = 0;
	for (int i = 0; i < NUM_STEPPERS; i++) {
		if (!steppers[i].movementDone)
			movementComplete = false;
		if (((1 << i) & remainingSteppersFlag)
				&& steppers[i].scaledDelay == mind)
			nextStepperFlag |= (1 << i);
	}

	if (remainingSteppersFlag == 0) {
		TIMER1_INTERRUPTS_OFF
		OCR1A = 65500;
	}

	OCR1A = mind;
}

ISR(TIMER1_COMPA_vect) {
	unsigned int tmpCtr = OCR1A;

	OCR1A = 65500;

	for (int i = 0; i < NUM_STEPPERS; i++) {

		if (!((1 << i) & remainingSteppersFlag))
			continue;

		if (!(nextStepperFlag & (1 << i))) {
			steppers[i].scaledDelay -= tmpCtr;
			continue;
		}

		volatile stepperInfo &s = steppers[i];

		if (s.stepCount < s.totalSteps) {
			s.stepFunc();
			s.stepCount++;
			s.stepPosition += s.dir;
			if (s.stepCount >= s.totalSteps) {
				s.movementDone = true;
				remainingSteppersFlag &= ~(1 << i);
			}
		}

		if (s.rampUpStepCount == 0) {
			s.accIndex++;
			s.currentDelay = s.currentDelay
					- (2 * s.currentDelay) / (4 * s.accIndex + 1);
			if (s.currentDelay <= s.minStepInterval) {
				s.currentDelay = s.minStepInterval;
				s.rampUpStepCount = s.stepCount;
			}
			if (s.stepCount >= s.totalSteps / 2) {
				s.rampUpStepCount = s.stepCount;
			}
			s.rampUpStepTime += s.currentDelay;
		} else if (s.stepCount >= s.totalSteps - s.rampUpStepCount) {
			s.currentDelay = (s.currentDelay * (4 * s.accIndex + 1))
					/ (4 * s.accIndex + 1 - 2);
			s.accIndex--;
		}

		s.scaledDelay = s.currentDelay * s.speedScale; // integer
	}

	setNextInterruptInterval();

	TCNT1 = 0;
}

void runAndWait() {
	adjustSpeedScales();
	setNextInterruptInterval();
	TIMER1_INTERRUPTS_ON
	while (remainingSteppersFlag)
		;
	remainingSteppersFlag = 0;
	nextStepperFlag = 0;
}

void adjustSpeedScales() {
	float maxTime = 0;

	for (int i = 0; i < NUM_STEPPERS; i++) {
		if (!((1 << i) & remainingSteppersFlag))
			continue;
		if (steppers[i].estTimeForMove > maxTime)
			maxTime = steppers[i].estTimeForMove;
	}

	if (maxTime != 0) {
		for (int i = 0; i < NUM_STEPPERS; i++) {
			if (!((1 << i) & remainingSteppersFlag))
				continue;
			steppers[i].speedScale = maxTime / steppers[i].estTimeForMove;
		}
	}
}

void loop() {

	for (int i = 0; i < NUM_STEPPERS; i++) {
		prepareMovement(i, 800);
		runAndWait();
	}

	prepareMovement(0, 8000);
	prepareMovement(1, 800);
	prepareMovement(2, 2400);
	prepareMovement(3, 800);
	prepareMovement(4, 1600);
	prepareMovement(5, 800);
	runAndWait();

	delay(1000);

	prepareMovement(0, -8000);
	prepareMovement(1, 1600);
	prepareMovement(2, -2400);
	prepareMovement(3, -800);
	prepareMovement(4, 2400);
	prepareMovement(5, -800);
	runAndWait();

	while (true)
		;

}

SpiderCam::SpiderCam() {
	// TODO Auto-generated constructor stub

}

SpiderCam::~SpiderCam() {
	// TODO Auto-generated destructor stub
}

