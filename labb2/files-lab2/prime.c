/*
 prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>

int is_prime(int n){
  int i;

  for(i=2; i<=n-1; i++){ // böjrar med en loop som börjar på 2 som är första prim tal
  	if(n%i==0){	// tar sedan en modulo för att kolla om värdet är delbart med i
	return 0;	// returnerar noll isåfall, n-1 gör att vi aldrig kommer dela med sig sjäv.
	}
  }	
	if(i==n){ 	// dubbelkollar så de är samma
	return 1;	// returnerar 1
	}  
}

int main(void){
  printf("%d\n", is_prime(11));  // 11 is a prime.      Should print 1.
  printf("%d\n", is_prime(383)); // 383 is a prime.     Should print 1.
  printf("%d\n", is_prime(987)); // 987 is not a prime. Should print 0.
}
