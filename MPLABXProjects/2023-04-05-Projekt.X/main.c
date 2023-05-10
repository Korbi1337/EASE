// Prof. Dr. Artem Ivanov
// HAW Landshut


#include <xc.h> // include processor description
#include "main.h"



uint16_t maxtime=65000;      //zählerüberlauf verhindern
uint32_t timer4ms = 0;       //Globale Zählervariable Systemzeit
uint16_t LEDD6_FLAG = 0;     //Globales Flag LED D6 togglen
uint16_t delaytime4 = 0;     //Vergleichswert für Entprellzeit
uint16_t LEDD5_FLAG = 0;

    void _ISR _T2Interrupt(void){      //Interrupt Timer: 2Hz Blinken LED D5
        
        _T2IF=0; //reset Interrupt flag
        
        //LATCbits.LATC15 = 1 ^ PORTCbits.RC15;
    }
    
    void _ISR _T4Interrupt(void){       //Interrupt Timer: Globale Systemzeit
        _T4IF=0;
        timer4ms++;
        if(timer4ms>=maxtime)
        {
            timer4ms=0;
        }
    }

    void _ISR _CNInterrupt(void){       //change notification Interrupt 
        
        if(PORTBbits.RB3==0){           //Taster K3
            LEDD6_FLAG=1;
            delaytime4 = timer4ms; 
        }
        if(PORTDbits.RD8==0){           //Taster K2
           LEDD5_FLAG=1;
           delaytime4 = timer4ms;
        }
        if(PORTBbits.RB7==0){           ///Taster K1
           LEDD6_FLAG=1;
           delaytime4 = timer4ms;
        }
        _CNIF=0;
    }

int main(void)
{
	initialize_HW();
    
    uint16_t entprellzeit=4;      //Entprellzeit in ms
       
    PR1=31250;
    PR2=15625;
    PR4=2000;
	// main loop:
    
	while(1){


        /*if(PORTBbits.RB3==0)
        {
            xneu=1;
            if(xneu == 1 && xalt == 0) // Flankenerkennung
            {     
            LATCbits.LATC12 = 1 ^ PORTCbits.RC12;
            }
        }*/
       /*if(PORTDbits.RD8==0){
            xneu2=1;
            if(xneu2 == 1 && xalt2 == 0){ 
           LATCbits.LATC15 = 1 ^ PORTCbits.RC15;
            }}*/

        
       /* if(_T1IF==1)
        {
            LATCbits.LATC12 = 1 ^ PORTCbits.RC12;
            _T1IF=0;
        }*/
        

        
        /*if(PORTBbits.RB7==0)                //Ansteuerung LED D5 mit Taster K1
        {
            LEDD6_FLAG=1;                        //Taster gedrückt - Flankenerkennung Flag
            delaytime4 = timer4ms;          //Übergabe der aktuellen Systemzeit
        }*/
        
           
        if(LEDD6_FLAG==1){
            if((timer4ms-delaytime4)>entprellzeit)  //nach der entprellzeit wird der Ausgang beschrieben
            {
                LATCbits.LATC12 = 1 ^ PORTCbits.RC12;
                LEDD6_FLAG = 0;                              //Tasterflag zurücksetzen
            }   
        }
        
        
        /*if(PORTDbits.RD8==0)
        {
            LEDD5_FLAG=1;
            delaytime4 = timer4ms;
        }*/
           
        if(LEDD5_FLAG==1){
            if((timer4ms-delaytime4)>entprellzeit)
                {
                LATCbits.LATC15 = 1 ^ PORTCbits.RC15;
                LEDD5_FLAG = 0;
                }
           }
        
	}	
}