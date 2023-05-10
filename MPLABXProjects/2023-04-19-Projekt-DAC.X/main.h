// header file for main.c

void initialize_HW(void);	// initialisation procedure



void __attribute__((interrupt(auto_psv))) _DefaultInterrupt(void);
void __attribute__((interrupt(auto_psv))) _T2Interrupt(void);
void __attribute__((interrupt(auto_psv))) _CNInterrupt(void);
void __attribute__((interrupt(auto_psv))) _T4Interrupt(void);



volatile uint16_t timer4ms = 0;       //Globale Zählervariable Systemzeit
volatile uint16_t delaytime4 = 0;     //Vergleichswert für Entprellzeit
volatile uint16_t hilf=0;

uint16_t Array[256]={1};
uint16_t Array2[256]={0};