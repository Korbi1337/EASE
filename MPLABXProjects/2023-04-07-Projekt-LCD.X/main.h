// header file for main.c

void initialize_HW(void);	// initialisation procedure

void __attribute__((interrupt(auto_psv))) _DefaultInterrupt(void);
void __attribute__((interrupt(auto_psv))) _T2Interrupt(void);
void __attribute__((interrupt(auto_psv))) _CNInterrupt(void);
void __attribute__((interrupt(auto_psv))) _T4Interrupt(void);



void PrintDigit_LCD(uint16_t,uint16_t);
void Print4Digits_LCD(uint16_t);