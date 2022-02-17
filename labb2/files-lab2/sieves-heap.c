#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define COLUMNS 6

int column_count = 0;

void print_number(int number){
	printf("%10d", number);
	column_count++;
	if(column_count%COLUMNS == 0){ //denna if satas gör så att vi börjar på ny rad efter 6 siffor
	printf("\n");
	}
}

void print_sieves(int input_value){

/*
 * psudokod för seives algoritm
 * input: an int n < 1 
 * output: all prime numbers from 2 too n
 *
 * let A be an arrat of boolean values, indexed by in 2 to n,
 * initially all set to true.
 *
 * for i = 2,3,4,..., not exceeding ??? do 
 * 	if A[i] is true 
 * 		for j = i2,i2+i,i2+2i,i2+3i,..., not exeeding n do 
 * 			A[j] := false
 *
 * return all i such that A[i] is true 
*/

	int array_size = input_value - 1; // initterar arrayn vi kommer använda
	char *amount_numbers = malloc (sizeof (char) *array_size); // lokal array
		//tilldela minne från arrayn eftersom den är dynamisk
		//malloc allokerar minne i heapen


	for(int i = 0; i < array_size; i++){
	amount_numbers[i] = 1;
	}


	for(int i = 2; i <= (int) sqrt(input_value); i++){
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
	free(amount_numbers);
}





// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
	clock_t begin = clock();
  if(argc == 2)
    print_sieves(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  	
  	clock_t end = clock();
	double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
	printf("\n Executed in : %1f seconds\n", time_spent);

  return 0;
}
