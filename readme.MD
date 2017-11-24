This repository is for the implementation of the INTAL library on C.

To use this library, include the intal.h header file in your C program and use the detINTAL function which takes the following parameters:-

char * operand1, char * operand2, char * result, INTAL operation

operand1,operand2 and result have to be strings (terminate with a '\0') for the detINTAL to work on the operands.

Also included is Demo.c which shows a sample usage of the intal library.

Note: Change the MAX_SIZE in intal.h if using the intal library with your program results in a segmentation fault. The MAX_SIZE depends on 	 the machine you are using and various local parameters. 

