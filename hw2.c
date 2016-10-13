#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define _CRT_SECURE_NO_WARNINGS

void minus(FILE *output_fp, float a, float b, float c, float d);
void plus(FILE *output_fp, float a, float b, float c, float d);
void multi(FILE *output_fp, float a, float b, float c, float d);
void division(FILE *output_fp, float a, float b, float c, float d);

typedef struct bak{
	float a;
	float b;
	float c;
	float d;
}bak;

int main()
{
	FILE *input_fp, *output_fp;
	input_fp = fopen("hw2.inp", "r");
	output_fp = fopen("hw2.out", "w");
	int hm = 0; //받고싶은 복소수의 개수
	int i;
	bak *bak1;
	int hm2 = hm*2;

	fscanf(input_fp, "%d\n", &hm);
	bak1 = (bak*)malloc(sizeof(bak)*hm2);

	for (i = 0; i < hm; i++)
	{
		fscanf(input_fp, "[%f,%f] [%f,%f]\n", &bak1[i].a, &bak1[i].b, &bak1[i].c, &bak1[i].d);
	}

	for (i = 0; i < hm; i++)
	{
		plus(output_fp, bak1[i].a, bak1[i].b, bak1[i].c, bak1[i].d);
		minus(output_fp, bak1[i].a, bak1[i].b, bak1[i].c, bak1[i].d);
		multi(output_fp, bak1[i].a, bak1[i].b, bak1[i].c, bak1[i].d);
		division(output_fp, bak1[i].a, bak1[i].b, bak1[i].c, bak1[i].d);
		fprintf(output_fp, "\n");
		//printf("\n");
	}
	fprintf(output_fp, "*");
	//printf("*");

	fclose(input_fp);
	fclose(output_fp);
	free(bak1);
	return 0;
}

void plus(FILE *output_fp, float a, float b, float c, float d)
{
	float plus = a + c;
	float plus1 = b + d;
	plus *= 100;
	plus1 *= 100;
	fprintf(output_fp, "[%.2lf,%.2lf] ", floor(plus) / 100, floor(plus1) / 100);
	//printf("[%.2lf,%.2lf] ", floor(plus) / 100, floor(plus1) / 100);
}

void minus(FILE *output_fp, float a, float b, float c, float d)
{
	float minus = a - c;
	float minus1 = b - d;
	minus *= 100;
	minus1*= 100;
	fprintf(output_fp, "[%.2lf,%.2lf] ", floor(minus) / 100, floor(minus1) / 100);
	//printf("[%.2lf,%.2lf] ", floor(minus) / 100, floor(minus1) / 100);
}

void multi(FILE *output_fp, float a, float b, float c, float d)
{
	float multiple = a * c - (b*d);
	float multiple1 = b*c + a*d;
	multiple *= 100;
	multiple1 *= 100;
	fprintf(output_fp, "[%.2lf,%.2lf] ", floor(multiple) / 100, floor(multiple1) / 100);
	//printf("[%.2lf,%.2lf] ", floor(multiple) / 100, floor(multiple1) / 100);
}

void division(FILE *output_fp, float a, float b, float c, float d)
{
	float division = a*c + -(b*-d);
	float division1 = b*c + (a*-d);
	float division2 = c*c - (d*-d);
	if (division2 != 0)
	{
		division = (division / division2) * 100;
		division1 = (division1 / division2) * 100;
		fprintf(output_fp, "[%.2lf,%.2lf] ", floor(division) / 100, floor(division1) / 100);
		//printf("[%.2lf,%.2lf] ", floor(division) / 100, floor(division1) / 100);
	}
	else
	{
		fprintf(output_fp, "0");
		printf(output_fp, "0");
	}
}