#ifndef CONFIG_H
#define	CONFIG_H
#include <xc.h>

#define map(x, a, b, c, d) ((x - a) * (d - c) / (b - a) + c)

//definir si se usa el interno, comentar si se usa un xtal//
//#define INT_OSC

#ifdef INT_OSC
#   define XTAL_FREQ 7372800L
#else
#   define XTAL_FREQ 6000000L
#endif

#define PLL_MULTIPLIER 16
#define FOSC (XTAL_FREQ * PLL_MULTIPLIER)
#define FCY (FOSC / 4)

#define TRIS_LED1 TRISEbits.TRISE8
#define PORT_LED1 LATEbits.LATE8
#define TRIS_LED2 TRISDbits.TRISD1
#define PORT_LED2 LATDbits.LATD1
#define TRIS_LED3 TRISDbits.TRISD3
#define PORT_LED3 LATDbits.LATD3

#define TRIS_SW1 TRISDbits.TRISD2
#define PORT_SW1 PORTDbits.RD2
#define TRIS_SW2 TRISDbits.TRISD0
#define PORT_SW2 PORTDbits.RD0
#define TRIS_SW3 TRISFbits.TRISF6
#define PORT_SW3 PORTFbits.RF6

enum {OUTPUT, INPUT};
enum {MENU, RUN, CAL, READY};
enum {OFF, ON};

#define ERROR 0xFF
#define SW_PRESSED 0

#define or ||
#define and &&

#define MAX_BARRIDOS 5
#define BARRIDO_SPEED 1000

#define LENTO_SPEED 5000
#define ARGON_SPEED 10000

#define toggleLED(n) (n == 1 ? (!PORT_LED1) : (n == 2 ? (!PORT_LED2) : (n == 3 ? (!PORT_LED3) : ERROR)))
#define getSW(n) (n == 1 ? (PORT_SW1 == SW_PRESSED) : (n == 2 ? (PORT_SW2 == SW_PRESSED) : (n == 3 ? (PORT_SW3 == SW_PRESSED) : ERROR)))

#define PID_THRESHOLD 100

#endif