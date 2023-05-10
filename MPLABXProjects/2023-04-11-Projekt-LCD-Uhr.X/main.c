// Prof. Dr. Artem Ivanov
// HAW Landshut


#include <xc.h> // include processor description
#include "main.h"



void __attribute__((interrupt(auto_psv))) _T2Interrupt(void) //Interrupt Timer: 2Hz Blinken LED D5
{
_T2IF=0; //reset Interrupt flag
LATCbits.LATC15 = 1 ^ PORTCbits.RC15;           //LED D5 blinken
}

void __attribute__((interrupt(auto_psv))) _DefaultInterrupt(void){

    
    LATCbits.LATC15 = 1 ^ PORTCbits.RC15;     //Default: LED D5 blinkt
}


void __attribute__((interrupt(auto_psv))) _T4Interrupt(void){   
    _T4IF=0;
    timer4ms++;
    

}

void __attribute__((interrupt(auto_psv))) _CNInterrupt(void)
{
    key_event=1;
        if(PORTBbits.RB3==0)
        {           //Taster K3
            LEDD6_FLAG=1;               //Funktion Taster K3: LED D6 toggle
            delaytime4 = timer4ms; 
        }
        if(PORTDbits.RD8==0)            //Taster K2
        {                               
            zahl_LCD=0;                 //0->Dekrementieren
            delaytime4 = timer4ms; 
        }
        if(PORTBbits.RB7==0)            //Taster K1
        {                               
            zahl_LCD=1;                 //1->Inkrementieren
            delaytime4 = timer4ms; 
        }
        _CNIF=0;
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
    
    uint16_t entprellzeit=7;      //Entprellzeit in ms
    uint16_t Zahl=1234;
    uint16_t sekunde = 0;       
    uint16_t minute =0;
    
    PR1=31250;
    PR2=15625;
    PR4=2000;
	// main loop:
    
    Print4Digits_LCD(Zahl);
    //PrintDigit_LCD(4,Zahl);
	while(1){


        /*PrintDigit_LCD(1,1);
        PrintDigit_LCD(2,3);
        PrintDigit_LCD(3,3);*/
        
        
        
        if(_T1IF==1)
        {
            //LATCbits.LATC12 = 1 ^ PORTCbits.RC12;
            LCDDATA1bits.S23C0=1^LCDDATA1bits.S23C0;
            _T1IF=0;
        }
        
        
        if(key_event==1){
            if(zahl_LCD==0){        
                if(((timer4ms-delaytime4)>entprellzeit)&&PORTDbits.RD7==0)
                {
                    if(Zahl>0){
                    Zahl--;}else{Zahl=0;}
                    Print4Digits_LCD(Zahl);
                    zahl_LCD=5;
                    key_event=0;
                }else if(((timer4ms-delaytime4)>entprellzeit)&&PORTDbits.RD7==1){zahl_LCD=5; key_event=0;}
            }


            if(zahl_LCD==1){        
                if(((timer4ms-delaytime4)>entprellzeit)&&PORTBbits.RB7==0)
                {
                    if(Zahl<9999){Zahl++;}else{Zahl=9999;}
                    Print4Digits_LCD(Zahl);
                    zahl_LCD=5;
                    key_event=0;
                }else if(((timer4ms-delaytime4)>entprellzeit)&&PORTBbits.RB7==1){zahl_LCD=5; key_event=0;}
            }

            if(LEDD6_FLAG==1){
                if(((timer4ms-delaytime4)>entprellzeit)&&PORTBbits.RB3==0)  //nach der entprellzeit wird der Ausgang beschrieben
                   
                {
                    LATCbits.LATC12 = 1 ^ PORTCbits.RC12;
                    LEDD6_FLAG = 0;                              //Tasterflag zurücksetzen
                    key_event=0;
                }else if(((timer4ms-delaytime4)>entprellzeit)&&PORTBbits.RB3==1){LEDD6_FLAG = 0; key_event=0;}
            }
            
            if(LEDD5_FLAG==1){
                if((timer4ms-delaytime4)>entprellzeit)
                    {
                    LATCbits.LATC15 = 1 ^ PORTCbits.RC15;
                    LEDD5_FLAG = 0;
                    key_event=0;
                    }
               }
        }
        

            if(time_alt == timer4ms) 
            {
                sekunde++;               
                time_alt = timer4ms +1000;
                if(sekunde==60){
                    minute++;
                    sekunde=0;
                }
                Print4Digits_LCD(sekunde+(minute*100));
            }
        
	}	
}














                    ///////////////////////////////////////
///////////////////////////////Alte Codebausteine////////////////////////////////////////////
                    //////////////////////////////////////


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

        /*if(PORTDbits.RD8==0)
        {
            LEDD5_FLAG=1;
            delaytime4 = timer4ms;
        }*/
                   
        /*if(PORTBbits.RB7==0)                //Ansteuerung LED D5 mit Taster K1
        {
            LEDD6_FLAG=1;                        //Taster gedrückt - Flankenerkennung Flag
            delaytime4 = timer4ms;          //Übergabe der aktuellen Systemzeit
        }*/
        