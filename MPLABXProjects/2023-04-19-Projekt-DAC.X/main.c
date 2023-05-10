// Prof. Dr. Artem Ivanov
// HAW Landshut


#include <xc.h> // include processor description
#include "main.h"



void __attribute__((interrupt(auto_psv))) _DefaultInterrupt(void){
    LATCbits.LATC15 = 1 ^ PORTCbits.RC15;     //Default: LED D5 blinkt
}


void __attribute__((interrupt(auto_psv))) _T2Interrupt(void) //Interrupt Timer: 22050 Hz 
{
_T2IF=0; //reset Interrupt flag

/*DMACH0bits.CHREQ=1;
while(DMACH0bits.CHREQ);*/

}

void __attribute__((interrupt(auto_psv))) _T4Interrupt(void){   
    _T4IF=0;
    timer4ms++;
}


    
int main(void)
{
	initialize_HW();
    uint8_t i;
    PR1=31250;
    PR2=725;
    PR4=1999;
    
	// main loop:

    for(i=0;i<255;i++){
        
        Array[i]=i;
    }
    
    DMAH=(uint16_t)&Array[0]+(256*sizeof(uint16_t));    //Obere Adressgrenze 
    DMAL=(uint16_t) &Array[0];                          //untere Adressgrenze


    DMASRC0=(uint16_t)&Array[0];
    DMADST0=(uint16_t)&DAC1DAT; 
    DMACNT0=256;
    DMACH0bits.CHEN=0b1;
    DMAINT0bits.CHSEL = 0b110101;   //Timer2 Interrupt als DMA Channel trigger
    IFS0bits.DMA0IF=0;
        
	while(1){
                    
        
        if(_T1IF==1){
        
            //LATCbits.LATC12 = 1 ^ PORTCbits.RC12;
            LCDDATA1bits.S23C0=1^LCDDATA1bits.S23C0;
            _T1IF=0;  
        }	
        
        

    }
}

