#ifndef _HCSR04SENSOR_H_
#define _HCSR04SENSOR_H_


uint16_t hc_sr04_measure_outside(uint8_t *servo_status_sr04);
uint16_t hc_sr04_measure_inside(void);
int hc_sr04_measure(int TRIGGER, int ECHO);

#endif // _HCSR04SENSOR_H_
