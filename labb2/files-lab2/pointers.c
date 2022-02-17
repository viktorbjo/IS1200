


#include <stdio.h>

char* text1 = "This is a string.";
char* text2 = "Yet another thing.";

//vi anänvder värdet 20 eftersom att asm använder 80 bytes lagring medans int 4 (80/4)
int list1[20];		//int för att få hexa värde
int list2[20];		//printlist callar också efter int array
int count = 0;		//definerar count globalt i minnet

void copycodes(char* text, int* list, int* count){
	while(*text != 0){	//beq $to, $0, done
	*list = *text;		//lb $t0,0($a0) och sw $t0,0($a1)

	text += 1;		//addi $a0,$a0,1 
	list += 1;		//addi $a1,$a1,4

	(*count)++; 		//addi $t1,$t1,1
	}
}

void work(){
	copycodes(text1, list1, &count);

	copycodes(text2, list2, &count);
}

void printlist(const int* lst){
  printf("ASCII codes and corresponding characters.\n");
  while(*lst != 0){
    printf("0x%03X '%c' ", *lst, (char)*lst);
    lst++;
  }
  printf("\n");
}

void endian_proof(const char* c){
  printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n", 
         (int)*c,(int)*(c+1), (int)*(c+2), (int)*(c+3));
  
}

int main(void){
  work();

  printf("\nlist1: ");
  printlist(list1);
  printf("\nlist2: ");
  printlist(list2);
  printf("\nCount = %d\n", count);

  endian_proof((char*) &count);
}
