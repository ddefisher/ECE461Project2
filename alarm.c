/*
 * adc14.c
 *
 *  Created on: Mar 14, 2016
 *      Author: daniel
 */
#include "msp.h"

#define DUTY_CYCLE 410

unsigned int badguy_here = 0;

void sample_mic()
{

	  ADC14CTL0 |= ADC14ENC |ADC14SC ;    // Start sampling/conversion
	  __wfi();                            // alternatively you can also use __sleep();

	  if(ADC14MEM0 > 9000){
		  badguy_here = 1;
	  }

}
int burglar_here()
{
    if(badguy_here){
        return 1;
    }
    else{
        return 0;
    }
}
void burglar_alarm()
{
	 TA0CCR0 = DUTY_CYCLE*3;                // Change PWM period based on ADC result
	 TA0CCR4 = TA0CCR0 / 2;

}
unsigned int alarm_button(unsigned int alarm_status)
{

    if( alarm_status ){
        P2OUT &= ~BIT4;//turn off green rgb     
        P2OUT |= BIT6;//turn on red rgb
        alarm_status = 0;
    }
    else{
        P2OUT &= ~BIT6;//turn off red rgb     
        P2OUT |= BIT4;//turn on green rgb
        alarm_status = 1;
    }

    unsigned int i;

    for(i = 0; i < 50000;i++);

    return alarm_status;

}
