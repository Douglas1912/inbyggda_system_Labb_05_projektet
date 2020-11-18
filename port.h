#ifndef _PORT_H_
#define _PORT_H_

#define SERVOMOTOR PB1
#define YELLOW_LED PD5
#define RED_LED PD6
#define GREEN_LED PD4

#define TRIGGER_HCR04_OUTSIDE PC0
#define ECHO_HCR04_OUTSIDE PC1
#define TRIGGER_INSIDE PC5
#define ECHO_INSIDE PC4


void port_init();

#endif 
