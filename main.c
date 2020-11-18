#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

#include "serial.h"
#include "timer.h"
#include "port.h"
#include "hcsr04sensor.h"
#include "servomotor.h"

int main(void)
{
	
	uint8_t servo_status = 0;
	uint16_t sample_from_hcsr04_inside;
	uint16_t sample_from_hcsr04_outside;
	
	uart_init();	
	timer_init();
	port_init();	
	
    while(1)
    {	
		sample_from_hcsr04_inside = hc_sr04_measure_inside();
		sample_from_hcsr04_outside = hc_sr04_measure_outside(&servo_status);
    }
}
