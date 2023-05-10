// header file for main.c

void initialize_HW(void);	// initialisation procedure

void __attribute__((interrupt(auto_psv))) _DefaultInterrupt(void);
void __attribute__((interrupt(auto_psv))) _T2Interrupt(void);
void __attribute__((interrupt(auto_psv))) _CNInterrupt(void);
void __attribute__((interrupt(auto_psv))) _T4Interrupt(void);



void PrintDigit_LCD(uint16_t,uint16_t);
void Print4Digits_LCD(uint16_t);


volatile uint16_t timer4ms = 0;       //Globale Zählervariable Systemzeit
volatile uint16_t LEDD6_FLAG = 0;     //Globales Flag LED D6 togglen
volatile uint16_t delaytime4 = 0;     //Vergleichswert für Entprellzeit
volatile uint16_t LEDD5_FLAG = 0;     //globales Flag für LED D5
volatile uint16_t zahl_LCD = 10;      //globales Flag für veränderung der Zahl auf dem LCD-Display
volatile uint16_t key_event=0;        //Taster gedrückt
volatile uint16_t time_alt = 0;