// Prof. Dr. Artem Ivanov
// HAW Landshut


#include <xc.h> // include processor description
#include "main.h"



    void _ISR _T2Interrupt(void){
        
        _T2IF=0; //reset Interrupt flag
        
        LATCbits.LATC15 = 1 ^ PORTCbits.RC15;
    }


int main(void)
{
	initialize_HW();
    uint16_t xalt = 0;
    uint16_t xneu = 0;
    uint16_t xalt2 = 0;
    uint16_t xneu2 = 0;

    
    
    IEC0bits.T2IE = 1;
    
    PR1=31250;
    PR2=15625;
	// main loop:
    
    
    //Interrupts
    
    

        
    
	while(1)
	{
        xneu = 0;
        xneu2=0;
        if(PORTBbits.RB3==0){
            xneu=1;
            if(xneu == 1 && xalt == 0){     // Flankenerkennung
            
            LATCbits.LATC12 = 1 ^ PORTCbits.RC12;

            }}
       if(PORTDbits.RD8==0){
            xneu2=1;
            if(xneu2 == 1 && xalt2 == 0){ 
           LATCbits.LATC15 = 1 ^ PORTCbits.RC15;
            }}

        if(_T1IF==1){
            LATCbits.LATC12 = 1 ^ PORTCbits.RC12;
            _T1IF=0;
        }
            
        
                
       xalt = xneu; 
       xalt2=xneu2;

	}	
}	

