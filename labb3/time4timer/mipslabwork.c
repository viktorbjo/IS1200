/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x0001;

char textstring[] = "text, more text, and even more text!";

volatile int *tris_E;		// deklarerar våra pekare som volotära
volatile int *port_E;

int timeoutcount = 0;		// deklarerar timeoutcount

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
tris_E = (volatile int*) 0xbf886100;	// adrees för trise E register
port_E = (volatile int*) 0xbf886110;	// adress för port E register

	*tris_E = *tris_E & 0xffffff00;	// maskar de 8 LSB

	*port_E = 0x00000000;		// set port E till 0 vilket gör det enklare att se tickandet

	
	TRISD = TRISD | 0x0fe0; 	// "OR" för att spara värderna på platserna bitsen 11-5

// startar Timer 2 
T2CON = 0x0; 		// sätter ON-bit (15) till 0 för att stoppa klockan

T2CONSET = 0X70;	// anävnder se register för t2con för att sätta prescalling till 1:256 
			// (70 = 0111 0000)

TMR2 = 0X0;		// restar timer registret

PR2 = ((80000000/256)/10); // period register där vi sätter clockfeq/ prescalling
			   // vi delar sedan med 10 för att få 100ms delay
			   // timern går upp till vårt värde sedan sätter avbrotts flaga i IFS0 till 1
T2CONSET = 0x8000; 		//sätter ON-bit (15) till 1 för att starta klockan

  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{

int brytare = getsw();
int knappar = getbtns();

	if(knappar & 1){				// knapp 2 (001)
		mytime = mytime & 0xff0f;		// maskar de bits som visar 10de sekund

		mytime = (brytare << 4) | mytime;	// flyttar värdet från brytarna till rätt
	}						// position, sen "OR" de till mytime 

	if(knappar & 2){				// knapp 2 (001)
		mytime = mytime & 0xf0ff;		// maskar de bits som visar 10de sekund

		mytime = (brytare << 8) | mytime;	// flyttar värdet från brytarna till rätt
	}						// position, sen "OR" de till mytime 
	if(knappar & 4){				// knapp 2 (001)
		mytime = mytime & 0x0fff;		// maskar de bits som visar 10de sekund

		mytime = (brytare << 12) | mytime;	// flyttar värdet från brytarna till rätt
	}						// position, sen "OR" de till mytime 

if(IFS(0) & 0x100){
	timeoutcount++;

	IFSCLR(0) = 0x100;
}



  if(timeoutcount == 10){ 		// if sats som körs varje 10de avbrott

  // delay( 1000 );
  time2string( textstring, mytime );
  display_string( 3, textstring );
  display_update();
  tick( &mytime );
  display_image(96, icon);

  *port_E = *port_E + 0x00000001;	// ökar värdet per tick
	}
  }


