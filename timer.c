#include <avr/io.h>
#include "timer.h"

void timer_init() {


	EIMSK |= (1<<INT0); //enable external interrupt Turns on INT0
	EICRA |= (1<<ISC00) | (0<<ISC01); // Any logical change on INT0 generates an interrupt request.

	
	TCCR1B = (0<<CS12)|(1<<CS11)|(1<<CS10); // prescaler 64
	
	TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);  // (inverting mode)
	TCCR1B|=(1<<WGM13); //PWM, Phase Correct set WGM13 and WGM11 top ICR1 
	ICR1=2499;  //fPWM=100Hz (Period = 10ms Standard). set the TOP value ICR1 so I can use OCR1A/OCR2A
}

