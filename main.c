#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

#define F_CPU 16000000UL // telling controller crystal frequency (16 MHz AVR ATMega328P)

#include "serial.h"
#include "timer.h"

#define SERVOMOTOR PB1
#define ECHO_HCR04_OUTSIDE PD2
#define TRIGGER_HCR04_OUTSIDE PD3
#define ECHO_INSIDE PB5
#define TRIGGER_INSIDE PD5
#define RED_LED PC0
#define YELLOW_LED PC2
#define GREEN_LED PC1

volatile unsigned short hc_sr04_counter;
volatile unsigned char sample_meausure;
volatile unsigned char servo_counter = 0;

void port_init();
void servormotor_open();
void servormotor_close();
unsigned char hc_sr04_measure_outside( void );
  
int main(void)
{	
	sei();
	uart_init();	
	timer_init();
	port_init();
	

    while(1)
    {
		sample_meausure = hc_sr04_measure_outside();
		printf("TCNT1:%5d\n\r",TCNT1 );
		
		printf("dist - %d\n", sample_meausure);
		
		if(sample_meausure <= 10){
 
			PORTC |= (1<<RED_LED); 
			PORTC |= (1<<YELLOW_LED); 
			PORTC |= (1<<GREEN_LED); 
			
			servormotor_open();
			
			sample_meausure = hc_sr04_measure_outside();
			if(sample_meausure > 10){
				servormotor_close();
				servo_counter = 0;
			}
		}
		else{
			 
			PORTC &= ~(1<<RED_LED); 
			PORTC &= ~(1<<YELLOW_LED); 
			PORTC &= ~(1<<GREEN_LED); 	
			
			_delay_ms( 200 );
		}
    }
}


void port_init()
{
	DDRB |= (1<<SERVOMOTOR);
	DDRC |= (1<<RED_LED) | (1<<YELLOW_LED) | (1<<GREEN_LED); // for the LED
	DDRD |= (1<<TRIGGER_HCR04_OUTSIDE) | (0<<ECHO_HCR04_OUTSIDE); // Set TRIGGER_HCR04_OUTSIDE as output. Set ECHO_HCR04_OUTSIDE as input. SERVOMOTOR as output
	DDRD |= (1<<TRIGGER_INSIDE) | (0<<ECHO_INSIDE) ; //
	PORTD=0x00; // Set all pins of PORTD low which turns it off.
}


void servormotor_open()
{
	if(servo_counter == 0){
		OCR1A=200;   //degree
		_delay_ms( 900 );
		servo_counter = 1;
	}
	if(servo_counter == 1){
		OCR1A=0;  //clear to stop the buzzing
		_delay_ms( 2000 );
	}
}


void servormotor_close()
{
	OCR1A=90;  //degree
	_delay_ms( 900 );
	OCR1A=0;  
}


unsigned char hc_sr04_measure_outside( void )
{
	hc_sr04_counter = 0;
	
	// transample_meausureit at least 10 us trigger pulse to the HC-SR04 Trig Pin.
	PORTD |=  (1 << TRIGGER_HCR04_OUTSIDE);
	_delay_us( 10 );
	PORTD &= ~(1 << TRIGGER_HCR04_OUTSIDE);


	while( hc_sr04_counter == 0 );

	if (hc_sr04_counter<1200) {
		return 0.000004 * hc_sr04_counter/2 * 34300;
	} 
	else {
		return 41;
	}
}


ISR( INT0_vect )
{
	if(PIND & (1 << ECHO_HCR04_OUTSIDE)) { //The Port D Input Pins Register - read only
		TCNT1 = 0; // Clear Timer counter 
	}
	else  {
		hc_sr04_counter = TCNT1;
	}	
}









