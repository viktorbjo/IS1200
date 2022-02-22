#include <stdint.h> 
#include <pic32mx.h>
#include "mipslab.h"

// returnerar data från SWx
int getsw(void){ 			// shiftar bitsen 8 steg eftersom brytarna är bits 11-8 
	return ((PORTD>>8) & 0x000f);	// för att returnera värden på de 4 LSB.
}

// returnerar data från BTNx
int getbtns(void){			// shiftar 5 steg eftersom knapparna är bits 7-5
	return((PORTD>>5) & 0x0007);	// för att returnera värden på de 3 LSB.
}
