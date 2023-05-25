
#include <p24FJ128GC006.h>

// Initialization of the hardware

#include <xc.h> // include processor description


// Set cofiguration registers:-------------------------------------------------------------
// CONFIG4
#pragma config DSWDTPS = DSWDTPS1F      // Deep Sleep Watchdog Timer Postscale Select bits (1:68719476736 (25.7 Days))
#pragma config DSWDTOSC = LPRC          // DSWDT Reference Clock Select (DSWDT uses LPRC as reference clock)
#pragma config DSBOREN = OFF            // Deep Sleep BOR Enable bit (DSBOR Disabled)
#pragma config DSWDTEN = OFF            // Deep Sleep Watchdog Timer Enable (DSWDT Disabled)
#pragma config DSSWEN = OFF             // DSEN Bit Enable (Deep Sleep operation is always disabled)
#pragma config RTCBAT = ON              // RTC Battery Operation Enable (RTC operation is continued through VBAT)
#pragma config PLLDIV = NODIV           // PLL Input Prescaler Select bits (Oscillator used directly (4 MHz input))
#pragma config I2C2SEL = SEC            // Alternate I2C2 Location Select bit (I2C2 is multiplexed to SDA2/RF4 and SCL2/RF5)
#pragma config IOL1WAY = OFF            // PPS IOLOCK Set Only Once Enable bit (The IOLOCK bit can be set and cleared using the unlock sequence)

// CONFIG3
#pragma config WPFP = WPFP0             // Write Protection Flash Page Segment Boundary (Page 0 (0x00))
#pragma config SOSCSEL = ON             // SOSC Selection bits (SOSC circuit selected)
#pragma config WDTWIN = PS25_0          // Window Mode Watchdog Timer Window Width Select (Watch Dog Timer Window Width is 25 percent)
#pragma config BOREN = ON               // Brown-out Reset Enable (Brown-out Reset Enable)
#pragma config WPDIS = WPDIS            // Segment Write Protection Disable (Disabled)
#pragma config WPCFG = WPCFGDIS         // Write Protect Configuration Page Select (Disabled)
#pragma config WPEND = WPSTARTMEM       // Segment Write Protection End Page Select (Write Protect from page 0 to WPFP)

// CONFIG2
#pragma config POSCMD = NONE            // Primary Oscillator Select (Primary Oscillator Disabled)
#pragma config WDTCLK = LPRC            // WDT Clock Source Select bits (WDT uses LPRC)
#pragma config OSCIOFCN = ON           // OSCO Pin Configuration (OSCO/CLKO/RC15 functions as CLKO (FOSC/2))
#pragma config FCKSM = CSDCMD           // Clock Switching and Fail-Safe Clock Monitor Configuration bits (Clock switching and Fail-Safe Clock Monitor are disabled)
#pragma config FNOSC = FRCPLL           // Initial Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))
#pragma config ALTADREF = AVREF_RB      // External 12-Bit A/D Reference Location Select bit (AVREF+/AVREF- are mapped to RB0/RB1)
#pragma config ALTCVREF = CVREF_RB      // External Comparator Reference Location Select bit (CVREF+/CVREF- are mapped to RB0/RB1)
#pragma config WDTCMX = LPRC            // WDT Clock Source Select bits (WDT always uses LPRC as its clock source)
#pragma config IESO = OFF               // Internal External Switchover (Disabled)

