/*
Denna fil innehåller main funktionen av programmet
*/
#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

uint8_t screen[128*4];

int main(void) {
	configbtn();
	configscreen();
	display_init();
	display_image(0, screen);
	flappy_game();
}
