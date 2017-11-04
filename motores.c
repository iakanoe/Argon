#include "motores.h"

void initPWM(){
    TRIS_DIR_D  = OUTPUT;
    TRIS_PWM_D  = OUTPUT;
    TRIS_DIR_I  = OUTPUT;
    TRIS_PWM_I  = OUTPUT;
    LAT_DIR_D = 0;
    LAT_DIR_I = 0;
    
    PTCON       = 0x0000;
    PTMR        = 0x0000;
    PTPER       = (int) ((FCY / FPWM) - 1);
    SEVTCMP     = 0x0000;
    PWMCON1     = 0x0030;
    PWMCON2     = 0x0000;
    DTCON1      = 0x0000;
    FLTACON     = 0x0000;
    OVDCON      = 0xFF00;
    PTCON = PTMR = SEVTCMP = PWMCON2 = DTCON1 = FLTACON = PDC1 = PDC2 = PDC3 = 0x0000;
    PDC2        = 0x0000;
    PDC3        = 0x0000;
    
    PTCONbits.PTEN = 1;
}

void setMotores(long izq, long der){
    LAT_DIR_I = (izq < 0);
    LAT_DIR_D = (der < 0);
    izq = ((izq < -10000) ? -10000 : ((izq > 10000)) ? 10000 : izq) + ((izq < 0) * 10000);
    der = ((der < -10000) ? -10000 : ((der > 10000)) ? 10000 : der) + ((der < 0) * 10000);
    PDC1 = ((unsigned int) map(izq, 0, 10000, 0, 0xFFFF));
    PDC2 = ((unsigned int) map(der, 0, 10000, 0, 0xFFFF));
}
