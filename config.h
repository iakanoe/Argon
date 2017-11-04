#ifndef CONFIG_H
#define	CONFIG_H
#include <xc.h>

#define PRESCALER 16
#define FOSC (XTAL_FREQ * PRESCALER)
#define FCY (FOSC / 4)

#define map(x, a, b, c, d) ((x - a) * (d - c) / (b - a) + c)

//definir si se usa el interno, comentar si se usa un xtal//
#define INT_OSC

#ifdef INT_OSC
    #define XTAL_FREQ 7372800
#else
    #define XTAL_FREQ 6000000
#endif
#endif