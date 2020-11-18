#include <avr/io.h>
#include <util/delay.h>


uint8_t servomotor_open(uint8_t *servo_status_sm)
{
	if(*servo_status_sm == 0){ 
		OCR1A=400;   // duty cycle Move the servo to position
		_delay_ms( 900 ); // wait for the motor to move in position
		*servo_status_sm = 1; // sets status pointer if the sensor is still triggerd so the motor doesn´t run again 
	}
	OCR1A=0;  //clear to stop the buzzing
	_delay_ms( 3000 ); // delay to keep the bin open for 3sec
	return 0;
}

void servomotor_close()
{
	OCR1A=100;  // duty cycle Return the servo to position
	_delay_ms(500);
	OCR1A=0;  

}

