
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define COLUMNS 6

void print_number(int number){
	printf("%10d", number);
	column_count++;
	if(column_count%COLUMNS == 0){
	printf("\n");
	}
}

void print_sieves(int input){

}





// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_primes(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}

