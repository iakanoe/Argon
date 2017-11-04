#ifndef SENSORES_H
#define	SENSORES_H
#include "misc.h"


void initADC();
int calcPID();

#define TAD_MIN 0.00000015385
#define ADCS_MIN (((int) (2 * TAD_MIN * FCY)) - 1)

#define MODE_ADVANCED //definir si se usa el modo avanzado, gana procesamiento pero no está testeado
#ifndef MODE_ADVANCED 
    void readCNY();
#else
    void turnADC(int v);
#endif

#endif

