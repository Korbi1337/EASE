// header file for main.c

void initialize_HW(void);	// initialisation procedure
 void Print4Digits_LCD(uint16_t);


void __attribute__((interrupt(auto_psv))) _DefaultInterrupt(void);
void __attribute__((interrupt(auto_psv))) _T2Interrupt(void);
void __attribute__((interrupt(auto_psv))) _CNInterrupt(void);
void __attribute__((interrupt(auto_psv))) _T4Interrupt(void);
void __attribute__((interrupt(auto_psv))) _U1RXInterrupt(void);
void __attribute__((interrupt(auto_psv))) _ADC1Interrupt(void);


volatile uint16_t timer4ms = 0;       //Globale Zählervariable Systemzeit
volatile uint16_t delaytime4 = 0;     //Vergleichswert für Entprellzeit
volatile uint16_t key_event=0;
volatile uint16_t SendenFlag=0;
volatile uint8_t receive_num[4];
volatile uint16_t Display = 123; //Angezeiter Wert
volatile uint8_t pgaflag=0;
volatile uint8_t z =0;
volatile uint16_t res=0;            //Result table 1 ADC
volatile uint8_t send[6];
volatile uint16_t y =0;
volatile uint16_t N; 
volatile uint8_t DataReceive[12]={0xff,0xff,'V',0x01,'H',0x4F,0x00,'T',0x00,0x08,'A','p'};
volatile uint8_t startmessungflag=1;
volatile uint8_t convertflag=1;
/*
 * 0-1: ff
 * 2:   'V' "Vertical"
 * 3:   1   PGA gain: -1
 *      2   PGA gain: -3
 *      3   PGA gain: -9
 *      4   PGA gain: -31
 * 4:   'H' "Vertical"
 * 5:   Low Byte N
 * 6:   High Byte N 
 * 7:   'T' "Trigger"
 * 8:   Low Byte Trigger
 * 9:   High Byte Trigger
 * 10:  'A' or 'N' or 'S'
 * 11:  'p' or 'n'
 */
volatile uint16_t DataSend[2048];
volatile uint8_t *DataTXPointer = &DataSend;
volatile uint8_t ByteNumberRX = 0;
volatile int16_t ByteNumberTX = -12;
volatile uint16_t i;

uint16_t entprellzeit=4;

uint16_t Array[256]={1};
uint16_t Array2[256]={0};