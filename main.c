#include "pragma.h"
#include "motores.h"
#include "misc.h"
#include "sensores.h"
#include "timers.h"

void initGPIO(){
    TRIS_LED1 = OUTPUT;
    TRIS_LED2 = OUTPUT;
    TRIS_LED3 = OUTPUT;
    TRIS_SW1 = INPUT;
    TRIS_SW2 = INPUT;
    TRIS_SW3 = INPUT;
}

void setLED(char n, unsigned char v){
    switch(n){
        case 1:
            PORT_LED1 = (v > 0);
            break;
        case 2:
            PORT_LED2 = (v > 0);
            break;
        case 3:
            PORT_LED3 = (v > 0);
            break;
        default: break;
    }
}

void loop(){
    static int estado = MENU;
    static char cal = 0;
    static unsigned long proxMillis = 0;
    static int maxSpeed;
    static int barridos = 0;
    static int btnReady = 0;
    int pid = calcPID();
    switch(estado){
        case MENU:
            setLED(1, ON);
            setLED(2, OFF);
            if(cal){
                setLED(3, ((pid <= PID_THRESHOLD) and (pid >= (-(PID_THRESHOLD)))));
                if(getSW(2)){
                    turnADC(ON);
                    estado = READY;
                    maxSpeed = ARGON_SPEED;
                    btnReady = 2;
                    break;
                }
                if(getSW(3)){
                    turnADC(ON);
                    estado = READY;
                    maxSpeed = LENTO_SPEED;
                    btnReady = 3;
                    break;
                }
            } else setLED(3, OFF);
            if(getSW(1)){
                estado = CAL;
                barridos = 0;
            }
            break;
            
        case READY:
            setLED(1, ON);
            setLED(2, ON);
            setLED(3, OFF);
            if(!getSW(btnReady)){
                estado = RUN;
                setLED(1, OFF);
                setLED(2, OFF);
                setLED(3, ON);
            }
            break;
            
        case CAL:
            if(barridos < MAX_BARRIDOS){
                if(millis() >= proxMillis){
                    barridos++;
                    setLED(2, toggleLED(2));
                    proxMillis += 1000;
                    if(barridos % 2) setMotores((-(BARRIDO_SPEED)), BARRIDO_SPEED);
                    else setMotores(BARRIDO_SPEED, (-(BARRIDO_SPEED)));
                }
            } else {
                setMotores(0, 0);
                estado = MENU;
                cal = 1;
            }
            break;
            
        case RUN:
            if(pid < 0) setMotores((maxSpeed - pid), maxSpeed);
            else setMotores(maxSpeed, (maxSpeed - pid));
            break;
    }
}

int main(){
    initTimer1();
    initADC();
    initPWM();
    initGPIO();
    while(1) loop();
    return 0;
}
