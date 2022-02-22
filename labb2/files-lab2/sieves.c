
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define COLUMNS 6

int column_count = 0;

void print_number(int number){
	printf("%10d", number);
	column_count++;
	if(column_count%COLUMNS == 0){
	printf("\n");
	}
}

void print_sieves(int input_value){
	int array_size = input_value - 1; // initterar arrayn vi kommer använda
	char amount_numbers[array_size]; // lokal array

	for(int i = 0; i < array_size; i++){ // vi fyller arrayen med ettor
	amount_numbers[i] = 1;
	} 


	for(int i = 2; i <= (int) sqrt(input_value); i++){ //vi kollar kvadraten av inputet.
		if(amount_numbers[i] == 1){	//detta är för att kolla om vi redan kollat nummret
			for(int j = i*i; j <= input_value; j+=i){ //för varje mulptipel av numret
			amount_numbers[j] = 0; //makrerar som ett icke prime
			}
		}
		
	}
	
	//printa ut alla sanna värden från arrayn med start från plats 2	
	for(int i = 2; i<= array_size; i++){
		if(amount_numbers[i] == 1){
		print_number(i);
		}
	}
}





// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_sieves(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}

