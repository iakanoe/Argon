#ifndef PRAGMA_H
#define	PRAGMA_H
#ifdef INT_OSC
    #pragma config FPR = FRC_PLL16
#else
    #pragma config FPR = XT_PLL16
#endif
#pragma config FOS = PRI
#pragma config FCKSMEN = CSW_FSCM_OFF
#pragma config FWPSB = WDTPSB_1
#pragma config FWPSA = WDTPSA_1
#pragma config WDT = WDT_OFF
#pragma config FPWRT = PWRT_OFF
#pragma config BODENV = BORV20
#pragma config BOREN = PBOR_OFF
#pragma config LPOL = PWMxL_ACT_HI
#pragma config HPOL = PWMxH_ACT_HI
#pragma config PWMPIN = RST_IOPIN
#pragma config MCLRE = MCLR_DIS
#pragma config GWRP = GWRP_OFF
#pragma config GCP = CODE_PROT_OFF
#pragma config ICS = ICS_PGD
#include "misc.h"
#endif

