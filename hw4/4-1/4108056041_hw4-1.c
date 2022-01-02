//should use priorty stack 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1

typedef struct Node *nodePointer;
typedef struct Node {
	int preCt;
	int postCt;
	int visitCt;
} Node;
//nodePointer head, nodeTmp;

FILE *fptrR, *fptrW;

int main()
{
	//open readFile
	fptrR = fopen("input_1.txt", "r");
	if(fptrR == NULL) {
		printf("fptrR error");
		exit(1);
	}
	fptrW = fopen("output_1.txt", "w");
	//read first line
	const int nodeNum, connectNum;
	fscanf(fptrR, "%d %d\n", &nodeNum, &connectNum);
	//printf("%d %d\n\n", nodeNum, connectNum);
	//default nodeArr and arrPost
	int i;
	int arrPost[nodeNum][nodeNum-1];
	Node nodeArr[nodeNum];
	for(i = 0; i < nodeNum; i++) {
		nodeArr[i].preCt = 0;
		nodeArr[i].postCt = 0;
		nodeArr[i].visitCt = 0;
	}
	//set nodeArr, rain watcher
	int preJob, postJob;
	for(i = 0; i < connectNum; i++) {
		fscanf(fptrR, "%d %d\n", &preJob, &postJob);
		//printf("%d %d\n", preJob, postJob);		
		nodeArr[postJob-1].preCt++;									//�����e�����X�Ӥu�@�o������ 
		
		arrPost[preJob-1][nodeArr[preJob-1].postCt] = postJob - 1;			//�O���L������A�򱵵ۥi�H���� 
		nodeArr[preJob-1].postCt++;										//�O���L�᭱���u�@�� 
	}
	//test
	/*for(i = 0; i < nodeNum; i++) {
		printf("%d  %d  %d\n", i+1, nodeArr[i].preCt, nodeArr[i].postCt);
	}*/ 
	//start!!
	int isCycle, ans[nodeNum], index, j;
	isCycle = 0;
	index = 0;
	while(TRUE) {
		isCycle = 1;
		for(i = 0; i < nodeNum; i++) {
			if(nodeArr[i].preCt == 0) {								//�N��L���e�m�@�~�Ҥw�����A�i�H���L
				if(nodeArr[i].visitCt == 0) {
					isCycle--;
					nodeArr[i].visitCt++;
					ans[index++] = i;
					for(j = 0; j < nodeArr[i].postCt; j++) {		//���e���򱵵۪��u�@�y�L�Ѳ�
						nodeArr[arrPost[i][j]].preCt--;
					}
					break;												//break for
				} 
			}
		}
		if(index == nodeNum) {
			for(i = 0; i < nodeNum; i++) {
				printf("%d  %d \n", i, ans[i]+1);
				fprintf(fptrW, "%d ", ans[i]+1);
			}
			break;														//break while
		}
		else if(isCycle == 1){											//�Y�]���@�����S���� 
			printf("not exist\n");
			fprintf(fptrW, "not exist\n");
			break;														//break while
		}
	}
	
	return 0;
}




