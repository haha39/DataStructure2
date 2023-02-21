#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listNode *listPointer;
typedef struct listNode {
	int data;
	listPointer link;
}listNode;
listPointer head;

#define IS_EMPTY(head) (!(head))
#define true 1

FILE *fptrR, *fptrW;

//if(!isdigit(firstline[0])) { return; }

int main(int argc, char *argv[]) {
	fptrR = fopen("input_1.txt", "r");
	if(fptrR == NULL) {
		printf("fptrR error");
	}
	else {
		char c;
		int value, isStr, nodeCt, i;
		nodeCt = 0;
		c = fgetc(fptrR);
		listPointer preNode, tail;
		preNode = (listNode*)malloc(sizeof(listNode) );
		head = preNode;
		//read to count node num
		/*if(c == 'e' || c == '\n') {	//nodeCt = 0
			printf("it's a empty list\n");
		}
		else {*/ 
		while(true) {	//count node number
			c = fgetc(fptrR);
			if(c == '\n') {
				 nodeCt++;
				 break;
			}
			else if(c == ' ') {
				nodeCt++;
			}
		}
		//build list
		printf("In the beginning. we have %d node.\n", nodeCt);
		fptrR = fopen("input_1.txt", "r");
		fscanf(fptrR, "%d ", &value);
		preNode->data = value;
		preNode->link = NULL;	//don't forget this step!
		
		for(i = 1; i < nodeCt; i++) {
			fscanf(fptrR, "%d ", &value);
			listPointer postNode;
			postNode = (listNode*)malloc(sizeof(listNode) );
			postNode->data = value;
			postNode->link = NULL;
			preNode->link = postNode;
			preNode = postNode;
		}
		tail = preNode;			
		//}
		//read command
		int commandCt, index, revIndex, j, k, val;
		commandCt = 0;
		fscanf(fptrR, "%d ", &commandCt);
		printf("we have %d command.\n", commandCt);
		fptrW = fopen("output_1.txt", "w");
		//deal command
		for(i = 0; i < commandCt; i++) {
			//printf("\nthe %d round.\n", i);
			c = fgetc(fptrR);
			//printf("%the %d command is start with : %c\n", i, c);
			if(c == 'a') {		//add
				fgetc(fptrR);fgetc(fptrR);fgetc(fptrR);
				fscanf(fptrR, "%d ", &value);
				//printf("in %d round, add %d\n", i, value);
				
				listPointer node;
				node = (listNode*)malloc(sizeof(listNode) );
				node->data = value;
				node->link = NULL;	//don't forget this step!
				nodeCt++;
				if(nodeCt == 1)	{	//if it is the first node
					head = node;
					tail = node;	
				}
				else {
					tail->link = node;
					tail = node;
				}
				//printf("after add command. we have %d node.\n", nodeCt);
			}
			else if(c == 'd') {	//del
				fgetc(fptrR);fgetc(fptrR);fgetc(fptrR);
				fscanf(fptrR, "%d ", &index);
				//printf("in %d round, del at %d\n", i, index);
				
				if(index == 1) { 	//if you want to del the first node
					head = head->link;
					nodeCt--;
				}
				else if(index > 1 && index <= nodeCt) {
					//printf("hahaha\n");
					listPointer temp, delNode;
					temp = head;
					for(j = 0; j < index-2; j++) {
						temp = temp->link;
					}
					delNode = temp->link;
					temp->link = delNode->link;
					if(index == nodeCt) {		//don't forget this step!!!
						tail = temp;
					}
					free(delNode);
					nodeCt--;
				}
				
				//printf("after del command. we have %d node.\n", nodeCt);
			}
			else if(c == 'i') {	//ins
				fgetc(fptrR);fgetc(fptrR);fgetc(fptrR);	//please notice the way i read file
				fscanf(fptrR, "%d ", &index);
				fscanf(fptrR, "%d ", &value);
				//printf("in %d round, after %d ins %d\n", i, index, value);
				listPointer node;
				
				if(index == 0) {	//if insert index 0
					node = (listNode*)malloc(sizeof(listNode) );
					node->data = value;
					node->link = NULL;
					head = node;
					tail = node;
					nodeCt++;
				}
				else if(index > 0 && index <= nodeCt) {	//草
					listPointer temp;
					temp = head;
					for(j = 0; j < index-1; j++) {
						temp = temp->link;
					}
					node = (listNode*)malloc(sizeof(listNode) );
					node->data = value;
					node->link = temp->link;	//don't forget this step!!!different from add
					temp->link = node;
					if(index == nodeCt) {		//don't forget this step!!!familiar with del
						tail = node;
					}
					nodeCt++;
				}
				/*else {
					listPointer node;
					node = (listNode*)malloc(sizeof(listNode) );
					node->data = value;
					node->link = NULL;	//don't forget this step!
					nodeCt++;					
					tail->link = node;
					tail = node;
				}*/
				
				//printf("after ins command. we have %d node.\n", nodeCt);
			}
			else if(c == 'm') {	//mul
				fgetc(fptrR);fgetc(fptrR);fgetc(fptrR);
				fscanf(fptrR, "%d ", &revIndex);	//please notice the way i read file
				fscanf(fptrR, "%d ", &value);
				//printf("in %d round, at %d - %d +1 mul %d\n", i,nodeCt, revIndex, value);
				index = nodeCt - revIndex + 1;
				listPointer temp;
				temp = head;
				if(index > 0 && index <= nodeCt) {
					for(j = 0; j < index-1; j++) {		//靠夭就他在搞 
						temp = temp->link;
					}
					val = temp->data;
					temp->data = val * value;
				}
				//printf("after mul command. we have %d node.\n", nodeCt);
			}
			else if(c == 'r') {	//rev
				fgetc(fptrR);fgetc(fptrR);fgetc(fptrR);
				fscanf(fptrR, "%d ", &value);
				//printf("in %d round, rev %d\n", i, value);				
				int *tmp, *tmpR;	
				int remainder = nodeCt % value;
				tmp = (int*)malloc(sizeof(int) * value);
				tmpR = (int*)malloc(sizeof(int) * (remainder));
				listPointer temp, tempR;
				temp = head;
				tempR = head;
				
				for(j = 0; j < nodeCt; j++) {
					if(j >= nodeCt - remainder) {	//剩下的地方 
						if(j == nodeCt - 1) {		//到最後了，反著丟回去 
							tmpR[j%value] = temp->data;
							
							for(k = 0; k < remainder; k++) {	//哭阿複製貼上也要檢查阿 
								tempR->data = tmpR[remainder -k-1];
								tempR = tempR->link;
							}
						}
						else {						//存列的值 
							tmpR[j%value] = temp->data;
							temp = temp->link;
						}
					}
					else {							//可以整除的地方 
						if((j+1) % value != 0) {	//存列的值
							tmp[j%value] = temp->data;						//重要!!! 
							//printf("%d\n", tmp[j%value]);
							temp = temp->link;
						}
						else {						//到最後了，反著丟回去 
							tmp[j%value] = temp->data;
							temp = temp->link;
							
							for(k = 0; k < value; k++) {
								tempR->data = tmp[value - k - 1];
								tempR = tempR->link;
							}
						}
					}
				}
			}
			else {				//show
				fgetc(fptrR);fgetc(fptrR);fgetc(fptrR);fgetc(fptrR);
				listPointer haha;
				haha = head;
				//int b=1;
				for(; haha; haha = haha->link) {
					//printf("%d %d	",b, haha->data);
					//b++;
					fprintf(fptrW,"%d ", haha->data);
				}
				//printf("\n");
				fprintf(fptrW,"\n");
			}
		}
	}
	fclose(fptrR);
	fclose(fptrW);
	return 0;
}







