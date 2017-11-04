#include "timers.h"

volatile unsigned long timer0_overflow_count = 0;
volatile unsigned long timer0_millis = 0;
static unsigned char timer0_fract = 0;

void initTimer1(){
    T1CON = 0x0000;
    T1CONbits.TCKPS = TCKPS_0;
    TMR1  = 0x0000;
    PR1   = 0xFFFF;
    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 1;
    T1CONbits.TON = 1;
}

void __attribute__((__interrupt__, auto_psv)) _T1Interrupt(void){
    unsigned long m = timer0_millis + MILLIS_INC;
	unsigned char f = timer0_fract + FRACT_INC;
	if (f >= FRACT_MAX) {
		f -= FRACT_MAX;
		m++;
	}
	timer0_fract = f;
	timer0_millis = m;
	timer0_overflow_count++;
}

unsigned long millis(){
    return timer0_millis;
}

unsigned long micros(){
    return ((timer0_overflow_count << 16) + TMR1) * (T0_PRESCALER / clockCyclesPerMicrosecond());
}
