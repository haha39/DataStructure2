#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Max_Stack_Size 250 

typedef enum {
	lparen,
	rparen, 
	plus, 
	minus, 
	times, 
	divide, 
	mod, 
	greaterThan, 
	lessThan, 
	bitAnd, 
	bitXor, 
	bitOr, 
	blank, 
	eos, 
	operand, 
	errorKey
} precedence;

precedence stack[Max_Stack_Size];	//nice
int top = -1;

void push(precedence item);
precedence pop();
void stackFull();
precedence stackEmpty();
void inToPrefix(char*, int, int*);	//turn infix into prefix with blank 
precedence getToken(char*, int*, char*);	//turn token into precedence
precedence getToken2(char);	//turn token into precedence
char getSymbol(precedence);	//turn token into precedence
int stackPriority(precedence );	//return priority of token
int incomingPriority(precedence );	//return priority of token

FILE *fptrR,*fptrW;

int main(int argc, char *argv[]) {
	fptrR = fopen("input_1.txt", "r");
	if(fptrR == NULL) {
		printf("fptrR error");
	}
	else {
		int isStr;
		fptrW = fopen("output_1.txt", "w");
		while(1) {
			char str[101] = {};
			isStr = fscanf(fptrR, " %s", &str);
			if(isStr != EOF) {
				int len = strlen(str), i, negCt=0;
				char inverseStr[len+1];
				precedence lastToken;
				
				//build inverse array and  negIndex array
				if(str[0] == '-')
					negCt++;
				for(i=0; i<len-1; i++) {
					if(str[len-i-1] == '-' && getToken2(str[len-i-2]) != operand) {	//this guy is a negactive sign
						negCt++;
					}
					inverseStr[i] = str[len-i-1];
				}
				inverseStr[len-1] = str[0];
				inverseStr[len] = '\0';
				
				//to remember which index is negative symbol
				int negIndex[negCt], index = negCt-1;
				if(str[0] == '-') {
					negIndex[index--] = len - 1 - 0;
				}
				for(i=1; i<len; i++) {
					if(str[i] == '-' && getToken2(str[i-1]) != operand) {	//this guy is a negactive sign
						negIndex[index--] = len - 1 - i;
					}
				}
				
				//ya
				inToPrefix(inverseStr, (len+1), negIndex);
			}
			else
				break;
		}
	}
	fprintf(fptrW,"\n\n");
	fclose(fptrR);
	fclose(fptrW);
	return 0;
}

void push(precedence item) {
	if(top >= Max_Stack_Size-1)
		stackFull();
	stack[++top] = item;
} 

precedence pop() {
	if(top == -1)
		return stackEmpty();
	return stack[top--];
}

void stackFull() {
	printf("yo, the stack is full");
	exit(EXIT_FAILURE);
}

precedence stackEmpty() {
	printf("hey, the stack is empty");
	return errorKey;
}

void inToPrefix(char *str, int len, int *negIndex) {
	int n=0, index=0, i=0, parenCt=0, blankCt=0, negI=0, operandCt=0;
	char inversePrefix[len*2], symbol;
	precedence token, defaultIsEos, catchpop, lastToken;	
	
	//let inverseinfix turn into postrock
	push(eos);
	lastToken = operand;	//clever setting
	for(token = getToken(&symbol,&n,str); token != eos; token = getToken(&symbol, &n,str)) {
		if(token != blank) {
			if(n == negIndex[negI]+1) {	//meet neg no blank
				inversePrefix[index++] = symbol;
				negI++;
			}
			else if(token == operand) {	//meet operand
				operandCt++;
				if(lastToken != operand && operandCt != 1) {
					inversePrefix[index++] = ' ';
					blankCt++;
				}
				inversePrefix[index++] = symbol;
			}
			else if(token == lparen) {	//meet lparen
				parenCt++;
				while(stack[top] != rparen) {
					catchpop = pop();
					inversePrefix[index++] = ' ';
					blankCt++;
					inversePrefix[index++] = getSymbol(catchpop);
				}
				pop();
			}
			else {		//meet others
				while(stackPriority(stack[top]) > incomingPriority(token)) {
					catchpop = pop();
					inversePrefix[index++] = ' ';
					blankCt++;
					inversePrefix[index++] = getSymbol(catchpop);
				}
				push(token);
			}
			lastToken = token;
		}
	}
	while((token = pop()) != eos) {		//pop remaind token
		inversePrefix[index++] = ' ';
		blankCt++;
		inversePrefix[index++] = getSymbol(token);
	}
	
	//let the weird postfix turn into prefix
	//»Ý­n'\0'¶Ü
	//int prefixLen = len-(parenCt*2);
	int prefixLen = len-(parenCt*2)+blankCt-1;
	char prefix[prefixLen];
	
	for(i = 0+(parenCt*2); i < len+blankCt-1; i++) {	//reverse again
		prefix[i-(parenCt*2)] = inversePrefix[len+blankCt-i-2];
	}
	
	for(i = 0; i < prefixLen; i++) {
		fprintf(fptrW, "%c", prefix[i]);
	}
	//printf("jojolion");	//to ensure that the last one is not blank
	fprintf(fptrW,"\n");
}

precedence getToken(char *symbol, int *n, char *str) {
	*symbol = str[(*n)++];
	switch(*symbol) {
		case '(' : return lparen;
		case ')' : return rparen;
		case '+' : return plus;
		case '-' : return minus;
		case '/' : return divide;
		case '*' : return times;
		case '%' : return mod;
		case '>' : return greaterThan;
		case '<' : return lessThan;
		case '&' : return bitAnd;
		case '^' : return bitXor;
		case '|' : return bitOr;
		case ' ' : return blank;
		case '\0' : return eos;
		default : return operand;
	}
}

precedence getToken2(char symbol) {
	switch(symbol) {
		case '(' : return lparen;
		case ')' : return rparen;
		case '+' : return plus;
		case '-' : return minus;
		case '/' : return divide;
		case '*' : return times;
		case '%' : return mod;
		case '>' : return greaterThan;
		case '<' : return lessThan;
		case '&' : return bitAnd;
		case '^' : return bitXor;
		case '|' : return bitOr;
		case ' ' : return blank;
		case '\0' : return eos;
		default : return operand;
	}
}

char getSymbol(precedence symbol) {
	switch(symbol) {
		case lparen : 		return '(';
		case rparen : 		return ')';
		case plus : 		return '+';
		case minus : 		return '-';
		case divide : 		return '/';
		case times : 		return '*';
		case mod : 			return '%';
		case greaterThan : 	return '>';
		case lessThan : 	return '<';
		case bitAnd : 		return '&';
		case bitXor : 		return '^';
		case bitOr : 		return '|';
	}
}	

int stackPriority(precedence symbol) {
	switch(symbol) {
		case lparen : return 19;
		case rparen : return 0;
		case plus : return 12;
		case minus : return 12;
		case divide : return 13;
		case times : return 13;
		case mod : return 13;
		case greaterThan : return 10;
		case lessThan : return 10;
		case bitAnd : return 8;
		case bitXor : return 7;
		case bitOr : return 6;
		case eos : return 0;
	}
}

int incomingPriority(precedence symbol) {
	switch(symbol) {
		case lparen : return 19;
		case rparen : return 20;
		case plus : return 12;
		case minus : return 12;
		case divide : return 13;
		case times : return 13;
		case mod : return 13;
		case greaterThan : return 10;
		case lessThan : return 10;
		case bitAnd : return 8;
		case bitXor : return 7;
		case bitOr : return 6;
		case eos : return 0;
	}
}




