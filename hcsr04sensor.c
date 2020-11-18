#include <avr/io.h>
#include <util/delay.h>

#include "port.h"
#include "servomotor.h"


uint16_t hc_sr04_measure_outside(uint8_t *servo_status_sr04){ // function for the sensor on the outside
	
	uint16_t distance_measure_outside;

	distance_measure_outside = hc_sr04_measure(TRIGGER_HCR04_OUTSIDE, ECHO_HCR04_OUTSIDE); // send defined PINed pins to function
	
	if(distance_measure_outside <= 10){
		servomotor_open(servo_status_sr04);
	}	
	else if(distance_measure_outside >= 11 && *servo_status_sr04 == 1){
			servomotor_close();
			*servo_status_sr04 = 0;
		}
	return distance_measure_outside;
}



uint16_t hc_sr04_measure_inside(void){ // function for the sensor on the inside
 
	uint16_t distance_measure_inside;
	
	distance_measure_inside = hc_sr04_measure(TRIGGER_INSIDE, ECHO_INSIDE);
	
	if(distance_measure_inside <= 3){
		PORTD |= (1<<RED_LED); 
		PORTD &= ~(1<<YELLOW_LED); 
		PORTD &= ~(1<<GREEN_LED);
	}
	else if(distance_measure_inside >= 4 && distance_measure_inside <= 6){
		PORTD |= (1<<YELLOW_LED);
		PORTD &= ~(1<<RED_LED); 
		PORTD &= ~(1<<GREEN_LED);
	}
	else{
		PORTD &= ~(1<<RED_LED); 
		PORTD &= ~(1<<YELLOW_LED);
		PORTD |= (1<<GREEN_LED);

	}	
	return distance_measure_inside;
}


int hc_sr04_measure(int TRIGGER, int ECHO){ // function for reading the sensor values
	
	uint8_t read_status=0;
	uint16_t distance_time=0;
	
	_delay_us(2);
	PORTC |= (1 << TRIGGER);
	_delay_us(10);
	PORTC &= ~(1 << TRIGGER);
	
	while(read_status == 0)
	{
		while(PINC & (1 << ECHO))
		{
			distance_time++;
			read_status = 1;
		}
	}	
	return distance_time * 0.00862;	//return data in cm
}


