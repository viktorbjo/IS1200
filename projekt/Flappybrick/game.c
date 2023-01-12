/* 
* Denna fil innehåller logiken för spelet. 
* Skriven av Viktor B & Adam L. 
*/

#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

//storlek på skärmen 
#define screen_height 32
#define screen_width 128

//storlek på fågel
#define bird_height 2
#define bird_width 5

// bredden på rören 
#define block_width 7

//varibler för random funktioner
int random_Value;
int final_Value = 0;
int block_Value;

//kordinater för fågeln (globla varibler)
double position_X = 10; 
double position_Y = 8;
// Position för första blocket. första blocket kommer efter 300 enheter,
// Y-led slumpas varje gång som användaren trycker på hoppa knappen. 
double block_position_X = 300;
double block_position_Y = 50; //sätter värdet till 50 för att motverka att röret ska gå hela vägen upp.

// display (kolla uint8_t)
uint8_t screen[512] = {0}; 

//Global variabel för poängen. 
int score = 0;

//konvertera x och y kordinater så det blir enklare att rita på skärmen 
void fill (int x, int y, uint8_t *array){

    // detta gör så det inte läggs pixlar utanför skärmen
    if(x <= 0 || x >= screen_width || y <= 0 || y >= screen_height){
	    return;
    }

    	//definerar i vilken "page"/sida/bild pixlarna ska hamna 0 < y < 32 (pga skärmens storlek)
	int page = y / 8; 

	// page * 128 ger oss bilden/sidan. Plus x ger oss indexet innuti den bilden/sidan
	// y position i bilden. 
	array[page * 128 + x] |= (1 << (y - page * 8));		
	} 

	//rita fågelns position
	void bird_Print() {
	int i;
	int j;
		for(i = 0; i < bird_height; i++){
			for(j = 0; j < bird_width; j++){
			    fill((int) position_X + j, (int) position_Y + i, screen);
			}
		}	
	}

	// kollar vilka knapp 
	volatile int getbtn(int btn){
		int value = 0;
		switch (btn){
			case 1:
				value = (PORTF)&2;
				break;
			case 2:
				value = ((PORTD>>5)&7) & 1;
				break;
			case 3:
				value = ((PORTD>>5)&7) & 2;
				break;
			case 4:
				value = ((PORTD>>5)&7) & 4;
			break;
		default:
			value = 0;
	}
	return value;
}

//kopierar värdet från TMR4 när knapp 3 är nedtryckt
int num_generator() {
	if(getbtn(3)){
        int temp = TMR4; // när knapp 3 blir nedtryckt slumpar den ett tal mellan 0-9
        random_Value = temp;
	}
	return random_Value;
}

// fågel flyger uppåt. 
void bird_fly_up() {
	if(getbtn(3)){
		if(position_Y >= 0){
		position_Y -= 0.25;
		}
	}
}

//denna kod innehåller kod från annan källa, se bild "Binary to decimal generator".
// den gör om kod från binärt från num_generator till decimal som lagras i final_Value
//vi hittade en funktion som konverterar från binärt till decimal.
// Ger ett värde till nästa blocks y-posetion  
void block_generator () {
    int temp_decimal = 0;
    int temp_counter = 1;
    int adder;
    int temp_number = num_generator() * 2; 
        while (temp_number > 0){
            adder = temp_number % 10;
            temp_decimal = temp_decimal + adder * temp_counter;
            temp_number = temp_number / 10 ;
            temp_counter = temp_counter * 2;
        }
    final_Value = (temp_decimal % 10); //värde mellan 0 och 9 
}

//Byter nästa blocks y position  
int get_block_pos() {
    if (block_position_X == 128) {
        block_Value = final_Value;
    }
    return block_Value;
}
// ritar nästa block. 
void draw_block() {
   	int localtemp = 0; 
	int i;
	int j;
	// Flyttar block från vänster till höger. 
    if (block_position_X == 0) {
        block_position_X = 128;
		score++; //Varje gång ett hinder försvinner får du en poäng.
    }
	//hämtar värdet i y-led 
    block_generator ();
    localtemp = get_block_pos();

    if (localtemp != 0) {
        block_position_Y = ((2 * localtemp) + 8); //Höjden som blocket ska ha
    }
    for (i=0; i < (32-block_position_Y); i++) { // 32 för att starta den från golvet. 
        for (j = 0; j < block_width; j++) {
            fill((int) block_position_X + j,(int) block_position_Y + i, screen);
        }
    }
}

// sätter varje byte till 0 för att rensa skärmen
void clear() {
	int i; 
    for(i = 0; i < sizeof(screen); i++){
		screen[i] = 0;
	}
} 

//kollar vilken switch som är aktiverad
volatile int getsw(int sw){
	int value = 0;
	switch (sw) {
		case 1:
			value = ((PORTD>>8)&15) & 1;
			break;
	
		case 2:
			value = ((PORTD>>8)&15) & 2;
			break;
		
		case 3:
			value = ((PORTD>>8)&15) & 4;
			break;

		case 4:
			value = ((PORTD>>8)&15) & 8;
			break;
		default:
			value = 0;
	}
	return value;
}

