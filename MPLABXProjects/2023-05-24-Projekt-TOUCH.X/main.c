// Prof. Dr. Artem Ivanov
// HAW Landshut


#include <xc.h> // include processor description
#include "main.h"
#include <math.h>
//#include "Display.c"

#define Key_K3 PORTBbits.RB3
#define Key_K2 PORTDbits.RD8
#define Key_K1 PORTBbits.RB7


void __attribute__((interrupt(auto_psv))) _DefaultInterrupt(void){
    LATCbits.LATC15 = 1 ^ PORTCbits.RC15;     //Default: LED D5 blinkt
}

void __attribute__((interrupt(auto_psv))) _T2Interrupt(void) //Interrupt Timer: 22050 Hz 
{
_T2IF=0; //reset Interrupt flag 
/*DMACH0bits.CHREQ=1;
while(DMACH0bits.CHREQ);*/
}


void __attribute__((interrupt(auto_psv))) _ADC1Interrupt(void){
    //3V = 4096 1V = 1365, 1mV =1.365
    uint32_t x;
    _AD1IF=0;             //Interrupt Flag zurücksetzen
    ADL0CONLbits.SAMP=1;  //Schalter öffnen
    res = ADRES0;         //Tabelle 0 auslesen (VBat/2)
    res2= ADRES1;         //Tabelle 1 auslesen (In1)
    
                  

    
    x= res;               
    x=(x*1000)/1365;
    res=x;
     
    x= res2;
    x=(x*1000)/1365;
    res2=x;
    
    ADL0CONLbits.SAMP=0;   //Schalter schließen

}  



void __attribute__((interrupt(auto_psv))) _T4Interrupt(void){   
    _T4IF=0;
    timer4ms++;
}
void __attribute__((interrupt(auto_psv))) _CNInterrupt(void){       //change notification Interrupt 
        
    key_event=1;
        if(Key_K3==0){           //Taster K3
            SendenFlag=1;
            delaytime4 = timer4ms; 
        }
        if(Key_K2==0){           //Taster K2 - Messung von In1
           delaytime4 = timer4ms;
           ADL0CONLbits.SAMP=0;
           Displayflag=0;
        }
        if(Key_K1==0){           ///Taster K1 - Messung von Vbat/2
           delaytime4 = timer4ms;
           ADL0CONLbits.SAMP=0;
           Displayflag=1;
        }
        _CNIF=0;
    }

void __attribute__((interrupt(auto_psv))) _U1RXInterrupt(void){   

    IFS0bits.U1RXIF = 0;    //Reset Interrupt Flag   
    Display=U1RXREG;
           /* i++;
            if(i>3){
                Display= (uint16_t)(receive_num[0])*1000;
                Display += (uint16_t)(receive_num[1])*100;
                Display += (uint16_t)(receive_num[2])*10;
                Display += (uint16_t)(receive_num[3]);
                Print4Digits_LCD(Display); //Update Display
                i=0;*/
}

void __attribute__((interrupt(auto_psv))) _U1TXInterrupt(void){
    
    _U1TXIF=0;
    
    
    
    
} 


   
    
int main(void)
{
	initialize_HW();
    uint8_t send[6]={0};
    PR1=31250;
    PR2=24999;
    PR4=1999;

	// main loop:
    Print4Digits_LCD(Display);
    send[0]=0xff;
    send[1]=0xff;
    
	while(1){
        

        if(Displayflag==1){
            
        Print4Digits_LCD(res);}else{Print4Digits_LCD(res2);}
        
        
            if(SendenFlag==1){
                if(((timer4ms-delaytime4)>entprellzeit)&&PORTBbits.RB3==0)  //nach der entprellzeit wird der Ausgang beschrieben
                   

                    SendenFlag = 0;                              //Tasterflag zurücksetzen
                    key_event=0;
                    Print4Digits_LCD(res); //Update Display
                }else if(((timer4ms-delaytime4)>entprellzeit)&&PORTBbits.RB3==1){SendenFlag = 0; key_event=0;}
            }

//             if(_ADBUSY==1){
//                 LATCbits.LATC12 = 1;
//             }else{LATCbits.LATC12 = 1;}   
//        
        
            if(U1STAbits.OERR == 1){
                    
                U1STAbits.OERR = 0;    
            }
        
            if(U1STAbits.FERR == 1){
                U1STAbits.FERR = 0;
            }
        
        
        if(_T1IF==1){
            //LATCbits.LATC12 = 1 ^ PORTCbits.RC12;
            LCDDATA1bits.S23C0=1^LCDDATA1bits.S23C0;
            _T1IF=0;  
        }	
        
    }
}



