/*
*幾個stove， 幾個cut 幾個ohter  
*記得要加1喔
*先放5
*每次放都放少的
*接著再放3
*每次都放少的 
*從orders[][1]中找出最小的時間
*若有一樣的，兩者中看誰orders[][3]比較大就用它 
*做player1, player2的時間線，應該是用變數 
*加到p1, p2上 
*算錢 
*算時間， 記得other的那個要 1+ 
*把那個訂單[5] = 1 
*印出來 
*重來 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//to build the recipe
typedef struct foodNode *foodPointer;
typedef struct foodNode {
	int ct;				//this is the ct time to cook this food
	int type;			//0 : stove, 1 : cut, 2 : presentation
	int foodLen;		//if len = 0, it means this type do not exist 
	char foodName[50];
	foodPointer flink;
}foodNode;
foodPointer ftemp;

typedef struct headNode *headPointer;
typedef struct headNode {
	int serialNumber;	//start from 0
	int foodLen;
	int stoveNum;
	int cutNum;
	int otherNum;		//please remember to add 1
	char foodName[50];
	headPointer hlink;
	foodPointer flink;
}headNode;
headPointer head, htemp;

#define TRUE 1
#define MaxNum 400

FILE *fptrRrecipes, *fptrRorders, *fptrW;

int main(int argc, char *argv[]) {
	//initialize recipes
	fptrRrecipes = fopen("recipes.txt", "r");
	if(fptrRrecipes == NULL) {
		printf("fptrRrecipes error");
		exit(1);
	}
	int recipeNum, i, j, k, foodLen, lastLen, comma;
	char c;
	fscanf(fptrRrecipes,"%d\n", &recipeNum);
	printf("the recipe num is : %d\n", recipeNum);
	for(i = 0; i < recipeNum; i++) {
		printf("i = %d\n",i);
		//headnode
		headPointer hnode;
		hnode = (headNode*)malloc(sizeof(headNode));
		hnode->hlink = NULL;
		//build vertical link
		if( i == 0) {	//const head pointer
			head = hnode;
			htemp = hnode;
		}
		else {
			htemp->hlink = hnode;
			htemp = hnode;
		}
		hnode->serialNumber = i;
		//to read food name
		foodLen = 0;
		for(j = 0; j < MaxNum; j++) {
			c = fgetc(fptrRrecipes);
			if(c == ' ') {
				hnode->foodLen = foodLen;
				break;
			}
			else {
				hnode->foodName[j] = c;
				foodLen++;}
		}
		//to read stove, cut, other
		foodPointer fnode;
		fnode = (foodNode*)malloc(sizeof(foodNode));
		hnode->flink = fnode;
		fnode->flink = NULL;
		ftemp = fnode;
		for(j = 0; j < 3; j++) {
			printf("j = %d\n",j);
			foodLen = 0;	
			lastLen = -1;
			comma = 0;
			for(k = 0; k < MaxNum; k++) {
				c = fgetc(fptrRrecipes);
				printf("read : %c	%d	\n", c, ftemp->type/*, ftemp->foodName[k-lastLen-1]*/);
				if(c == ' ') {
					fnode->foodLen = foodLen;
					if(j == 1 || comma == 1) {				
						ftemp->flink = fnode;
					}
					ftemp = fnode;
					foodLen = 0;				//last three line 
					fnode = (foodNode*)malloc(sizeof(foodNode));
					fnode->flink = NULL;/**/
					break;
				}
				else if(c == '\n' || c == EOF) {
					fnode->foodLen = foodLen;
					ftemp->flink = fnode;
					ftemp = fnode;
					break;
				}
				else if(c == 'x') {
					foodLen = -1;				//
					fnode->ct = 0;
					fnode->foodName[0] = 'x';
					fnode->type = j;			//oh ya
					
					//ftemp->flink = fnode;
					//ftemp = fnode;
					//c = fgetc(fptrRrecipes);	//blank
					//break;
				}
				else if(c == ',') {
					//Ct++;
					fnode->foodLen = foodLen;	//first three line equals meet ' '
					ftemp->flink = fnode;
					ftemp = fnode;
					
					comma = 1;
					lastLen += foodLen;
					lastLen++; 
					foodLen = 0;				//last three line 
					//foodPointer fnode;
					fnode = (foodNode*)malloc(sizeof(foodNode));				
					fnode->flink = NULL;/**/
				}
				else {
					printf("read : %c	%d	%c\n", c, ftemp->type, ftemp->foodName[k-lastLen-1]);
					foodLen++;
					fnode->ct = 0;
					fnode->type = j;
					fnode->foodName[k-lastLen-1] = c;
					printf("%d - %d - 1 = %d\n", k, lastLen, k-lastLen-1);
					printf("%c\n",fnode->foodName[k-lastLen-1]);
					printf("%c\n",ftemp->foodName[0]);/**/
				}
			}
			/*foodPointer fnode;
			fnode = (foodNode*)malloc(sizeof(foodNode));
			fnode->flink = NULL;*/
			//otherCt = Ct;
		}
	}
	printf("jojo the world\n");	
	//count the stove cut other num of each food
	int stoveCt, cutCt, otherCt;
	htemp = head;
	for(; htemp; htemp = htemp->hlink) {
		printf("%d",i++);
		printf("\n");
		printf("%d %d %c\n", htemp->foodLen, htemp->serialNumber, htemp->foodName[0]);
		ftemp = htemp->flink;
		stoveCt = 0;
		cutCt = 0;
		otherCt = 0;
		for(; ftemp; ftemp = ftemp->flink) {
			if((ftemp->type == 0) && (ftemp->foodLen != -1)) {
				printf("%d %d %d\n", stoveCt, cutCt, otherCt);
				printf("%d %d %c\n", ftemp->foodLen, ftemp->type, ftemp->foodName[0]);				
				stoveCt++;
			}
			else if((ftemp->type == 1) && (ftemp->foodLen != -1)) {
				cutCt++;
			}
			else if((ftemp->type == 2) && (ftemp->foodLen != -1)) {
				otherCt++;
			}
			printf("%d %d %d\n", stoveCt, cutCt, otherCt);
			printf("%d %d %c\n", ftemp->foodLen, ftemp->type, ftemp->foodName[0]);
		}
		htemp->stoveNum = stoveCt;
		htemp->cutNum = cutCt;
		htemp->otherNum = otherCt; 
	}
	//print recipe
	printf("j\n");
	htemp = head;
	for(; htemp; htemp = htemp->hlink) {
		printf("\n");
		printf("%d %d %c	", htemp->foodLen, htemp->serialNumber, htemp->foodName[0]);
		printf("%d %d %d\n", htemp->stoveNum, htemp->cutNum, htemp->otherNum);
		ftemp = htemp->flink;
		for(; ftemp; ftemp = ftemp->flink) {
			printf("%d %d %c\n", ftemp->foodLen, ftemp->type, ftemp->foodName[0]);
		}
	}/**/
	printf("\nj\n");
	//initialize orders
	fptrRorders = fopen("orders.txt", "r");
	if(fptrRorders == NULL) {
		printf("fptrRorders error");
		exit(1);
	}
	const int ordersNum;
	fscanf(fptrRorders,"%d\n", &ordersNum);
	printf("the order num is : %d\n\n", ordersNum);
	int lenCt;
	int iorders[ordersNum][7];	//iorders[5] default = -1, means out of deadline, = -2 -> test and fail, iorders[6] = foodlen
	char corders[ordersNum][50];
	//print orders
	for(i = 0; i < ordersNum; i++) {
		fscanf(fptrRorders, "%d ", &iorders[i][0]);
		j = 0;
		lenCt = 0;
		while(TRUE) {
			c = fgetc(fptrRorders);
			if(c == ' ') {
				break;
			}
			corders[i][j++] = c;
			lenCt++;
		}
		iorders[i][6] = lenCt;
		fscanf(fptrRorders, "%d %d %d %d\n", &iorders[i][1], &iorders[i][2], &iorders[i][3], &iorders[i][4]);
		iorders[i][5] = -1;
		printf("%d\t%c%c%c\t%d\t%d\t%d\t%d\t%d\t%d\n", iorders[i][0], corders[i][0],corders[i][1],corders[i][2]
		, iorders[i][1], iorders[i][2], iorders[i][3], iorders[i][4], iorders[i][5], iorders[i][6]);
	}
	//initialize sequence
	int commandCt, Stimeline, Ctimeline, tempP1, tempP2, tempCommandCt, failNum, successNum, earliest, latest, money;
	failNum = 0;
	successNum = 0;
	commandCt = 0;
	tempCommandCt = 0;
	Stimeline = 0;
	Ctimeline = 0;
	latest = 0;
	money = 0;
	
	/**/for(i = 0; i < ordersNum; i++) {
		if(iorders[i][1] > iorders[latest][1]) {
			latest = i;	
		}
	}
	printf("latest 送進來的時間是%d\n",  iorders[latest][1]);
	
	//start to work!
	while(TRUE) {
		//printf("Player1 : %d \n", tempP1);
		//printf("Player2 : %d \n", tempP2);
		printf("\nStimeline : %d \n", Stimeline);
		printf("Ctimeline : %d \n", Ctimeline);		
		if((failNum + successNum) == ordersNum) {
			break;
		}
		tempCommandCt = 0;
		//找出這次要做哪個訂單 //
		earliest = latest;
		for(i = 0; i < ordersNum; i++) {
			if(iorders[i][5] == -1) {									//此筆訂單還沒做過
				//if(iorders[i][1] <= present) {							//還有機會做的訂單們 
					if(iorders[i][1] < iorders[earliest][1]) {			//找到更早可以做的訂單 
						earliest = i;
					}
					else if(iorders[i][1] == iorders[earliest][1]) {	//若是時間一樣就看誰的報酬比較好 
						if(iorders[i][3] > iorders[earliest][3]) {		//報酬比較高 
							earliest = i;
						}
					}
				//}
				/*else {													//來不雞柳
					iorders[i][5] = -2;		
				}*/ 
			}
		}
		printf("現在要做的是第%d號訂單 送來的時間是: %d\n", iorders[earliest][0], iorders[earliest][1]);
		//找到對應食譜 
		htemp = head;
		for(i = 0; i < recipeNum; i++) {
			//printf("%d %d\n", htemp->foodLen, iorders[earliest][6]);
			if(htemp->foodLen == iorders[earliest][6]) {
				for(j = 0; j < htemp->foodLen; j++) {
					if((htemp->foodName[j] != corders[earliest][j])) {
						//printf("%c %c", htemp->foodName[j], corders[earliest][j]);
						htemp = htemp->hlink;
						break;
					}
				}
			}
			else {
				//printf("hahahahahaha\n");
				htemp = htemp->hlink;
				//printf("%d haha\n", htemp->foodLen);
			}
		}
		printf("這個訂單叫做 : \n");
		for(i = 0; i < htemp->foodLen; i++) {
			printf("%c", htemp->foodName[i]);
		}
		printf("\n");
		//來做啊!來啊!!
		//來啊!
		//初始值 
		//printf("Player1 : %d \n", tempP1);
		//printf("Player2 : %d \n", tempP2);
		printf("Stimeline : %d \n", Stimeline);
		printf("Ctimeline : %d \n", Ctimeline);			
		if(iorders[earliest][1] > tempP1) {
			tempP1 = iorders[earliest][1];
		}
		if(iorders[earliest][1] > tempP2) {
			tempP2 = iorders[earliest][1];
		}
		if(iorders[earliest][1] > Stimeline) {
			Stimeline = iorders[earliest][1];
		}
		if(iorders[earliest][1] > Ctimeline) {
			Ctimeline = iorders[earliest][1];
		}		
		//printf("Player1 : %d \n", tempP1);
		//printf("Player2 : %d \n", tempP2);
		printf("Stimeline : %d \n", Stimeline);
		printf("Ctimeline : %d \n", Ctimeline);			
		//stove
		for(i = 0; i < htemp->stoveNum; i++) {
			tempCommandCt++;
			if(Stimeline > tempP1) {	//代表爐子目前在被使用中 	
				tempP1 = Stimeline + 5;
				Stimeline = tempP1;
			}
			else if(Stimeline > tempP2) {
				tempP2 = Stimeline + 5;
				Stimeline = tempP2;				
			}
			else
			{
				if(tempP1 < tempP2) {
					tempP1 += 5;
					Stimeline = tempP1;
				}
				else {
					tempP2 += 5;
					Stimeline = tempP2;	
				}				
			}
		}
		//cut
		for(i = 0; i < htemp->cutNum; i++) {
			tempCommandCt++;
			if(Ctimeline > tempP1) {	//代表爐子目前在被使用中 
				tempP1 = Ctimeline + 3;
				Ctimeline = tempP1;
			}
			else if(Ctimeline > tempP2) {
				tempP2 = Ctimeline + 3;
				Ctimeline = tempP2;				
			}
			else
			{
				if(tempP1 < tempP2) {
					tempP1 += 3;
					Ctimeline = tempP1;
				}
				else {
					tempP2 += 3;
					Ctimeline = tempP2;	
				}				
			}
		}
		//other
		tempCommandCt++;
		if(tempP1 < tempP2) {	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			tempP2 += htemp->otherNum + 1;
		}
		else {
			tempP1 += htemp->otherNum + 1;	
		}
		if((tempP1 - 1 >= iorders[earliest][2]) || (tempP2 - 1 >= iorders[earliest][2])) {	//超時了 
			iorders[earliest][5] = -2;
			money -= iorders[earliest][4];
			failNum++;
			//break;
		}
		else
		{
			money += iorders[earliest][3];
			commandCt += tempCommandCt;
			iorders[earliest][5] = 1;
			successNum++;
		}
		printf("money : %d \n\n", money);
		printf( "commandCtcommandCt  %d\n", commandCt);
		//printf("Player1 : %d \n", tempP1);
		//printf("Player2 : %d \n\n\n", tempP2);
		printf("Stimeline : %d \n", Stimeline);
		printf("Ctimeline : %d \n\n", Ctimeline);			
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	tempP1 = 0;
	tempP2 = 0;
	Stimeline = 0;
	Ctimeline = 0;
	printf("\n\n爽拉\n");
	printf("money : %d \n\n", money);
	fptrW = fopen("players.txt", "w");
	printf( "%d\n", commandCt);
	fprintf(fptrW, "%d\n", commandCt);
	while(TRUE) {
		if(successNum == 0) {
			break;
		}
		printf("\nStimeline : %d \n", Stimeline);
		printf("Ctimeline : %d \n", Ctimeline);		
		//找出這次要做哪個訂單 
		earliest = latest;
		for(i = 0; i < ordersNum; i++) {
			if(iorders[i][5] == 1) {									//此筆訂單還沒做過
				//if(iorders[i][1] <= present) {							//還有機會做的訂單們 
					if(iorders[i][1] < iorders[earliest][1]) {			//找到更早可以做的訂單 
						earliest = i;
					}
					else if(iorders[i][1] == iorders[earliest][1]) {	//若是時間一樣就看誰的報酬比較好 
						if(iorders[i][3] > iorders[earliest][3]) {		//報酬比較高 
							earliest = i;
						}
					}
				//}
				/*else {													//來不雞柳
					iorders[i][5] = -2;		
				}*/ 
			}
		}
		printf("現在要做的是第%d號訂單 送來的時間是: %d\n", iorders[earliest][0], iorders[earliest][1]);
		//找到對應食譜 
		htemp = head;
		for(i = 0; i < recipeNum; i++) {
			//printf("%d %d\n", htemp->foodLen, iorders[earliest][6]);
			if(htemp->foodLen == iorders[earliest][6]) {
				for(j = 0; j < htemp->foodLen; j++) {
					if((htemp->foodName[j] != corders[earliest][j])) {
						//printf("%c %c", htemp->foodName[j], corders[earliest][j]);
						htemp = htemp->hlink;
						break;
					}
				}
			}
			else {
				//printf("hahahahahaha\n");
				htemp = htemp->hlink;
				//printf("%d haha\n", htemp->foodLen);
			}
		}
		printf("這個訂單叫做 : \n");
		for(i = 0; i < htemp->foodLen; i++) {
			printf("%c", htemp->foodName[i]);
		}
		printf("\n");
		//來做啊!來啊!!
		//來啊!
		//初始值 
		if(iorders[earliest][1] > tempP1) {
			tempP1 = iorders[earliest][1];
		}
		if(iorders[earliest][1] > tempP2) {
			tempP2 = iorders[earliest][1];
		}
		if(iorders[earliest][1] > Stimeline) {
			Stimeline = iorders[earliest][1];
		}
		if(iorders[earliest][1] > Ctimeline) {
			Ctimeline = iorders[earliest][1];
		}		
		//printf("Player1 : %d %d\n", tempP1, P1);
		//printf("Player2 : %d %d\n", tempP2, P2);
		printf("Stimeline : %d \n", Stimeline);
		printf("Ctimeline : %d \n\n", Ctimeline);		
		ftemp = htemp->flink;
		//stove
		for(i = 0; i < htemp->stoveNum; i++) {
			if(Stimeline > tempP1) {	//代表爐子目前在被使用中 
				//tempP1 = Stimeline + 5;
				//Stimeline = tempP1;			
				printf("1 %d %d s ", Stimeline, iorders[earliest][0]);
				fprintf(fptrW, "1 %d %d s ", Stimeline, iorders[earliest][0]);				
				tempP1 = Stimeline + 5;
				Stimeline = tempP1;
			}
			else if(Stimeline > tempP2) {
				//tempP2 = Stimeline + 5;
				//Stimeline = tempP2;					
				printf("2 %d %d s ", Stimeline, iorders[earliest][0]);
				fprintf(fptrW, "2 %d %d s ", Stimeline, iorders[earliest][0]);				
				tempP2 = Stimeline + 5;
				Stimeline = tempP2;				
			}
			else
			{
				if(tempP1 < tempP2) {
					printf("111111 %d %d s ", tempP1, iorders[earliest][0]);
					fprintf(fptrW, "1 %d %d s ", tempP1, iorders[earliest][0]);					
					tempP1 += 5;
					Stimeline = tempP1;
				}
				else {
					printf("2 %d %d s ", tempP2, iorders[earliest][0]);
					fprintf(fptrW, "2 %d %d s ", tempP2, iorders[earliest][0]);					
					tempP2 += 5;
					Stimeline = tempP2;	
				}
			}
			for(j = 0; j < ftemp->foodLen; j++) {
				printf("%c", ftemp->foodName[j]);
				fprintf(fptrW, "%c", ftemp->foodName[j]);					
			}
			printf("\n");
			fprintf(fptrW, "\n");
			ftemp = ftemp->flink;
		}
		if(htemp->stoveNum == 0) {
			ftemp = ftemp->flink;
		}
		//cut
		for(i = 0; i < htemp->cutNum; i++) {
			printf( "%d %d %d\n\n", Ctimeline, tempP1, tempP2);
			if(Ctimeline > tempP1) {	//代表爐子目前在被使用中 
				//tempP1 = Ctimeline + 3;
				//Ctimeline = tempP1;			
				printf("1 %d %d c ", Ctimeline, iorders[earliest][0]);
				fprintf(fptrW, "1 %d %d c ", Ctimeline, iorders[earliest][0]);				
				tempP1 = Ctimeline + 3;
				Ctimeline = tempP1;
			}
			else if(Ctimeline > tempP2) {
				//tempP2 = Ctimeline + 3;
				//Ctimeline = tempP2;					
				printf("2 %d %d c ", Ctimeline, iorders[earliest][0]);
				fprintf(fptrW, "2 %d %d c ", Ctimeline, iorders[earliest][0]);					
				tempP2 = Ctimeline + 3;
				Ctimeline = tempP2;			
			}
			else
			{
				if(tempP1 < tempP2) {
					printf("1 %d %d c ", tempP1, iorders[earliest][0]);
					fprintf(fptrW, "1 %d %d c ", tempP1, iorders[earliest][0]);					
					tempP1 += 3;
					Ctimeline = tempP1;
				}
				else {			
					printf("2 %d %d c ", tempP2, iorders[earliest][0]);
					fprintf(fptrW, "2 %d %d c ", tempP2, iorders[earliest][0]);					
					tempP2 += 3;
					Ctimeline = tempP2;	
				}
			}
			for(j = 0; j < ftemp->foodLen; j++) {
				printf("%c", ftemp->foodName[j]);
				fprintf(fptrW, "%c", ftemp->foodName[j]);					
			}
			printf("\n");
			fprintf(fptrW, "\n");
			ftemp = ftemp->flink;
		}
		//other
		if(tempP1 < tempP2) {	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			printf("2 %d %d f \n", tempP2, iorders[earliest][0]);
			fprintf(fptrW, "2 %d %d f\n", tempP2, iorders[earliest][0]);
			tempP2 += htemp->otherNum + 1;
		}
		else {
			printf("1 %d %d f \n", tempP1, iorders[earliest][0]);
			fprintf(fptrW, "1 %d %d f\n", tempP1, iorders[earliest][0]);
			tempP1 += htemp->otherNum + 1;	
		}
		//printf("Player1 : %d %d\n", tempP1, P1);
		//printf("Player2 : %d %d\n", tempP2, P2); 
		iorders[earliest][5] = -1;
		//money += iorders[earliest][3];
		//printf("MONEY :　%d\n", money);
		successNum--;
		printf("Stimeline : %d \n", Stimeline);
		printf("Ctimeline : %d \n\n", Ctimeline);
	}
	
	
	
	
	
	//如果1做完2再送餐 阿那1可以接下一單嗎
	//而且other只能塞大的 
	//please remember to add 1
	//please remember to add 1
	//please remember to add 1
	//please remember to add 1
	//please remember to add 1
	//please remember to add 1
	//please remember to add 1
	//please remember to add 1
	printf("\n\nMMMMMMMMMMMMMMONEY :　%d\n", money);
	fclose(fptrRrecipes);
	fclose(fptrRorders);
	fclose(fptrW);
	return 0;
}

/*
*上面先算每個食譜的時間 各 要花多久 
*用headnode去存 
*記得是float
*幾個stove， 幾個cut 幾個ohter  
*記得要加1喔
*先放5
*每次放都放少的
*接著再放3
*每次都放少的 
*從orders[][1]中找出最小的時間
*若有一樣的，兩者中看誰orders[][3]比較大就用它 
*做player1, player2的時間線，應該是用變數 
*加到p1, p2上 
*算錢 
*算時間， 記得other的那個要 1+ 
*把那個訂單[5] = 1 
*印出來 
*重來 
*/





