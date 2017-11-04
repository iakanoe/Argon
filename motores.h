#ifndef MOTORES_H
#define	MOTORES_H
#include "misc.h"

#define TRIS_DIR_D TRISEbits.TRISE0
#define LAT_DIR_D LATEbits.LATE0
#define TRIS_PWM_D TRISEbits.TRISE1
#define TRIS_DIR_I TRISEbits.TRISE2
#define LAT_DIR_I LATEbits.LATE2
#define TRIS_PWM_I TRISEbits.TRISE3

#define FPWM 25000

void initPWM();
void setMotores(long izq, long der);

#endif