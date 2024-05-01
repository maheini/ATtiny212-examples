/*
 * buttonpress.h
 *
 * Created: 01.05.2024 22:50:49
 *  Author: Martin
 */ 


#ifndef BUTTONPRESS_H_
#define BUTTONPRESS_H_

/* Listen on specified pin
 * Setup all registers, a pull up resistor and enables interrupts in order to listen on specified pin and call back. 
 * 
 * IMPORTANT: re-listening a pin number will overwrite the callback function!
 * De-bouncing done by the callback function recommended.
 */
void listen_pin(uint8_t pin, void (*callback)());

#endif /* BUTTONPRESS_H_ */