#include<stdio.h>
#include<stdlib.h>

int main()
{
	FILE *input_fp, *output_fp;
	input_fp = fopen("hw3.inp", "r");
	output_fp = fopen("hw3.out", "w");
	int **AB;//AB���
	int **AC;//AC���
	int a, b;//a�� �� b�� ��
	int c, d;//c�� �� d�� ��
	int e, f;//e,f�� ���� ����
	int i, j, k, q=0;
	int x, y, z;
	char cha;
	int **BA;//AB�� ��ġ���
	int **BC;//BC���� �������

	//q = (int)malloc(sizeof(int));


	fscanf(input_fp, "%d %d %d", &a, &b, &e);
	AB = (int**)malloc(sizeof(int*)*a);
	for (i = 0; i < a; i++)
	{
		AB[i] = (int*)malloc(sizeof(int)*b);
	}
	for (i = 0; i < a; i++)
	{
		for (j = 0; j < b; j++)
		{
			AB[i][j] = 0;
		}
	}


	for (i = 0; i < e; i++)
	{
		fscanf(input_fp, "%d %d %d\n", &x, &y, &z);
		AB[x][y] = z;
	}

	fscanf(input_fp, "%c", &cha);
	fscanf(input_fp, "%d %d %d", &c, &d, &f);
	AC = (int**)malloc(sizeof(int*)*c);
	for (i = 0; i < c; i++)
	{
		AC[i] = (int*)calloc(d, sizeof(int));//calloc �ʱ�ȭ(���� 0���� �ʱ�ȭ���ش�)
	}
	/*for (i = 0; i < c; i++)
	{
	for (j = 0; j < d; j++)
	{
	AC[i][j] = 0;
	}
	}
	*/

	for (i = 0; i < f; i++)
	{
		fscanf(input_fp, "%d %d %d\n", &x, &y, &z);
		AC[x][y] = z;
	}
	fscanf(input_fp, "%c", &cha);
	//BA��� �����Ҵ�
	BA = (int**)malloc(sizeof(int*)*b);
	for (i = 0; i < b; i++)
	{
		BA[i] = (int*)malloc(sizeof(int)*a);
	}
	//BA��ġ��� ����
	for (i = 0; i < a; i++)
	{
		for (j = 0; j < b; j++)
		{
			BA[j][i] = AB[i][j];
		}
	}
	//BC��� �����Ҵ�
	BC = (int**)malloc(sizeof(int*)*b);
	for (k = 0; k < b; k++)
	{
		BC[k] = (int*)calloc(d,sizeof(int));
	}
	//BA��� *AC���
	for (i = 0; i < a; i++)
	{
		for (j = 0; j < b; j++)
		{
			if (AB[i][j] == 1)
			{
				for (k = 0; k < d; k++)
				{
					if (AC[i][k] == 1)
					{
						BC[j][k] = 1;
					}
				}
			}
		}
	}
	//������ �����
	for (i = 0; i < b; i++)
	{
		for (j = 0; j < d; j++)
		{
			if (BC[i][j] == 1)
			{
				q += 1;
			}
		}
	}
	fprintf(output_fp, "%d %d %d\n", b, d, q);
	for (i = 0; i < b; i++)
	{
		for (j = 0; j < d; j++)
		{
			if (BC[i][j] == 1)
			{
				fprintf(output_fp, "%d %d %d\n", i, j, BC[i][j]);
			}
		}
	}
	fprintf(output_fp, "*");
	fclose(input_fp);
	fclose(output_fp);

}