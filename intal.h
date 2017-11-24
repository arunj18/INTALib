typedef enum {ADD,SUB,MUL,DIV,EXP} INTAL;
#define MAX_SIZE 1000000000 //change this in case of segmentation faults
/*

		To fix Segmentation faults occuring during runtime,change the MAX_SIZE defined in intal.h to a size such that segmentation fault doesn't occur. (Reduce the number of zeros)
	
		Code last Modified on 7th March 2017 at IST 18:35:42
*/
#include<string.h>
#include<stdlib.h>
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void add_zeros(char* src, unsigned long int n){ //function for adding zeroes
	int lensrc = strlen(src);
  	for(int i=lensrc-1+n;i>=n;--i){
	    	src[i] = src[i - n];
	}
	src[lensrc + n] = 0;
  	for(int i=0;i<n;++i){
    		src[i] = '0';
  	}
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void remove_zeros(char* src){ //function for removing zeros from starting of string
  	int lensrc = strlen(src);
  	int ind = 0;
  	while (ind < lensrc && src[ind] == '0'){
    	++ind;
  	}
  	for (int i = ind; i < lensrc; ++i){
    	src[i - ind] = src[i];
  	}
  	src[lensrc - ind] = 0;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void makeEqualLength(char *op1,char *op2){ //function for equating length
	unsigned long int lena=strlen(op1);
	unsigned long int lenb=strlen(op2);
	if(lena==lenb)
		return;
	if(lena>lenb)
		add_zeros(op2,lena-lenb);
	else
		add_zeros(op1,lenb-lena);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void addNum(char *op1,char *op2,char *res){ //function for adding two numbers (only positive integers)
	if(op2==NULL)
		memcpy(op2,op1,strlen(op1));
	makeEqualLength(op1,op2);
	int carry=0,check;
	for(int i=strlen(op1)-1;i>=0;i--){
		check=carry+(op1[i]-'0'+op2[i]-'0');
		carry=check/10;
		res[i]=(check%10)+'0';
	}
	res[strlen(op1)]='\0';
	if(carry>0){
		for(int i=strlen(op1)+1;i>0;i--)
			res[i]=res[i-1];
		res[0]=carry+'0';
		res[strlen(op1)+1]='\0';
	}
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void subNum(char *op1,char *op2,char *res){ //function for subtracting two numbers.assuming a>b always
	makeEqualLength(op1,op2);
	int check;
	for(int i=strlen(op1)-1;i>=0;i--){
		check=(op1[i]-'0'-(op2[i]-'0'));
		if(check<0){
			int j=i-1;
			while(j>=0 && res[j]=='0'){
				j--;	
			}
			if(j>=0){
				op1[j]=((op1[j]-'0')-1)+'0';
				for(int k=j+1;k<i;k++)
					res[k]=9+'0';
				check=10+check;
			}	
		}
		res[i]=check+'0';
	}
	res[strlen(op1)]='\0';
	remove_zeros(res);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
int isNeg(char *src){ //function for checking if the number is negative
	if(src[0]=='-')
		return 1;
	return 0;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void makeNeg(char *src){ //function for making the number negative
	for(int i=strlen(src)+1;i>0;i--)
		src[i]=src[i-1];
	src[0]='-';
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void makeUsa(char *src){ //function for making the number usable for operations i.e. removing the sign
	for(int i=0;i<strlen(src);i++)
		src[i]=src[i+1];
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
int detBigger(char *op1,char *op2){ //function to determine which number is bigger
	int i;	
	if(strlen(op1)>strlen(op2))
		return 1;
	else if(strlen(op1)<strlen(op2))
		return -1;
	for(i=0;i<=strlen(op1);i++){
		if((op1[i]-'0')>(op2[i]-'0'))
			return 1;
		else if((op1[i]-'0')<(op2[i]-'0'))
			return -1;
	}
	if(i==strlen(op1))
		return 0;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void mul10(char *src,int n){ //function for multiplying number with 10
	int len=strlen(src);
	for(int i=len;i<len+n;i++)
		src[i]='0';
	src[len+n]='\0';
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void mulNum(char *op1,char *op2,char *res){ //bruteforce multiplication for two numbers
	makeEqualLength(op1,op2);
	int carry=0,check;
	strcpy(res,"0");
	for(int i=strlen(op1)-1;i>=0;i--){
		carry=0;		
		char *temp=(char *)(malloc(sizeof(char)*MAX_SIZE));
		for(int j=strlen(op2)-1;j>=0;j--){
			check=carry+((op1[j]-'0')*(op2[i]-'0'));
			carry=check/10;
			temp[j]=(check%10)+'0';
		}
		temp[strlen(op1)]='\0';
		if(carry>0){
			for(int i=strlen(op1)+1;i>0;i--)
				temp[i]=temp[i-1];
			temp[0]=carry+'0';
			temp[strlen(op1)+1]='\0';
		}
		mul10(temp,strlen(op1)-1-i);
		addNum(temp,res,res);
		free(temp);
	}
	remove_zeros(res);		
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void detINTAL(char *op11,char *op21,char *res,INTAL n){ //function to determine which INTAL operation to perform and is the only function that the client should use
	int big;
	char *one=(char *)(malloc(sizeof(char)*MAX_SIZE));
	char *op1=(char *)(malloc(sizeof(char)*MAX_SIZE));
	char *op2=(char *)(malloc(sizeof(char)*MAX_SIZE));
	memcpy(op1,op11,strlen(op11));
	memcpy(op2,op21,strlen(op21));
	strcpy(one,"1");	
	int isNega=isNeg(op1),isNegb=isNeg(op2),isNegc;
	if(n==ADD){ //different cases in addition,taking care of sign
		if(isNega && isNegb){
			makeUsa(op1);
			makeUsa(op2);
			addNum(op1,op2,res);
			makeNeg(res);
		}
		else if(isNega){ 
			makeUsa(op1);
			big=detBigger(op1,op2);
			if(big==1){
				subNum(op1,op2,res);
				makeNeg(res);
			}
			else if(big==-1)
				subNum(op2,op1,res);
			else
				strcpy(res,"0");
		}
		else if(isNegb){
			makeUsa(op2);
			big=detBigger(op1,op2);
			if(big==1)
				subNum(op1,op2,res);
			else if(big==-1){
				subNum(op2,op1,res);
				makeNeg(res);
			}				
			else
				strcpy(res,"0");
		}
		else
			addNum(op1,op2,res);
	}
	if(n==SUB){ //different cases in subtraction,taking care of sign
		if(isNega && isNegb){
			makeUsa(op1);
			makeUsa(op2);
			big=detBigger(op1,op2);
			if(big==1){
				subNum(op1,op2,res);
				makeNeg(res);
			}
			else if(big==-1)
				subNum(op2,op1,res);
			else
				strcpy(res,"0");
		}
		else if(isNega){
			makeUsa(op1);
			addNum(op1,op2,res);
			makeNeg(res);
		}
		else if(isNegb){
			makeUsa(op2);
			addNum(op1,op2,res);
		}
		else{
			big=detBigger(op1,op2);
			if(big==1)
				subNum(op1,op2,res);
			else if(big==-1){
				subNum(op2,op1,res);
				makeNeg(res);
			}
			else
				strcpy(res,"0");			
		}
	}
	if(n==MUL){ //different cases in multiplication,taking care of sign
			if(isNega)
				makeUsa(op1);
			if(isNegb)
				makeUsa(op2);
			if(strcmp(op1,"0")==0 || strcmp(op2,"0")==0){
				strcpy(res,"0");
				return;
			}
			mulNum(op1,op2,res);
			if(!((isNega && isNegb) || (!isNega && !isNegb)))
				makeNeg(op1);	
	}
	if(n==DIV){ //different cases in division,taking care of sign
		if(isNega)
			makeUsa(op1);
		if(isNegb)
			makeUsa(op2);		
		strcpy(res,"0");
		int flag=detBigger(op1,op2);	
		while(flag>0){
			subNum(op1,op2,op1);
			remove_zeros(op2);
			addNum(one,res,res);
			flag=detBigger(op1,op2);
		}
		if(!((isNega && isNegb) || (!isNega && !isNegb)))
				makeNeg(res);	
	}
	if(n==EXP){ //different cases in exponentiation,taking care of sign
		strcpy(res,"1");
		if(isNega)
				makeUsa(op1);
		while(strcmp(op2,"0")>0){
			char *temp=(char *)(malloc(sizeof(char)*MAX_SIZE));			
			isNegc=isNeg(res);
			if(isNegc)
				makeUsa(res);
			mulNum(op1,res,temp);
			memcpy(res,temp,strlen(temp));		
			if(isNega && !isNegc)
				makeNeg(res);
			subNum(op2,one,op2);
			free(temp);
		}
	}
	free(one);
	free(op1);
	free(op2);
}
//----------------------------------------------------------------------------------------END-----------------------------------------------------------------------------------------------------//

/*
	INTAL.H Written by Arun John (01FB15ECS053)
*/
