/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6

int column_count = 0;

void print_number(int number){ 		//en funktion som efter 6 rader prim tal gör en ny rad.
	printf("%10d", number);
	column_count++;
	if(column_count%COLUMNS == 0){
	printf("\n");
	}
}

int is_prime(int n){ 		//samma funktion från uppgift 1
  int i;

  for(i=2; i<=n-1; i++){
  	if(n%i==0){
	return 0;
	}
  }	
	if(i==n){
	return 1;
	}  
}

void print_primes(int n){
  // Should print out all prime numbers less than 'n'
  // with the following formatting. Note that
  // the number of columns is stated in the define
  // COLUMNS

  //printf("%10d ", 2);
  //printf("%10d ", 3);
  //printf("%10d ", 5);
  //printf("%10d ", 7);
  //printf("%10d ", 11);
  //printf("%10d ", 13);
  //printf("\n");
  //printf("%10d ", 17);
  //printf("%10d ", 19);

  int i = 0;
  for(i = 2; i<=n; i++){ 	//samma for loop som tidigare, 
  	if(is_prime(i)){	// om is prime returnerar det värdet som i antar så 
	print_number(i);	//  printar vi numret med print_number funktionen. 
	}
  }	
  printf("\n");
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
