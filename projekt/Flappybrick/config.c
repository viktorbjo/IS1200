/*
 All code in configscreen function was
 taken from mipslabmain.c by Axel Isaksson and F. Lundevall
 The rest was written by Viktor B och Adam L
*/
#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

// Sätter knapparnar och switcharna
void configbtn() {

	TRISFSET = 0x2; //knapp 1
    TRISDSET = 0xFE0; //switchar 1-4 och knapp 2-4

}
// tagen från mipslabmain.c se högst upp. 
void configscreen() {
	/*
	  This will set the peripheral bus clock to the same frequency
	  as the sysclock. That means 80 MHz, when the microcontroller
	  is running at 80 MHz. Changed 2017, as recommended by Axel.
	*/
	SYSKEY = 0xAA996655;  /* Unlock OSCCON, step 1 */
	SYSKEY = 0x556699AA;  /* Unlock OSCCON, step 2 */
	while(OSCCON & (1 << 21)); /* Wait until PBDIV ready */
	OSCCONCLR = 0x180000; /* clear PBDIV bit <0,1> */
	while(OSCCON & (1 << 21));  /* Wait until PBDIV ready */
	SYSKEY = 0x0;  /* Lock OSCCON */

	//output pins for display signal
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;

	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;
	/* SPI2STAT bit SPIROV = 0; */
	SPI2STATCLR = 0x40;
	/* SPI2CON bit CKP = 1; */
  	SPI2CONSET = 0x40;
	/* SPI2CON bit MSTEN = 1; */
	SPI2CONSET = 0x20;
	/* SPI2CON bit ON = 1; */
	SPI2CONSET = 0x8000;

}

//timer för fågelns gravidation 
void setGravity() {
	TMR3 = 0;
	T3CON = 0x70; // 111 i hex (1:256 pre-scaling) största skalan för att undvika stora nummer att få plats me i registret
	T3CONSET = 0x8000; // Startar timern genom att sätta bit 15 till 1
	PR3 = ((80000000/256) / 100); //sätter perioden

}

//timer för block
void setBlockSpeed() {
	TMR4 = 0;
	T4CON = 0x70; // 111 i hex (1:256 pre-scaling) största skalan för att undvika stora nummer att få plats me i registret
	T4CONSET = 0x8000; // Startar timern genom att sätta bit 15 till 1
	PR4 = ((80000000/256) / difficulty); //Sätter perioden. Delar med svårighetsgraden vald. 

}
void user_isr() {
	return;
}
