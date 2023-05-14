// Prof. Dr. Artem Ivanov
// HAW Landshut


#include <xc.h> // include processor description
#include "main.h"
#include <math.h>
//#include "Display.c"

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
            U1TXREG=0x55;
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

void __attribute__((interrupt(auto_psv))) _UART1ReceiverInterrupt(void){   
    IFS0bits.U1RXIF = 0;    //Reset Interrupt Flag
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
        
        
    uint8_t Receive = 0; //Empfangenes UART Bit
    
    
    
    Print4Digits_LCD(Receive);
        
        /* Check for receive errors */
        if(U1STAbits.FERR == 1){
            LATCbits.LATC15 = 1 ^ PORTCbits.RC15;   //LED D6 zu Debug Zwecken
//            continue;
        }
        
        /* Must clear the overrun error to keep UART receiving */
        if(U1STAbits.OERR == 1){
            U1STAbits.OERR = 0;
            LATCbits.LATC15 = 1 ^ PORTCbits.RC15;   //LED D6 zu Debug Zwecken
//            continue;
        }
        
        if(U1STAbits.URXDA == 1){                   //Daten im UART1 Receive Buffer
            LATCbits.LATC15 = 1 ^ PORTCbits.RC15;   //LED D6 zu Debug Zwecken
            Receive = U1RXREG;                      //Empfangenes UART Byte Variable zuweisen
        }
        
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
                
                
                                             //Tasterflag zurücksetzen
                key_event=0;
            }else if(((timer4ms-delaytime4)>entprellzeit)&&PORTDbits.RD8==1){key_event=0;}
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

