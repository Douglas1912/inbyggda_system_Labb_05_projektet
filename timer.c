#include <avr/io.h>
#include "timer.h"

void timer_init() {
	
	TCCR1B = (1<<CS11) | (1<<CS10); // prescaler 64
	TCCR1A|=(1<<COM1A1);  // Enable the PWM outputs OC1A, on digital pins 9
	TCCR1B|=(1<<WGM13); // PWM, phase and frequency correct, top = ICR1 
	ICR1=4999;  //fPWM=50Hz (delay Period = 20ms ). set the TOP value ICR1 so I can use OCR1A
}

 