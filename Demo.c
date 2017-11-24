/* 	

	Menu based program to test detINTAL function which takes 4 parameters,a being operand 1,b being operand 2,c being the result and the last parameter being the operation
	to be performed which is in the form of enum INTAL (refer to intal.h for the typedef of it).
	

	detINTAL is an intermediate function which takes care of the signs in the strings given by the user and does the appropriate action based on the parameters supplied to it.


	Size of character arrays in intal.h have been fixed at multiples of 1000000000 as values with more number of 0's gives a segmentation fault in the computer being used to test the code.

	intal.h and the Demo.c code both have been tested on Ubuntu 16.04 LTS with sufficient RAM for running with the size of character arrays used in both codes. 
	
	To fix Segmentation faults occuring during runtime,change the MAX_SIZE defined in intal.h to a size such that segmentation fault doesn't occur. (Reduce the number of zeros)
	
	
	intal.h does Addition,subtraction,multiplication,division for positive and negative integers and Exponentiation for postive powers(including 0) with a positive or negative base.

	Code last Modified on 7th March 2017 at IST 18:35:45

*/	


#include "intal.h"
#include<stdio.h>
int main(void){
	char *a,*b,*c;
	a=(char *)malloc(sizeof(char)*MAX_SIZE); //operand 1
	b=(char *)malloc(sizeof(char)*MAX_SIZE); //operand 2
	int k;
	while(1){
		c=(char *)malloc(sizeof(char)*2*MAX_SIZE); //result
		printf("\t\tCalculator\n\n1.Addition\n2.Subtraction\n3.Multiplication\n4.Division\n5.Exponentiation\n6.Exit\nPlease select an option: ");	
		scanf("%d",&k);
		printf("Operand 1:");
		scanf("%s",a);
		printf("Operand 2:");
		scanf("%s",b);
		switch(k){
			case 1: detINTAL(a,b,c,ADD);
				printf("\nResult: %s",c);		
				break;
			case 2: detINTAL(a,b,c,SUB);
				printf("\nResult: %s",c);
				break;
			case 3: detINTAL(a,b,c,MUL);
				printf("\nResult: %s",c);
				break;
			case 4: detINTAL(a,b,c,DIV);
				printf("\nResult: %s",c);				
				break;
			case 5: detINTAL(a,b,c,EXP);
				printf("\nResult: %s",c);
				break;
			case 6: free(a);
				free(b);
				exit(0);
			default:printf("Option doesn't exist. Please re-enter.");
		}
		printf("\n");
		free(c);
	}
	free(a);
	free(b);
	return 0;
}

/*
	Demo.c written by Arun John,01FB15ECS053.

*/
