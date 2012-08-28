


#include "GPIO.h"

short int set_dir(short int port_num, short int pin_num, short int dir)
{
	short int target_pin = (1 << pin_num);
	
	if (GPIO_OUTPUT<dir || 2<port_num || 0 == port_num || 7<pin_num)
		return ERROR_STAT;
	
	if (1 == port_num) {
		(GPIO_OUTPUT == dir) ? (P1DIR |= target_pin) : (P1DIR &= ~target_pin);
		P1SEL &= ~target_pin;
		P1SEL2 &= ~target_pin;
		return SUCCESS;
	} else if (2 == port_num) {
		(GPIO_OUTPUT == dir) ? (P2DIR |= target_pin) : (P2DIR &= ~target_pin);
		P2SEL &= ~target_pin;
		P2SEL2 &= ~target_pin;
		return SUCCESS;
	}
		return ERROR_STAT;
}

short int set_pullup_resistors(short int port, short int pin)
{
	short int target_pin = (1 << pin);
	
	if (1 == port) {
		if (0 == (P1DIR & target_pin))
			return ERROR_STAT;
		
		P1REN |= target_pin;
	} else if (2 == port) {
		if (0 == (P2DIR & target_pin))
			return ERROR_STAT;
		
		P2REN |= target_pin;
	} else
		return ERROR_STAT;
	
	return SUCCESS;
}

short int set_value(short int port, short pin)
{
	if (1 == port) {
		P1OUT |= (1 << pin);
		P1OUT |= P1REN;
	} else if (2 == port) {
		P2OUT |= (1 << pin);
		P2OUT |=  P2REN;
	} else
		return ERROR_STAT;
	
	return SUCCESS;
}

short int interrupt_command(short int port, short int pin, short int edge)
{
	short int target_pin = 1 << pin;
	
	if (1<edge)
		return ERROR_STAT;
	
	if (1 == port) {
		if (P1DIR & target_pin)
			return ERROR_STAT;
		
		P1IE |= target_pin;
		if (GPIO_RISING_EDGE == edge)
			P1IES |= target_pin;
		else
			P1IES &= ~target_pin;
		
		P1IFG |= target_pin;
		
	} else if (2 == port) {
		if (P2DIR & target_pin)
			return ERROR_STAT;
		
	} else
		return ERROR_STAT;
	
	return SUCCESS;
}

short int read_value(short int port, short int pin)
{
	if (port>2 || pin>7 || port<1 || pin<0)
		return ERROR_STAT;
	
	if (1 == port)
		return (1<<pin) & P1IN;
	else if (2 == port)
		return (1<<pin) &  P2IN;
	
	// this return staments for defeating compiler's warning 
	// "missing return statements"
	return SUCCESS;
}