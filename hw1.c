#include <stdio.h>
#include<stdlib.h>
int main()
{
	FILE *input_fp, *output_fp;
	int num = 0;
	int *sum;
	
	int odd = 0, even = 0;
	int odd_cnt = 0, even_cnt = 0;

	char star = ' ';
	float odd_ave = 0, even_ave = 0;

	fopen_s(&input_fp,"hw1.inp", "r");
	fopen_s(&output_fp,"hw1.out", "w");
	
	/*
	if ((input_fp = fopen("hw1.inp", "r")) == NULL){
		fprintf(stderr, "can't open %s\n", "program1.inp");
	}

	if ((output_fp = fopen("hw1.out", "w")) == NULL){
		fprintf(stderr, "can't open %s\n", "1.out");
	}

	if ((sum = (int *)malloc(sizeof(int) * 3)) == NULL)
	{
		fprintf(stderr, "memory allocation error %s\n", "sum");
	}*/


	for (;;){
		fscanf_s(input_fp, "%d", &num);

		if (star != ' '){
			break;
		}

		else if (num % 2 == 0){
			even += num;
			even_cnt++;
		}
		else{
			odd += num;
			odd_cnt++;
		}

		fscanf_s(input_fp, "%c", &star);

	}


	odd_ave = (float)odd / odd_cnt;
	even_ave = (float)even / even_cnt;

	fprintf(output_fp, "odd %d %.1f\n%", odd_cnt, odd_ave);
	fprintf(output_fp, "even %d %.1f\n", even_cnt, even_ave);
	fprintf(output_fp, "*\n");

	fclose(input_fp);
	fclose(output_fp);
	//free(sum);

	return 0;
}