//kollar om fåglen krockat med antingen ett rör eller skärmens kanter 
int check_death(){
	int i;

	//skärmens kanter 
	int max_screen = 0;
	int min_screen = screen_height;

	//fågelns kanter 
	int bird_max = position_Y;
	int bird_min = position_Y + bird_height;	
	// så fåglens storlek är i åtanke när den slår i
	int bird_left = position_X;
	int bird_right = position_X + bird_width;

	//Pipes kanter
	int block_max = block_position_Y;
	int block_left = block_position_X;
   	int block_right = block_position_X + block_width;


	//kollision med skärmens kanter 
	if(bird_max == max_screen || bird_min == min_screen ){
	    return 1;
	}
	//Kollision med rören. 
	if ( ((bird_min == block_max) && ((bird_right >= block_left) && (bird_left <= block_right )) ) ||
	( (bird_right == block_left) && (bird_min >= block_max) ) ) { 
        return 1;
    }
    else
        return 0;
}

//KOD FRÅN: mipslabfun.c (labb 3). "Itoa" 
//konverterar binärt till decimal. 
//returnerar pekare till en statisk char array.
#define ITOA_BUFSIZ ( 24 )
char * itoaconv( int num )
{
  register int i, sign;
  static char itoa_buffer[ ITOA_BUFSIZ ];
  static const char maxneg[] = "-2147483648";

  itoa_buffer[ ITOA_BUFSIZ - 1 ] = 0;   /* Insert the end-of-string marker. */
  sign = num;                           /* Save sign. */
  if( num < 0 && num - 1 > 0 )          /* Check for most negative integer */
  {
    for( i = 0; i < sizeof( maxneg ); i += 1 )
    itoa_buffer[ i + 1 ] = maxneg[ i ];
    i = 0;
  }
  else
  {
    if( num < 0 ) num = -num;           /* Make number positive. */
    i = ITOA_BUFSIZ - 2;                /* Location for first ASCII digit. */
    do {
      itoa_buffer[ i ] = num % 10 + '0';/* Insert next digit. */
      num = num / 10;                   /* Remove digit from number. */
      i -= 1;                           /* Move index to next empty position. */
    } while( num > 0 );
    if( sign < 0 )
    {
      itoa_buffer[ i ] = '-';
      i -= 1;
    }
  }
  /* Since the loop always sets the index i to the next empty position,
   * we must add 1 in order to return a pointer to the first occupied position. */
  return( &itoa_buffer[ i + 1 ] );
}



void run_game(){
	score = 0; //återställer score

    int game_active = 1; //boolean för att veta när du spelar eller inte. 
	while(game_active){
    // Får fågeln att röra sig, reset är nödvändig för att det ska fungera felfritt 
	bird_fly_up();
	clear();	

	// "Se bild IFS0 bits" fär värden på IFS0 BITS. 

		// Gravitation i y-led. (fågel) 
	if(IFS(0) & 0x1000){
			if(position_Y >= 0){
				position_Y += 0.25;
			}
				IFSCLR(0) = 0x1000; //RESET
	}

		// Flyttar hindret från höger till vänster. (x-led)
        if (IFS(0) & 0x10000) {
            if(block_position_X > 0) {
                block_position_X -= 0.25;
            }
		IFSCLR(0) = 0x10000; //reset
	}
	draw_block();
	bird_Print();
	display_image(0, screen);

	game_active = !check_death(); //slutar spela om vi får tillbaka en 1:a från funktionen check_death
	}
}

//game over skärmenen 
void game_over(){
    //Återställer värdena till orginal 
	position_X = 10;
	position_Y = 8;
	block_position_X = 300;
	block_position_Y = 50;	//sätter så att rören inte går hela vägen upp.

    int game_over = 1; //booelean som är 1 om det är game over.
	display_string(0, "DU DOD");
	display_string(1, "POANG:");
	display_string(2, itoaconv(score));
	display_string(3, "BTN2 meny");
	display_update();

	while(game_over){
		if(getbtn(2)) {
			game_over = 0;
		}
	}
}

//välj svårighetsgrad
void choose_difficulty() {
    clear_text();
    display_update();

    display_string(0,"SVARIGHET");
    display_string(1,"SW3: ENEKEL");
    display_string(2,"SW2: Normal");
    display_string(3,"SW1: SVAR");
    display_update();

    while(1) {
        if(getsw(3)) {
            difficulty = 100;
            break;
        }
        if(getsw(2)) {
            difficulty = 250;
            break;
        }
        if(getsw(1)) {
             difficulty = 500;
             break;
        }
    }
}

void menu(){
	int main_menu = 1;

	display_string(0, "Flappy bird-spel");
	display_string(1, "Skapare: ");
	display_string(2, "Viktor & Adam");
	display_string(3, "BTN1 Spela");
	display_update();

	while(main_menu){
		if(getbtn(1)){
			main_menu = 0;
		}	
	}
}
// Oändlig loop som kör igenom alla olika steg i spelet
// Meny, svårighet, spela och avslutskärmen.
void flappy_game(){
	while (1){
		menu();
		choose_difficulty();
		setGravity();
		setBlockSpeed();
		run_game();
		game_over();
	}
}