void PrintDigit_LCD(uint16_t segment,uint16_t nummer){
        if(segment==1)
        {
        switch(nummer){//a,b,c,d,e,f,g
            case 0: _S22C3=1;_S22C2=1;_S23C3=1;_S22C0=1;_S23C1=1;_S23C2=1;_S22C1=0; break; //a,b,c,d,e,f
            case 1: _S22C3=0;_S22C2=1;_S23C3=1;_S22C0=0;_S23C1=0;_S23C2=0;_S22C1=0; break; //b,c
            case 2: _S22C3=1;_S22C2=1;_S23C3=0;_S22C0=1;_S23C1=1;_S23C2=0;_S22C1=1; break; //a,b,d,e,g
            case 3: _S22C3=1;_S22C2=1;_S23C3=1;_S22C0=1;_S23C1=0;_S23C2=0;_S22C1=1; break; //a,b,c,d,g
            case 4: _S22C3=0;_S22C2=1;_S23C3=1;_S22C0=0;_S23C1=0;_S23C2=1;_S22C1=1; break; //b,c,f,g
            case 5: _S22C3=1;_S22C2=0;_S23C3=1;_S22C0=1;_S23C1=0;_S23C2=1;_S22C1=1; break; //a,c,d,f,g
            case 6: _S22C3=1;_S22C2=0;_S23C3=1;_S22C0=1;_S23C1=1;_S23C2=1;_S22C1=1; break; //a,c,d,e,f,g
            case 7: _S22C3=1;_S22C2=1;_S23C3=1;_S22C0=0;_S23C1=0;_S23C2=0;_S22C1=0; break; //a,b,c
            case 8: _S22C3=1;_S22C2=1;_S23C3=1;_S22C0=1;_S23C1=1;_S23C2=1;_S22C1=1; break; //a,b,c,d,e,f,g
            case 9: _S22C3=1;_S22C2=1;_S23C3=1;_S22C0=1;_S23C1=0;_S23C2=1;_S22C1=1; break; //a,b,c,d,f,g
                
            default: break;}
        
        }
        
                
        if(segment==2)
        {
        switch(nummer){//a,b,c,d,e,f,g
            case 0: _S20C3=1;_S20C2=1;_S21C3=1;_S20C0=1;_S21C1=1;_S21C2=1;_S20C1=0; break; //a,b,c,d,e,f
            case 1: _S20C3=0;_S20C2=1;_S21C3=1;_S20C0=0;_S21C1=0;_S21C2=0;_S20C1=0; break; //b,c
            case 2: _S20C3=1;_S20C2=1;_S21C3=0;_S20C0=1;_S21C1=1;_S21C2=0;_S20C1=1; break; //a,b,d,e,g
            case 3: _S20C3=1;_S20C2=1;_S21C3=1;_S20C0=1;_S21C1=0;_S21C2=0;_S20C1=1; break; //a,b,c,d,g
            case 4: _S20C3=0;_S20C2=1;_S21C3=1;_S20C0=0;_S21C1=0;_S21C2=1;_S20C1=1; break; //b,c,f,g
            case 5: _S20C3=1;_S20C2=0;_S21C3=1;_S20C0=1;_S21C1=0;_S21C2=1;_S20C1=1; break; //a,c,d,f,g
            case 6: _S20C3=1;_S20C2=0;_S21C3=1;_S20C0=1;_S21C1=1;_S21C2=1;_S20C1=1; break; //a,c,d,e,f,g
            case 7: _S20C3=1;_S20C2=1;_S21C3=1;_S20C0=0;_S21C1=0;_S21C2=0;_S20C1=0; break; //a,b,c
            case 8: _S20C3=1;_S20C2=1;_S21C3=1;_S20C0=1;_S21C1=1;_S21C2=1;_S20C1=1; break; //a,b,c,d,e,f,g
            case 9: _S20C3=1;_S20C2=1;_S21C3=1;_S20C0=1;_S21C1=0;_S21C2=1;_S20C1=1; break; //a,b,c,d,f,g
                
            default: break;}
        
        }
        
                
        if(segment==3)
        {
        switch(nummer){//a,b,c,d,e,f,g
            case 0: _S16C3=1;_S16C2=1;_S17C3=1;_S16C0=1;_S17C1=1;_S17C2=1;_S16C1=0; break; //a,b,c,d,e,f
            case 1: _S16C3=0;_S16C2=1;_S17C3=1;_S16C0=0;_S17C1=0;_S17C2=0;_S16C1=0; break; //b,c
            case 2: _S16C3=1;_S16C2=1;_S17C3=0;_S16C0=1;_S17C1=1;_S17C2=0;_S16C1=1; break; //a,b,d,e,g
            case 3: _S16C3=1;_S16C2=1;_S17C3=1;_S16C0=1;_S17C1=0;_S17C2=0;_S16C1=1; break; //a,b,c,d,g
            case 4: _S16C3=0;_S16C2=1;_S17C3=1;_S16C0=0;_S17C1=0;_S17C2=1;_S16C1=1; break; //b,c,f,g
            case 5: _S16C3=1;_S16C2=0;_S17C3=1;_S16C0=1;_S17C1=0;_S17C2=1;_S16C1=1; break; //a,c,d,f,g
            case 6: _S16C3=1;_S16C2=0;_S17C3=1;_S16C0=1;_S17C1=1;_S17C2=1;_S16C1=1; break; //a,c,d,e,f,g
            case 7: _S16C3=1;_S16C2=1;_S17C3=1;_S16C0=0;_S17C1=0;_S17C2=0;_S16C1=0; break; //a,b,c
            case 8: _S16C3=1;_S16C2=1;_S17C3=1;_S16C0=1;_S17C1=1;_S17C2=1;_S16C1=1; break; //a,b,c,d,e,f,g
            case 9: _S16C3=1;_S16C2=1;_S17C3=1;_S16C0=1;_S17C1=0;_S17C2=1;_S16C1=1; break; //a,b,c,d,f,g
                
            default: break;}
        
        }
        
                
        if(segment==4)
        {
        switch(nummer){//a,b,c,d,e,f,g
            case 0: _S14C3=1;_S14C2=1;_S15C3=1;_S14C0=1;_S15C1=1;_S15C2=1;_S14C1=0; break; //a,b,c,d,e,f
            case 1: _S14C3=0;_S14C2=1;_S15C3=1;_S14C0=0;_S15C1=0;_S15C2=0;_S14C1=0; break; //b,c
            case 2: _S14C3=1;_S14C2=1;_S15C3=0;_S14C0=1;_S15C1=1;_S15C2=0;_S14C1=1; break; //a,b,d,e,g
            case 3: _S14C3=1;_S14C2=1;_S15C3=1;_S14C0=1;_S15C1=0;_S15C2=0;_S14C1=1; break; //a,b,c,d,g
            case 4: _S14C3=0;_S14C2=1;_S15C3=1;_S14C0=0;_S15C1=0;_S15C2=1;_S14C1=1; break; //b,c,f,g
            case 5: _S14C3=1;_S14C2=0;_S15C3=1;_S14C0=1;_S15C1=0;_S15C2=1;_S14C1=1; break; //a,c,d,f,g
            case 6: _S14C3=1;_S14C2=0;_S15C3=1;_S14C0=1;_S15C1=1;_S15C2=1;_S14C1=1; break; //a,c,d,e,f,g
            case 7: _S14C3=1;_S14C2=1;_S15C3=1;_S14C0=0;_S15C1=0;_S15C2=0;_S14C1=0; break; //a,b,c
            case 8: _S14C3=1;_S14C2=1;_S15C3=1;_S14C0=1;_S15C1=1;_S15C2=1;_S14C1=1; break; //a,b,c,d,e,f,g
            case 9: _S14C3=1;_S14C2=1;_S15C3=1;_S14C0=1;_S15C1=0;_S15C2=1;_S14C1=1; break; //a,b,c,d,f,g
                
            default: break;}
        
        }
        
    }


 void Print4Digits_LCD(uint16_t digits){
        
        uint16_t seg1,seg2,seg3,seg4;
        
        seg1=(digits-(digits%1000))/1000;
        seg2=((digits-(seg1*1000))-(digits%100))/100;
        seg3=((digits-(seg1*1000)-(seg2*100))-(digits%10))/10;
        seg4=digits-(seg1*1000)-(seg2*100)-(seg3*10);
        
        PrintDigit_LCD(1,seg1);
        PrintDigit_LCD(2,seg2);
        PrintDigit_LCD(3,seg3);
        PrintDigit_LCD(4,seg4);
    }
