#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define MAXSIZE 70	//70�ئr�� 
#define MAXVALUE 10000000 

typedef struct treeNode *treePointer;
typedef struct treeNode {
	int feq;
	int lchild;
	int rchild;
	int parent;
	char data;
} treeNode;
treePointer treeTmp;

FILE *fptrR, *fptrW;

int main()
{
	//initialize 
	fptrR = fopen("input_2.txt", "r");
	if(fptrR == NULL) {
		printf("fptrR error");
		exit(1);
	}
	fptrW = fopen("output_2.txt", "w");
	while(TRUE) {
		int lineNum, len, arrN[MAXSIZE], i, isExist;
		char c, arrC[MAXSIZE];
		len = 0;
		/*for(i = 0; i < MAXSIZE; i++) {
			arrC[i] = '*';
			arrN[i] = 0;	
		}*/
		
		fscanf(fptrR, "%d\n", &lineNum);
		//printf("%d\n", lineNum);
		if(lineNum == 0) {		//����
			break;
		}
		while(lineNum) {
			c = fgetc(fptrR);
			
			if(c == '\n') {
				 lineNum--;
			}
			else {
				isExist = 0;
				for(i = 0; i < len; i++) {
					if(c == arrC[i]) {
						isExist = 1;
						break;
					}
				}
				if(isExist == 0) {						//�J��s�r�� 
					arrC[len] = c;
					arrN[len] = 1;
					len++;
				}
				else {									//�J���¦r�� 
					arrN[i]++;
				}
			}
		}
		//printf("len = %d\n", len);
		//��l�Ƹ��`�I
		const int Size = 2*len-1;
		treeNode node[Size];
		for(i = 0; i < Size; i++) {
			//node[i].data = '*';
			node[i].feq = MAXVALUE;
			node[i].parent = -1;
			//node[i].lchild = -1;
			//node[i].rchild = -1;
		}
		for(i = 0; i < len; i++) {
			node[i].data = arrC[i];
			node[i].feq = arrN[i];
			node[i].parent = -1;
			node[i].lchild = -1;
			node[i].rchild = -1;
			//printf("%c %d %c \n", node[i].data, node[i].feq, arrC[i]);
		}
		//�}�l���N�ҰҾ�
		int j, min1, min2, index1, index2;
		
		for(i = 0; i < len-1; i++) {
			min1 = min2 = MAXVALUE;			/* m1�Bm2���s���ӵL�����I�B���I�v�ȳ̤p����ӵ��I */
			index1 = index2 = 0;
			
			/* ��X�Ҧ����I���v�ȳ̤p�B'�L�����I'����ӵ��I�A�֦X�ä����@���G�e�� */
			for(j = 0; j < len + i; j++) {
				if(node[j].feq < min1 && node[j].parent == -1) {
					min2 = min1;
					index2 = index1;
					min1 = node[j].feq;
					index1 = j;
				}
				else if(node[j].feq < min2 && node[j].parent == -1) {
					min2 = node[j].feq;
					index2 = j;
				}
			}
			/* �]�w��쪺��Ӥl���I index1�Bindex2 �������I��T */
			node[index1].parent = len+i;
			node[index2].parent = len+i;
			node[len+i].feq = node[index1].feq + node[index2].feq;
			node[len+i].lchild = index1;
			node[len+i].rchild = index2;
		}
		//�}�l�ѽX�A��U�� 
		int total, tmp, bitLen;
		total = 0;
		
		for(i = 0; i < len; i++) {
			tmp = i;
			bitLen = 0;
			while(TRUE) {
				if(node[tmp].parent != -1) {
					bitLen++;
					tmp = node[tmp].parent;
				}
				else {								//��ܨ�ڤF�� 
					total += bitLen * node[i].feq;
					break;
				}
			}
		}
		
		printf("total = %d\n\n", total);
		fprintf(fptrW, "total = %d\n\n", total);
	}
	printf("wa ha!\n");
	fclose(fptrR);
	system("PAUSE");
	return 0;
}


