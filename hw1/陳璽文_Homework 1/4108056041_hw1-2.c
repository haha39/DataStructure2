#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fptrR, *fptrW;

int main()
{
	fptrR = fopen("input_2.txt", "r");
	if(fptrR == NULL) {
		printf("fptrR error");
	}
	else {
		int data_num, i;
		fscanf(fptrR, "%d\n", &data_num);
		fptrW = fopen("output_2.txt", "w");
		for(i=0; i<data_num; i++) {
			int len, times, j, k, l, m, n;
			char c;
			fscanf(fptrR,"%d %d\n", &len, &times);
			int arr_even[len+2][len+2],arr_odd[len+2][len+2];	//not forget their size!
			
			//let them wrapped by 0 
			for(j=0; j<len+2; j++) {
				arr_even[0][j] = arr_odd[0][j] = 0;
				arr_even[len+1][j] = arr_odd[len+1][j] = 0;
			}
			for(j=0; j<len; j++) {
				arr_even[j+1][0] = arr_odd[j+1][0] = 0;
				arr_even[j+1][len+1] = arr_odd[j+1][len+1] = 0;
				for(k=0; k<len; k++) {
					c = getc(fptrR);
					arr_even[j+1][k+1] = arr_odd[j+1][k+1] = c - 48;
					fgetc(fptrR);//ignore ' ' and '\n'
				}
				arr_even[len+1][j] = arr_odd[len+1][j] = 0;
			}
			
			//take turns to make the generation happen on each other
			int neighbors=0, non_zero_item=0;
			for(l=0; l<times; l++) {
				non_zero_item = 0;
				if(l%2 == 0)	//the 0, 2, 4, 6.... times
				{
					for(j=0; j<len; j++) {
						for(k=0; k<len; k++) {
							neighbors = 0;
							for(m=-1; m<2; m++) {	//count the number of lving neighbors
								for(n=-1; n<2; n++) {
									if( m != 0 || n!= 0 ) {	//roghi master
										if(arr_even[j+1+m][k+1+n] == 1)
											neighbors++;
									}									
								}
							}
							//folling the rules
							if(arr_even[j+1][k+1] == 1) {
								if(neighbors == 0 || neighbors == 1)
									arr_odd[j+1][k+1] = 0;
								else if(neighbors == 2 || neighbors == 3) {
									non_zero_item++; 
									arr_odd[j+1][k+1] = 1;
								}
								else
									arr_odd[j+1][k+1] = 0;
							}
							else {
								if(neighbors == 3) {
									non_zero_item++;
									arr_odd[j+1][k+1] = 1;
								}
								else
									arr_odd[j+1][k+1] = 0;					
							}
						}
					}
				}
				else {	//the 1, 3, 5, 7....times
					for(j=0; j<len; j++) {
						for(k=0; k<len; k++) {
							neighbors = 0;
							for(m=-1; m<2; m++) {	//count the number of lving neighbors 
								for(n=-1; n<2; n++) {
									if( m != 0 || n!= 0 ) {
										if(arr_odd[j+1+m][k+1+n] == 1)
											neighbors++;
									}									
								}
							}
							//folling the rules
							if(arr_odd[j+1][k+1] == 1) {
								if(neighbors == 0 || neighbors == 1)
									arr_even[j+1][k+1] = 0;
								else if(neighbors == 2 || neighbors == 3) {
									non_zero_item++;
									arr_even[j+1][k+1] = 1;
								}
								else
									arr_even[j+1][k+1] = 0;
							}
							else {
								if(neighbors == 3) {
									non_zero_item++;
									arr_even[j+1][k+1] = 1;
								}
								else
									arr_even[j+1][k+1] = 0;					
							}
						}
					}					
				}
			}
			
			//直接跑雙層迴圈 直接印
			//printf("%d %d %d\n", len, len, non_zero_item);
			fprintf(fptrW,"%d %d %d\n", len, len, non_zero_item);
			if(times%2 == 0)
			{
				l = 0;
				for(j=0; j<len; j++) {
					for(k=0; k<len; k++) {
						if(l != non_zero_item) {
							neighbors = 0;
							if(arr_even[j+1][k+1] == 1) {
								l++;
								//printf("%d %d ", j, k);
								fprintf(fptrW,"%d %d ", j, k);
								for(m=-1; m<2; m++) {
									for(n=-1; n<2; n++) {
										if( m != 0 || n!= 0 ) {
											if(arr_even[j+1+m][k+1+n] == 1)
												neighbors++;
										}									
									}
								}
								//printf("%d\n", neighbors);	
								fprintf(fptrW,"%d\n", neighbors);								
							}
						}
						else {
							j = len;	//interesting and floraly idea, this way the outside loop will break, too
							break;
						}
					}
				}
			}
			else {
				l = 0;
				for(j=0; j<len; j++) {
					for(k=0; k<len; k++) {
						if(l != non_zero_item) {
							neighbors = 0;
							if(arr_odd[j+1][k+1] == 1) {
								l++;
								//printf("%d %d ", j, k);
								fprintf(fptrW,"%d %d ", j, k);
								for(m=-1; m<2; m++) {
									for(n=-1; n<2; n++) {
										if( m != 0 || n!= 0 ) {
											if(arr_odd[j+1+m][k+1+n] == 1)
												neighbors++;
										}									
									}
								}
								//printf("%d\n", neighbors);
								fprintf(fptrW,"%d\n", neighbors);		
							}
						}
						else {
							j = len+100;
							break;
						}
					}
				}
			}							
		}
	}

	fclose(fptrR);
	fclose(fptrW);
	system("PAUSE");
	return 0;
}





