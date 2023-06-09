// header file for main.c

void initialize_HW(void);	// initialisation procedure
 void Print4Digits_LCD(uint16_t);


void __attribute__((interrupt(auto_psv))) _DefaultInterrupt(void);
void __attribute__((interrupt(auto_psv))) _T2Interrupt(void);
void __attribute__((interrupt(auto_psv))) _CNInterrupt(void);
void __attribute__((interrupt(auto_psv))) _T4Interrupt(void);
void __attribute__((interrupt(auto_psv))) _U1RXInterrupt(void);
void __attribute__((interrupt(auto_psv))) _ADC1Interrupt(void);


volatile uint16_t timer4ms = 0;       //Globale Z�hlervariable Systemzeit
volatile uint16_t delaytime4 = 0;     //Vergleichswert f�r Entprellzeit
volatile uint16_t key_event=0;
volatile uint16_t SendenFlag=0;
volatile uint8_t receive_num[4];
volatile uint16_t Display = 123; //Angezeiter Wert
volatile uint8_t pgaflag=0;
volatile uint8_t z =0;
volatile uint16_t res=0;            //Result table 1 ADC
volatile uint16_t res2=0;           //Result table 2 ADC
volatile uint8_t send[6];
volatile uint16_t y =0;
volatile uint8_t DataReceive[12];
volatile uint16_t DateSend[2048];
volatile uint8_t ByteNumber = 0;


uint16_t entprellzeit=4;

uint16_t Array[256]={1};
uint16_t Array2[256]={0};