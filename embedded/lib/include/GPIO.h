
#if !defined (GPIO_H)
#define GPIO_H

#include "io430.h"
#include "in430.h"

#define ERROR_STAT -1
#define SUCCESS 0

#define GPIO_FALLING_EGDE 0
#define GPIO_RISING_EDGE 1

#define GPIO_INPUT 0
#define GPIO_OUTPUT 1

short int set_dir(short int port_num, short int pin_num, short int dir);
short int set_pullup_resistors(short int port, short int pin);
short int set_value(short int port, short pin);
short int interrupt_command(short int port, short int pin, short int edge);
short int read_value(short int port, short int pin);

#endif