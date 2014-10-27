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
#define PWM_PERIOD (1/10000)
#define PWM_FREQ 10000						// setting frequency to 100 Hz; MAY NEED TO BE CHANGED
#define PR_VALUE (57600/PWM_FREQ)-1		// using presalar of 256 with F_CY

volatile int state = 0;
volatile double POT_POS = 0;

int main(void) {

	TRISAbits.TRISA0 = 1;	// set pin 2 to be input
	AD1PCFGbits.PCFG0 = 0;	// set pin 2 to be analog input

	TRISBbits.TRISB8 = 0;	// setting pin 17 to be output
	TRISBbits.TRISB9 = 0;	// setting pin 18 to be output
	RPOR4bits.RP8R = 18;	// pin RB8 (RP8) for OC1
	RPOR4bits.RP9R = 19;	// pin RB9 (RP9) for OC2

	TRISBbits.TRISB5 = 1;	// switch 1 is input

	CNEN2bits.CN27IE = 1;	// enable change notification for switch 1

	IFS1bits.CNIF = 0;		// set CN flag low
	IEC1bits.CNIE = 1;		// enable CN

	PWM_init(POT_POS);

	/***************************************
	
	TODO: Analog to digital conversions will go in here to find out the position of the
	potentiometer.  This position will be used to set the duty cycle for the motion of
	the motors in the Pulse Width Modulation (PWM).
	
	***************************************/

	// will arbitrarily define the result of the ADC as the double pot_pos (see above)
	
	// we have a 10-bit ADC, so the values from the approximation range from 0-1023 [2^10-1]
	// this means that our middle value is 511.5




	while (1) {
		PWM_Update(POT_POS);
		
		switch (state) {

			case 0:		// Idle

			case 1:		// Forward

			case 2:		// Backward





		}


	}
	






	return 0;
}


void __attribute__((interrupt)) _CNInterrupt(void) { // for SW1 RB5

	IFS1bits.CNIF = 0;

	if (PORTBbits.RB5 == 1) {   // released
		return;
	}

	//pressed (let's switch states)
	if (state = 2) {
		state = 0;
	}
	else {
		state++;
	}
}