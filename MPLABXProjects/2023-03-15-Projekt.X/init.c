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
#pragma config OSCIOFCN = OFF           // OSCO Pin Configuration (OSCO/CLKO/RC15 functions as CLKO (FOSC/2))
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
	ANSBbits.ANSB2 = 0;		// RB2 = signal "ON" - digital
	
// 2. Digital Input / Output:
	TRISBbits.TRISB2 = 0;	// "ON" = output
    TRISCbits.TRISC12 = 0;
// 3. Output level on digital pins:
	LATBbits.LATB2 = 0;
    LATCbits.LATC12 =1;
// 4. Open drain settings:
	ODCBbits.ODB2 = 1;					// open drain on "ON"
	
//5. Osc Settings finetune
    OSCTUNbits.TUN=100000;
}	