// ******************************************************************************************* //

#include "p24fj64ga002.h"

// ******************************************************************************************* //
#define F_CY 14745600
#define PWM_PERIOD (1/10000)
#define PWM_FREQ 10000					// setting frequency to 10 kHz
#define PR_VALUE (57600/PWM_FREQ)-1		// using presalar of 256 with F_CY


void PWM_init(double pot_position) {

	double OC_value_right = 0.0;
	double OC_value_left = 0.0;
	double DUTY_CYCLE_RIGHT = 0.0;
	double DUTY_CYCLE_LEFT = 0.0;

	DUTY_CYCLE_RIGHT = pot_position / (1023 / 2);						// initialize the duty cycle for right motor
	if (DUTY_CYCLE_RIGHT > 1.0) {
		DUTY_CYCLE_RIGHT = 1.0;
	}
	OC_value_right = DUTY_CYCLE_RIGHT * (PR_VALUE);				// initialize the output compare value for OC1
	OC1R = 0.0;													// set the initial duty cycle to have motor OFF
	OC1RS = OC_value_right;
	OC1CONbits.OCTSEL = 1;
	OC1CONbits.OCM = 6;

	if (DUTY_CYCLE_RIGHT > 1.0)
		DUTY_CYCLE_LEFT = 2 - DUTY_CYCLE_RIGHT;
	else
		DUTY_CYCLE_LEFT = 1.0;

	OC_value_left = DUTY_CYCLE_LEFT * (PR_VALUE);				// initialize the output compare for value for OC2
	OC2R = 0.0;													// set the initial duty cycle to have the motor OFF
	OC2RS = OC_value_left;
	OC2CONbits.OCTSEL = 1;
	OC2CONbits.OCM = 6;


	TMR3 = 0;
	PR3 = PR_VALUE;
	T3CON = 0x8030;		// configures with a prescalar of 256 and turns timer 3 ON

	return;
}

void PWM_Update(double pot_position) {

	double OC_value_right = 0.0;
	double OC_value_left = 0.0;
	double DUTY_CYCLE_RIGHT = 0.0;
	double DUTY_CYCLE_LEFT = 0.0;

	DUTY_CYCLE_RIGHT = pot_position / (1023 / 2);		// update duty cycle for new position
	if (DUTY_CYCLE_RIGHT > 1.0) {
		DUTY_CYCLE_RIGHT = 1.0;
	}			
	OC_value_right = DUTY_CYCLE_RIGHT * (PR_VALUE);		// set output compare value for new position
	OC1RS = OC_value_right;								// set the right motor value for the next cycle

	if (DUTY_CYCLE_RIGHT > 1.0)							// update duty cycle for new position
		DUTY_CYCLE_LEFT = 2 - DUTY_CYCLE_RIGHT;
	else
		DUTY_CYCLE_LEFT = 1.0;
	OC_value_left = DUTY_CYCLE_LEFT * (PR_VALUE);		// set output compare value for new position
	OC2RS = OC_value_left;								// set the left mtoor value for the next cycle


	return;
}




// Nicolas Fajardo, Paul Cross, Kevin Morris
// TEAM 202

