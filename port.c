#include <avr/io.h>
#include "port.h"

void port_init()
{
	DDRB |= (1<<SERVOMOTOR);
	DDRD |= (1<<RED_LED) | (1<<YELLOW_LED) | (1<<GREEN_LED); // for the LED
	DDRC |= (1<<TRIGGER_INSIDE) | (0<<ECHO_INSIDE) | (1<<TRIGGER_HCR04_OUTSIDE) | (0<<ECHO_HCR04_OUTSIDE) ; //// Set TRIGGER as output. Set ECHO input
}
