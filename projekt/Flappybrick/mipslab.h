/*
Programs's header file
Written by Viktor B and Adam L
*/

//All konfiguration som behövs
void configbtn(void);
void configscreen(void);
volatile int difficulty;
void setGravity(void);
void setPipeSpeed(void);
void user_isr(void);

//all display-relaterade funktioner 
uint8_t spi_send_recv(uint8_t data);
void display_init(void);
void display_update(void);
void display_string(int line, char *s);


extern const uint8_t const font[128*8];
extern char textbuffer[4][16];

// All spel-relaterade funktioner
void fill(int x, int y, uint8_t *array);
void clear_text(void);
void clear();
void run_game(void);
void flappy_game(void);
