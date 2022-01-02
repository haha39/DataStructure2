#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1

const int nodeNum, orderNum;

typedef struct Node *nodePointer;
typedef struct Node {
	int number;
	int distance;
	nodePointer adj;
} Node;
nodePointer head, nodeTmp;
/*

int dfs(int [][], int [] , int [], int [], int , int , int );
void printfMin(int[], int ); 

, int nodeNum
				//printf("i : %d		dist[i] :�@%d		order[i] :�@%d\n", i, dist[i], order[i]);

*/



int dfs(nodePointer arr[nodeNum], int visit[nodeNum] , int dist[nodeNum], int order[nodeNum], int total, int vertex) {
	nodePointer tmp;
	
	//printf("vertex : %d\n", vertex);
	
	visit[vertex] = 1;
	
	for(tmp = arr[vertex]; tmp; tmp = tmp->adj) {
		if(visit[tmp->number] == -1) {											//�N��i�٨S���X�L 
			dist[tmp->number] = dist[vertex] + tmp->distance;					//�o�X�_�I��i���Z�� 
			total += dist[tmp->number] * 2 * order[tmp->number];				//�[��total�̭� 
			total = dfs(arr, visit, dist, order, total, tmp->number);			//���qi�}�l 
		}
	}
	
	//printf("total :�@%d\n", total);
	
	return total;
}

FILE *fptrR, *fptrW;

int main()
{
	//open readFile
	fptrR = fopen("input_2.txt", "r");
	if(fptrR == NULL) {
		printf("fptrR error");
		exit(1);
	}
	fptrW = fopen("output_2.txt", "w");
	//read first line
	fscanf(fptrR, "%d %d\n", &nodeNum, &orderNum);
	printf("%d %d\n\n", nodeNum, orderNum);
	//build Adjacency list 
	nodePointer nodeArr[nodeNum];
	//nodeArr = (Node*)malloc(sizeof(Node) * nodeNum);
	int i, j, a, b, Ecost;
	//default
	for(i = 0; i < nodeNum; i++) {
		nodeArr[i] = (Node*)malloc(sizeof(Node));
		nodeArr[i]->number = i;
		nodeArr[i]->distance = 0;
		nodeArr[i]->adj = NULL;
	}
	//read edge and setting
	for(i = 0; i < nodeNum - 1; i++) {
		fscanf(fptrR, "%d %d %d\n", &a, &b, &Ecost);
		//printf("%d %d %d\n", a, b, Ecost);
		
		nodePointer x, y;
		x = (Node*)malloc(sizeof(Node) );
		y = (Node*)malloc(sizeof(Node) );
		x->number = b-1;
		x->distance = Ecost;
		x->adj = NULL;
		y->number = a-1;
		y->distance = Ecost;
		y->adj = NULL;
		
		
		nodeTmp = nodeArr[a-1];
		while(TRUE) {
			if(nodeTmp->adj == NULL) {
				nodeTmp->adj = x;
				break;
			}
			nodeTmp = nodeTmp->adj;
		}
		
		nodeTmp = nodeArr[b-1];
		while(TRUE) {
			if(nodeTmp->adj == NULL) {
				nodeTmp->adj = y;
				break;
			}
			nodeTmp = nodeTmp->adj;
		}
	}
	//read order
	int n, money, order[nodeNum];
	//initialized
	for(i = 0; i < nodeNum; i++) {
		order[i] = 0;
	}
	//read order and setting
	for(i = 0; i < orderNum; i++) {
		fscanf(fptrR, "%d %d\n", &n, &money);
		//printf("%d %d\n", n, money);
		order[n-1] = money;
	}
	
	//initialize
	int visit[nodeNum], dist[nodeNum], minTotalCost[nodeNum];
	//dfs
	for(i = 0; i < nodeNum; i++) {			//�C�Ӹ`�I���n����]�@���A�o��L��minTotalCost 
		//remember to initialization
		for(j = 0; j < nodeNum; j++) {
			visit[j] = -1;
			dist[j] = 0;
		}
		minTotalCost[i] = dfs(nodeArr, visit, dist, order, 0, i);	//��n�ۤv���f���ܤ]�S�t
		//printf("%d  min : %d\n", i, minTotalCost[i]);
	}
	//find the minimum total cost
	int min = INT_MAX;
	for(i = 0; i < nodeNum; i++) {
		if(minTotalCost[i] < min) {
			min = minTotalCost[i];
		}
	}
	printf("%d\n", min);
	fprintf(fptrW, "%d\n", min);
	//find who has the minimum total cost
	for(i = 0; i < nodeNum; i++) {
		if(minTotalCost[i] == min) {
			printf("%d \n", i+1);
			fprintf(fptrW, "%d \n", i+1);
		}
	}
	
	return 0;
}



