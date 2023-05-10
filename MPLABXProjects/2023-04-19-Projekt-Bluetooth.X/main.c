// Prof. Dr. Artem Ivanov
// HAW Landshut


#include <xc.h> // include processor description
#include "main.h"
#include <math.h>

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
void __attribute__((interrupt(auto_psv))) _CNInterrupt(void){       //change notification Interrupt 
        
    key_event=1;
        if(PORTBbits.RB3==0){           //Taster K3
            freqflag=1;
            delaytime4 = timer4ms; 
        }
        if(PORTDbits.RD8==0){           //Taster K2
           freqflag=2;
           delaytime4 = timer4ms;
        }
        if(PORTBbits.RB7==0){           ///Taster K1
           soundflag=1;
           delaytime4 = timer4ms;
        }
        _CNIF=0;
    }

    
int main(void)
{
	initialize_HW();
    uint16_t i;
    PR1=31250;
    PR2=725;
    PR4=1999;
    uint16_t freq =1;
	// main loop:

    for(i=0;i<=255;i++){
        
        Array[i]=(int)128*sin((i/255.0)*6.28*freq)+128;
    }
    
    DMAH=(uint16_t)&Array[0]+(256*sizeof(uint16_t));                //Obere Adressgrenze (?)
    DMAL=(uint16_t) &Array[0];                 //untere Adressgrenze(?)


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
        
                    
        if(freqflag==1){
            if(((timer4ms-delaytime4)>entprellzeit)&&PORTBbits.RB3==0)  //nach der entprellzeit wird der Ausgang beschrieben    
            {  
                freq ++;                               //Frequenz erhöhen
                                
                if(freq>10){freq=10;}
                    for(i=0;i<=255;i++){
                        Array[i]=(int)128*sin((i/255.0)*6.28*freq)+128;
                    }
                freqflag = 0;                              //Tasterflag zurücksetzen
                key_event=0;
            }else if(((timer4ms-delaytime4)>entprellzeit)&&PORTBbits.RB3==1){freqflag = 0; key_event=0;}
        }
        
                
        if(freqflag==2){
            if(((timer4ms-delaytime4)>entprellzeit)&&PORTDbits.RD8==0)  //nach der entprellzeit wird der Ausgang beschrieben    
            {  
                
                freq --;                                     //Frequenz niedriger
                if(freq<0){freq=0;}
                    for(i=0;i<=255;i++){
                        Array[i]=(int)128*sin((i/255.0)*6.28*freq)+128;
    }
                freqflag = 0;                              //Tasterflag zurücksetzen
                key_event=0;
            }else if(((timer4ms-delaytime4)>entprellzeit)&&PORTDbits.RD8==1){freqflag = 0; key_event=0;}
        }
        
                
        if(soundflag==1){
            if(((timer4ms-delaytime4)>entprellzeit)&&PORTBbits.RB7==0)  //nach der entprellzeit wird der Ausgang beschrieben    
            {  
                LATBbits.LATB12 = 1 ^ PORTBbits.RB12;
                soundflag = 0;                              //Tasterflag zurücksetzen
                key_event=0;
            }else if(((timer4ms-delaytime4)>entprellzeit)&&PORTBbits.RB7==1){soundflag = 0; key_event=0;}
        }
        

    }
}

