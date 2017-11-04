#ifndef TIMERS_H
#define	TIMERS_H

#include "misc.h"
#define clockCyclesPerMicrosecond() (FCY / 1000000L)
#define clockCyclesToMicroseconds(a) ((a) / clockCyclesPerMicrosecond())
#define microsecondsToClockCycles(a) ((a) * clockCyclesPerMicrosecond())

#define T0_PRESCALER 1
#define MICROSECONDS_PER_TIMER0_OVERFLOW (clockCyclesToMicroseconds(T0_PRESCALER * 65536L))
#define MILLIS_INC (MICROSECONDS_PER_TIMER0_OVERFLOW / 1000)
#define FRACT_INC ((MICROSECONDS_PER_TIMER0_OVERFLOW % 1000) >> 3)
#define FRACT_MAX (1000 >> 3)

#ifndef T0_PRESCALER
#   define TCKPS_0 ERROR
#   error No hay prescaler definido
#else
#   if (T0_PRESCALER == 1)
#       define TCKPS_0 0
#   elif (T0_PRESCALER == 8)
#       define TCKPS_0 1
#   elif (T0_PRESCALER == 64)
#       define TCKPS_0 2
#   elif (T0_PRESCALER == 256)
#       define TCKPS_0 3
#   else
#       define TCKPS_0 ERROR
#       error El prescaler es invalido.
#   endif
#endif

void initTimer1();
unsigned long millis();
unsigned long micros();

#endif