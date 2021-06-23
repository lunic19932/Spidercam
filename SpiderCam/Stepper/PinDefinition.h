/*
 * PinDeclaration.h
 *
 *  Created on: 22.06.2021
 *      Author: petra
 */

#ifndef PINDEFINITION_H_
#define PINDEFINITION_H_

// For RAMPS 1.4
#define X_DIR_PIN          55
#define X_STEP_PIN         54
#define X_ENABLE_PIN       38

#define Y_DIR_PIN          61
#define Y_STEP_PIN         60
#define Y_ENABLE_PIN       56

#define Z_DIR_PIN          48
#define Z_STEP_PIN         46
#define Z_ENABLE_PIN       62

#define E0_DIR_PIN          28
#define E0_STEP_PIN         26
#define E0_ENABLE_PIN       24

#define E1_DIR_PIN          34
#define E1_STEP_PIN         36
#define E1_ENABLE_PIN       30



#define X_STEP_HIGH             PORTF |=  0b00000001;
#define X_STEP_LOW              PORTF &= ~0b00000001;

#define Y_STEP_HIGH             PORTF |=  0b01000000;
#define Y_STEP_LOW              PORTF &= ~0b01000000;

#define Z_STEP_HIGH             PORTL |=  0b00001000;
#define Z_STEP_LOW              PORTL &= ~0b00001000;

#define E0_STEP_HIGH             PORTA |=  0b00010000;
#define E0_STEP_LOW              PORTA &= ~0b00010000;

#define E1_STEP_HIGH             PORTC |=  0b00000010;
#define E1_STEP_LOW              PORTC &= ~0b00000010;



#define TIMER1_INTERRUPTS_ON    TIMSK1 |=  (1 << OCIE1A);
#define TIMER1_INTERRUPTS_OFF   TIMSK1 &= ~(1 << OCIE1A);

#define X_STEPPER_INDEX 0
#define Y_STEPPER_INDEX 1
#define Z_STEPPER_INDEX 2
#define E0_STEPPER_INDEX 3
#define E1_STEPPER_INDEX 4


#endif /* PINDEFINITION_H_ */
