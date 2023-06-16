// Prof. Dr. Artem Ivanov
// HAW Landshut


#include <xc.h> // include processor description
#include "main.h"
#include <math.h>
//#include "Display.c"

#define Key_K3 PORTBbits.RB3
#define Key_K2 PORTDbits.RD8
#define Key_K1 PORTBbits.RB7
#define Chipselect PORTEbits.RE5
#define LEDD6   PORTCbits.RC15 

void __attribute__((interrupt(auto_psv))) _DefaultInterrupt(void){
    LATCbits.LATC15 = 1 ^ PORTCbits.RC15;     //Default: LED D6 blinkt
}

void __attribute__((interrupt(auto_psv))) _T2Interrupt(void) //Interrupt Timer: 100 Hz 
{
_T2IF=0; //reset Interrupt flag 
/*DMACH0bits.CHREQ=1;
while(DMACH0bits.CHREQ);*/

//_IDISSEN=1;
//**********CTMU**********
    /*CTMUCON1bits.IDISSEN = 0;       //Analog Current Source output is not grounded to Charge again
    CTMUCON2=CTMUCON2&~(0b11<<8);   //EDG1STAT bit 7, EDG2STAT bit 8 gleichzeitig löschen*/
    LATCbits.LATC12 = 0;            //LED D5 für Debugging
//........................
}


void __attribute__((interrupt(auto_psv))) _T3Interrupt(void) //Interrupt Timer: alle 2 ms 
{
_T3IF=0; //reset Interrupt flag 
z++;
    LEDD6=1^LEDD6;
    if(z==10)//alle 100ms senden 
    {
    _U1TXIF=1;
    z=0;
    }
}


void __attribute__((interrupt(auto_psv))) _ADC1Interrupt(void){
    //3V = 4096 1V = 1365, 1mV =1.365
    uint32_t x;
    _AD1IF=0;             //Interrupt Flag zurücksetzen
    ADL0CONLbits.SAMP=1;  //Schalter öffnen
    res = ADRES0;         //Tabelle 0 auslesen CTMU
    
    x= res;               
    x=(x*1000)/1365;
    res=x;
    
     
    send[2]=(uint8_t)(res>>8); 
    send[3]=(uint8_t)res;     
    /*send[4]=(uint8_t)(res2>>8);      
    send[5]=(uint8_t)res2;*/   
    ADL0CONLbits.SAMP=0;   //Schalter schließen
    
    
//**********CTMU**********
    CTMUCON1bits.IDISSEN = 1;    //Analog Current Source output is grounded to Discharge
//........................
    LATCbits.LATC12 = 1;    //LED D5 für Debugging
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

        }
        if(Key_K1==0){           ///Taster K1 - Umstellen PGA
            pgaflag=1;
           delaytime4 = timer4ms;
        }
        _CNIF=0;
    }

void __attribute__((interrupt(auto_psv))) _U1RXInterrupt(void){   

    IFS0bits.U1RXIF = 0;    //Reset Interrupt Flag   
//    Display=U1RXREG;
    DataReceive[ByteNumberRX] = U1RXREG;
    ByteNumberRX++;
    
    if(ByteNumberRX == 12)
        ByteNumberRX = 0;

}

void __attribute__((interrupt(auto_psv))) _SPI1Interrupt(void){   

    _SPI1IF=0;
    SPI1STATbits.SPIROV=0;
    Chipselect = 1;
    LATCbits.LATC15 = 1 ^ PORTCbits.RC15;   //LED D6 
}


void __attribute__((interrupt(auto_psv))) _U1TXInterrupt(void){
    
    
//    if(y>3){y=0;_U1TXIF=0;return;}
//
//    U1TXREG=send[y];
//    y++;
//    U1TXREG=send[y];
//    y++;
    
    if(ByteNumberTX < 4096)
    {
    
        while(!U1STAbits.UTXBF && ByteNumberTX < 4096)     //Writing Buffer while Buffer is not full (UT1BF = 1 if full)
        {
            
            if(ByteNumberTX<0)
                U1TXREG = DataReceive[ByteNumberTX+12];
            else
                U1TXREG = DataTXPointer[ByteNumberTX];

            ByteNumberTX++;
        }

//    if(ByteNumberTX == 4096)
//        ByteNumberTX++;
//        
//    if(ByteNumberTX == 4097)
//        ByteNumberTX = -12;
        
    }
//    else
//        ByteNumberTX = 0;
    
    _U1TXIF=0;
} 


   
    
int main(void)
{
	initialize_HW();
    PR1=31250;
    PR2=1250;           //Einstellen Periodendauer 5ms
    PR4=1999;
    PR3=3999;
    send[0]=0xff;
    send[1]=0xff;
    
    DataSend[0] = 0xffff;
    //Print4Digits_LCD(Display);
        
	while(1){
        
        
            
        Print4Digits_LCD(res);
        
        
            if(SendenFlag==1){
                if(((timer4ms-delaytime4)>entprellzeit)&&Key_K3==0)  //nach der entprellzeit wird der Ausgang beschrieben
                   
                {
                   
                    _U1TXIF=1;
                    ByteNumberTX = -12;
                    
                    SendenFlag = 0;                                 //Tasterflag zurücksetzen
                    key_event=0;
                    Print4Digits_LCD(res);                          //Update Display
                }else if(((timer4ms-delaytime4)>entprellzeit)&&Key_K3==1){SendenFlag = 0; key_event=0;}
            }
        
        
        
        
        
            if(pgaflag==1){
                if(((timer4ms-delaytime4)>entprellzeit)&&Key_K1==0)  //nach der entprellzeit wird der Ausgang beschrieben
                   
                {
                    
                    pgaflag = 0;                                 //Tasterflag zurücksetzen
                    key_event=0;
                    //Aktion
                   
                    while(SPI1STATbits.SPITBF);                  //transmit buffer full abfragen
                    Chipselect = 0;
                    SPI1BUF=0b0100000000000001;                  //gain register ansprechen, Gain auf 1
                    
                    
                    
                }else if(((timer4ms-delaytime4)>entprellzeit)&&Key_K1==1){pgaflag = 0; key_event=0;}
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
