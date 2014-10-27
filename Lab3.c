// ******************************************************************************************* //
// Include file for PIC24FJ64GA002 microcontroller. This include file defines
// MACROS for special function registers (SFR) and control bits within those
// registers.

#include "p24fj64ga002.h"
#include "RobotMove.h"
#include <stdio.h>
#include "lcd.h"

// ******************************************************************************************* //
// Configuration bits for CONFIG1 settings. 
//
// Make sure "Configuration Bits set in code." option is checked in MPLAB.
//
// These settings are appropriate for debugging the PIC microcontroller. If you need to 
// program the PIC for standalone operation, change the COE_ON option to COE_OFF.

_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & BKBUG_ON & COE_ON & ICS_PGx1 &
	FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS32768)

// ******************************************************************************************* //
// Configuration bits for CONFIG2 settings.
// Make sure "Configuration Bits set in code." option is checked in MPLAB.

_CONFIG2(IESO_OFF & SOSCSEL_SOSC & WUTSEL_LEG & FNOSC_PRIPLL & FCKSM_CSDCMD & OSCIOFNC_OFF &
IOL1WAY_OFF & I2C1SEL_PRI & POSCMOD_XT)

// ******************************************************************************************* //

// Varible used to indicate that the current configuration of the keypad has been changed,
// and the KeypadScan() function needs to be called.

#define F_CY 14745600

// FIXME: MAY NEED TO CHANGE FREQUENCY BELOW
#define PWM_PERIOD 1
#define PWM_FREQ 1						// setting frequency to 100 Hz; MAY NEED TO BE CHANGED
#define PR_VALUE (57600/PWM_FREQ)-1		// using presalar of 256 with F_CY


volatile double POT_POS = 0;

int main(void) {

	double OC_value_right = 0.0;
	double OC_value_left = 0.0;
	double DUTY_CYCLE_RIGHT = 0.0;
	double DUTY_CYCLE_LEFT = 0.0;

	TRISAbits.TRISA0 = 1;		// set pin 2 to be input
	AD1PCFGbits.PCFG0 = 0;		// set pin 2 to be analog input

	/***************************************
	
	TODO: Analog to digital conversions will go in here to find out the position of the
	potentiometer.  This position will be used to set the duty cycle for the motion of
	the motors in the Pulse Width Modulation (PWM).
	
	***************************************/

	// will arbitrarily define the result of the ADC as the double pot_pos (see above)
	
	// we have a 10-bit ADC, so the values from the approximation range from 0-1023 [2^10-1]
	// this means that our middle value is 511.5

	TRISBbits.TRISB8 = 0;	// setting pin 17 to be output
	TRISBbits.TRISB9 = 0;	// setting pin 18 to be output
	RPOR4bits.RP8R = 18;	// pin RB8 (RP8) for OC1
	RPOR4bits.RP9R = 19;	// pin RB9 (RP9) for OC2
	
	DUTY_CYCLE_RIGHT = POT_POS / ((2 ^ 10) - 1);				// initialize the duty cycle for right motor
	OC_value_right = DUTY_CYCLE_RIGHT * (PR_VALUE / PWM_FREQ);	// initialize the output compare value for OC1
	OC1R = 0.0;													// set the initial duty cycle to have motor OFF
	OC1RS = OC_value_right;
	OC1CONbits.OCTSEL = 1;
	OC1CONbits.OCM = 6;

	DUTY_CYCLE_LEFT = 1 - DUTY_CYCLE_RIGHT;						// left motor will be remaining fraction of right motor
	OC_value_left = DUTY_CYCLE_LEFT * (PR_VALUE / PWM_FREQ);	// initialize the output compare for value for OC2
	OC2R = 0.0;													// set the initial duty cycle to have the motor OFF
	OC2RS = OC_value_left;
	OC2CONbits.OCTSEL = 1;
	OC2CONbits.OCM = 6;


	TMR3 = 0;
	PR3 = PR_VALUE;
	T3CON = 0x8030;		// configures with a prescalar of 256 and turns timer 3 ON


	while (1) {
		DUTY_CYCLE_RIGHT = POT_POS / ((2^10) - 1);			// update duty cycle for new position
		OC_value_right = DUTY_CYCLE_RIGHT * (PR_VALUE/PWM_FREQ);	// set output compare value for new position
		OC1RS = OC_value_right;								// set the right motor value for the next cycle

		DUTY_CYCLE_LEFT = 1 - DUTY_CYCLE_RIGHT;				// update duty cycle for new position
		OC_value_left = DUTY_CYCLE_LEFT * (PR_VALUE / PWM_FREQ);	// set output compare value for new position
		OC2RS = OC_value_left;								// set the left mtoor value for the next cycle




	}
	






	return 0;
}