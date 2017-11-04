#include "sensores.h"

int values[9];
int max[9];
int min[9];

const float Kp = 0.0;
const float Ki = 0.0;
const float Kd = 0.0;
const int setpoint = 500;

int calcPID(){
    static int prevErr, err, integral; 
    unsigned long long s1 = 0, s2 = 0;
    for(int i = 0; i < 9; i++){
        s1 += values[i] * 100 * (i + 1);
        s2 += values[i];
    }
    int pos = (s1 / s2); // promedio ponderado | posición respecto a la linea
    prevErr = err; // guarda el error antiguo para derivada
    err = setpoint - pos; // calcula el error
    integral += err; // suma el error a la integral
    return ((int) (Kp * (float) err) + (Ki * (float) integral) + (Kd * (float) (err - prevErr)));
    //calcula el PID y lo devuelve
}

#ifndef MODE_ADVANCED
void initADC(){
    //todo supuesto con clock externo de 20MHz a HS con 1 de prescaler
    TRISB = ((1 << 9) - 1); // todo como salidas
    ADPCFG = (~((1 << 9) - 1)); // todos los pines analogicos posibles
    ADCSSL = 0; // VER SI ANDA ASI SINO CAMBIAR A TODOS 1
    ADCHS = 0; // selecciona todo como vref- | despues escribir numero del 0 al 8 para seleccionar input (ANx)
    ADCON3 = 259; // Tad = 2Tcy | ir subiendo de a 1 si no anda 
    ADCON2 = 0; // solo canal 0 | avss y avdd como ref | un solo sample | palabra 16 bits
    ADCON1 = 32993; // secuencialmente | auto convert | right-justified | ADC encendido
    for(int i = 0; i < 9; i++){
        max[i] = 0; // inicializa maximos a 0
        min[i] = 1024; // inicializa minimos a 1024
    }
}

void readCNY(){
    for(int i = 0; i < 9; i++){
        ADCBUF0 = 0; // borra el buffer para que se pueda reescribir
        ADCHS = i; // selecciona el input (ANi)
        ADCON1bits.SAMP = 1; // empezar la secuencia
        while(!ADCON1bits.DONE) continue; // espera a que termine
        int v = ADCBUF0; // lee valor
        if(v < min[i]) min[i] = v; // ajusta calibracion
        if(v > max[i]) max[i] = v; // ajusta calibracion
        values[i] = map(v, min[i], max[i], 0, 1000); // convierte a valor calibrado 0-1000
    }
}

#else
const volatile unsigned int * bufs[] = {
    (&ADCBUF0),
    (&ADCBUF1),
    (&ADCBUF2),
    (&ADCBUF3),
    (&ADCBUF4),
    (&ADCBUF5),
    (&ADCBUF6),
    (&ADCBUF7),
    (&ADCBUF8)
};

void initADC(){
    for(int i = 0; i < 9; i++){
        max[i] = 0; // inicializa maximos a 0
        min[i] = 1024; // inicializa minimos a 1024
    }
    TRISB  = 0x00FF;    // todo inputs
    ADCON1 = 0x20E4;    // ADSIDL = 1 | SSRC = 7 | ASAM = 1 | el resto 0
    ADCON2 = 0x0420;    // CSCNA = 1 | SMPI = 8 | el resto 0
    ADCON3 = 0x0100 | ADCS_MIN;    // SAMC = 1 | ADCS = 3 | el resto 0
    ADCHS  = 0x0000;    // selecciona canal 0
    ADPCFG = 0xFE00;    // todo inputs para adc
    ADCSSL = 0x01FF;    // leer todo como ch0
    IFS0bits.ADIF = 0;
    IEC0bits.ADIE = 1;
}

void turnADC(int v){
    if(v != OFF or v != ON) return;
    ADCON1bits.ADON = v;
}

void __attribute__((__interrupt__, auto_psv)) _ADCInterrupt(void) {
    for(int i = 0; i < 9; i++){
        unsigned int v = (*bufs[i]);
        if(v < min[i]) min[i] = v;
        if(v > max[i]) max[i] = v;
        values[i] = map(v, min[i], max[i], 0, 1000);
    }
    IFS0bits.ADIF = 0;
}
#endif