// CONFIG1
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler Select (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler Ratio Select (1:128)
#pragma config WINDIS = OFF             // Windowed WDT Disable (Standard Watchdog Timer)
#pragma config FWDTEN = WDT_SW          // Watchdog Timer Enable (WDT controlled with the SWDTEN bit)
#pragma config ICS = PGx3               // Emulator Pin Placement Select bits (Emulator functions are shared with PGEC3/PGED3)
#pragma config LPCFG = ON               // Low power regulator control (Low voltage regulator controlled in sw by RETEN bit)
#pragma config GWRP = OFF               // General Segment Write Protect (Disabled)
#pragma config GCP = OFF                // General Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF             // JTAG Port Enable (Disabled)

//==========================================================================================
void initialize_HW(void){
	
// Oscillator Configuration----------------------------------------------
// setting F_cy = Fosc/2 = 16MHz:
	CLKDIVbits.RCDIV = 1;			// divide by 2 (actually default)
	CLKDIVbits.CPDIV = 0;			// no division Clock=32MHz (default) 
	
// Pin functions --------------------------------------------------------
// 1. Analog / digital:
	ANSBbits.ANSB2 = 0;                    // RB2 = signal "ON" - digital
	ANSBbits.ANSB7 = 0;	
    ANSDbits.ANSD8 =0;
    ANSBbits.ANSB3 = 0;
    ANSBbits.ANSB12 = 0;                    //Audioausgang
    ANSFbits.ANSF5 = 0;                     //Bluetooth Pin 
    ANSBbits.ANSB1= 1;                      //ADC Eingang Analog :Vbat/2
    ANSBbits.ANSB6=1;                       //ADC Eingang Analog: IN1

    
// 2. Digital Input / Output:
	TRISBbits.TRISB2 = 0;                  // "ON" = output
    TRISCbits.TRISC12 = 0;                  //output LED D5 
    TRISBbits.TRISB7 = 1;                  //Input K1
    TRISCbits.TRISC15 = 0;                  //output LED D6
    TRISDbits.TRISD8 =1;                   //Input K2
    TRISBbits.TRISB3 =1;                   //Input K3
    TRISBbits.TRISB12 = 0;                  //Audioausgang output
    TRISBbits.TRISB1 =1;                    //Input Vbat/2
    TRISBbits.TRISB6=1;                     //Input IN1
    
    
// 3. Output level on digital pins:
	LATBbits.LATB2 = 0;                    //Aus
    LATCbits.LATC12 = 0;        
    LATCbits.LATC15 = 0;
    LATBbits.LATB12 =0;
    
// 4. Open drain settings:
	ODCBbits.ODB2 = 1;                     // open drain on "ON"
	
//5. Osc Settings finetune
    //OSCTUNbits.TUN = 0b011111;
    OSCTUNbits.TUN = 0b0;                   //finetuning auf 16.016 MHz
    //OSCTUNbits.TUN4 = 1;
	
//6. Input change notification
    
    _CNIF=0;                                 //Interrupt flag normalerweise 0
    _CNIE=1;                                 //Interrupt enable
    CNEN2bits.CN25IE = 1;                    //Interrupt Taster K1
    CNEN4bits.CN53IE = 1;                    //Interrupt Taster K2
    CNEN1bits.CN5IE = 1;                     //Interrupt Taster K3

    //Pullup/Pulldown
    CNPU1bits.CN5PUE = 1;      // Pull up für Taster K3
    
 //7. Timers
    //Timer1
    T1CONbits.TON = 1;          //Timer an
    T1CONbits.TCKPS = 0b11;     //Prescaler clock 0b11 = 1:256
    T1CONbits.TCS = 0;          //Clock Source Select Bit: 0 = internal
    T1CONbits.TSYNC = 0;        //Synchronizing on external clock off
    T1CONbits.TGATE=0;          //TGATE: gated Time accumulation
    //Timer2
    T2CONbits.TON = 1;          //Timer an
    T2CONbits.TCKPS = 0b10;     //Prescaler clock 1:64
    T2CONbits.TCS = 0;          //Clock Source Select Bit: 0= internal
    //Timer4
    T4CONbits.TON = 1;          //Timer an
    T4CONbits.TCKPS = 0b01;     //Prescaler clock 1:8 ->2000000
    T4CONbits.TCS = 0;          //Clock Source Select Bit: 0= internal
    
    
    //Timer Interrupt Enable
    IEC0bits.T2IE = 1;
    IEC1bits.T4IE = 1;
    
    //LCD Panel
    LCDCONbits.LMUX=0b011;      //1/4 MUX
    LCDCONbits.LCDEN=1;         //LCD Driver Enable bit
    LCDCONbits.CS=0b00;         //Clock source select: 00-frc
    LCDCONbits.LCDSIDL=1;       //Stop in CPU idle mode 
    
    LCDPSbits.LCDA=1;           //LCD driver module is active
    LCDPSbits.WFT=0;            //Type A Waveform
    LCDPSbits.WA=1;             //LCD write allow status bit
    
    
    LCDREFbits.LRLBP=0b11;      //B Timer power Control bits
    LCDREFbits.LCDIRE=1;        //LCD internal Reference enable
    LCDREFbits.LCDCST=0b000;    //resistor ladder maximum contrast
    LCDREFbits.LRLAT=0b000;     //immer in B-Power mode
       
    
    //Segmente Aktivieren       //Pinnr. am LCD
    LCDSE0bits.SE14=1;          //18 
    LCDSE0bits.SE15=1;          //17
    LCDSE1bits.SE16=1;          //16
    LCDSE1bits.SE17=1;          //15
    LCDSE1bits.SE20=1;          //14
    LCDSE1bits.SE21=1;          //13
    LCDSE1bits.SE22=1;          //12
    LCDSE1bits.SE23=1;          //11
    LCDSE1bits.SE24=1;          //10
    LCDSE1bits.SE25=1;          //9
    LCDSE1bits.SE26=1;          //8
    LCDSE1bits.SE27=1;          //7
    LCDSE2bits.SE47=1;          //6
    LCDSE3bits.SE62=1;          //5
    
    
    
    ///DAC 
    DAC1CONbits.DACEN=1;            //DAC Enabled
    DAC1CONbits.DACSIDL=1;          //DAC Stop in Idle mode
    DAC1CONbits.DACSLP=0;           //DAC disable during sleep mode 
    DAC1CONbits.DACFM=0;            //DAC Data Format select bit justification
    DAC1CONbits.DACTRIG=0;          //Trigger Input Enable bit
    DAC1CONbits.DACREF=0b10;        //DAC reference AVDD

    //Audioausgang
    _RB12=1;
    
    //DMA
    DMACONbits.DMAEN =0b1;          //DMA Enable
    DMACONbits.PRSSEL=0b0;          //fixed priority scheme selection
    DMACH0bits.CHEN=0b0;            //Channel 0 deaktiviert
    DMACH0bits.NULLW =0b0;          //kein Dummywert /nullwrite
    DMACH0bits.RELOAD = 0b1;        //DMASRCn, ST und CNT reloaden
    DMACH0bits.SAMODE=0b01;         //DMASRC is inkremented based on SIZE after transfer completion
    DMACH0bits.SIZE =0b0;           //Datengröße: word/16-bit
    DMACH0bits.TRMODE= 0b01;        // repeated oneshot mode
            
    //UART
    __builtin_write_OSCCONL(OSCCON & 0xbf);
    
    RPINR18bits.U1RXR=17;           //RP17 als Rx Uart1 
    RPOR7bits.RP14R=3;              //RP14 als U1TX UART1 Transmit

    __builtin_write_OSCCONL(OSCCON | 0x40);

    
    U1BRG=32;
    U1MODEbits.BRGH =1;             //standard Speed mode
    U1MODEbits.STSEL =0b0;          //1 Stopbit
    U1MODEbits.PDSEL =0b00;         //8 bit, no parity
    U1MODEbits.UARTEN = 0b1;        //UART Modul enable 
    U1STAbits.URXISEL = 0b10;       //Interrupt, wenn Empfangspuffer 4 Zeichen enthaelt
    U1STAbits.UTXISEL0=0;
    U1STAbits.UTXISEL1=1;
    U1STAbits.UTXEN =1;             //Transmit enabled
    
    IEC0bits.U1RXIE = 1;            //UART1 Reciever Interrupt enable
    
    
    
    
    /////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////ADC///////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    
   
    //ANS Pins Konfigurieren Fehlt
    ADCON1bits.PWRLVL=1;            //Full-Power Mode, um 8 MHZ zu ermöglichen
    
    ADCON2bits.BUFORG =1;           //indexed buffer: ADTBLn conversion result is stored in ADRESn
    ADCON2bits.PVCFG= 0;            //AVDD als Reference
    ADCON2bits.NVCFG= 0;            //AVSS als adref-
    
    ADCON3bits.ADRC=0;              //Conversion Clock derived from system Clock
    ADCON3bits.ADCS=0b0000001;      //AD Conversion prescaler :8MHz
    ADCON3bits.SLEN0=1;             //A/D Sample List 0 Enable 
    ADCON1bits.ADON =1;             //Enable ADC
  
    while(ADSTATHbits.ADREADY==0);
////5. Sample List settings
    //List0
    ADL0CONHbits.SAMC=0b00000;      //0.5 TAD Sample/Hold Charge Time
    ADL0CONHbits.ASEN=0;            //autosample disabled
    ADL0CONHbits.SLINT=0b01;        //Interrupt nach jedem sample
    ADL0CONLbits.SLSIZE = 00001;    //Sample List Size Select :2 Tables
    ADL0CONLbits.SLTSRC=0b00101;    //trigger timer2 trigger event
    ADL0CONLbits.SAMP=1;            //Prepares to generate a trigger event
    ADL0CONLbits.SLENCLR=0;         //SLEN is cleared by software
    
    //Table 0: Vbat/2
    ADTBL0bits.DIFF=0;              //Single-ended messung
    ADTBL0bits.UCTMU = 0b1;         //Charge time measurement unit
    ADTBL0bits.ADCH=0b0000001;      //Ch1: VBAT/2
    //Table: IN1
    ADTBL1bits.DIFF=0;              //Single-ended messung
    ADTBL1bits.UCTMU = 0b1;         //Charge time measurement unit
    ADTBL1bits.ADCH=0b0000110;      //table 2: IN

    _SL0IF=0;
    _AD1IE=1;                       //ADC Interrupt enable
    _AD1IF=0;
    
    ADL0CONLbits.SLEN = 1;          //trigger causes sampling
    ADCON1bits.ADCAL =1;            //Initiates Internal Analog calibration - Evtl in die Main! oder nicht
    
    while(ADSTATHbits.ADREADY==0);
    ADL0CONLbits.SAMP=0;            //close sample switch
    

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////USB///////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*U1CONbits.PPBRST=0;             //pingpong buffer clear
    U1IE=0;
    U1EIE=0;                        //interrupts disabled
    U1IR=0xFF;
    U1EIR=0xFF;                     //interrupt flags clearen
    //verify Vbus is present
    U1CONbits.USBEN =1;             //USB enable
    U1CONbits.USBRST=0;             //USB reset. minimum 50ms.

    
    U1CONbits.USBEN =0;    
    U1OTGCONbits.OTGEN=1;           //otg enable
    U1EP0bits.EPRXEN=1;             //enable endpoint 0 buffer
    U1EP0bits.EPHSHK =1;            //enable endpoint 0 buffer
    U1PWRCbits.USBPWR=1;            //USB module Powerup
    U1OTGCONbits.DPPULUP =1;        //signal an attach
    U1CONbits.USBEN =1;

        
    U1ADDRbits.DEVADDR = 0b0000011;  //Adresse: 3 (?)
    U1CNFG1bits.PPB=0b01;               //ping pong enabled for endpoint 0*/
    
    
    
    
    }