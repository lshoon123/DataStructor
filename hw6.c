#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int check1 = 0;
int check2 = 0;

typedef struct queue
{
	int queue[10];
	int front, rear;
}queue;
queue *creatqueue()
{
	queue *newQ;
	newQ = (queue*)malloc(sizeof(queue));
	newQ->front = -1;
	newQ->rear = -1;
	return newQ;
}
void restart(queue *que)
{
	int i;

	for (i = 0; i<10; i++)
	{
		que->queue[i] = 0;
	}
}

void input1(FILE *input, queue *que);
void result(FILE *output,queue *que1, queue *que2, int check1, int check2, char a[20], char b[20]);
void enqueue(queue *que, int num);
int dequeue(queue *que);
void compare(queue *que1, queue *que2);

int main()
{
	FILE *input = fopen("hw6.inp", "r");
	FILE *output = fopen("hw6.out", "w");

	char a[20] = { '\o', };
	char b[20] = { '\o', };
	char c;
	int i = 0;

	queue *que1 = creatqueue();
	restart(que1);
	queue *que2 = creatqueue();
	restart(que1);

	for (;;)
	{
		fscanf(input, "%c", &c);
		if (c == '\n')
		{
			break;
		}
		else
		{
			a[i] = c;
			i++;
		}
	}
	input1(input, que1);
	i = 0;
	for (;;)
	{
		fscanf(input, "%c", &c);
		if (c == '\n')
		{
			break;
		}
		else
		{
			b[i] = c;
			i++;
		}
	}
	input1(input, que2);
	compare(que1, que2);
	result(output,que1,que2,check1,check2,a,b);


	
	fprintf(output,"*");
	



	fclose(input);
	fclose(output);

}

void input1(FILE *input, queue *que)
{
	int num;
	char cc = ' ';
	int i = 0;
	while (cc != '\n')
	{
		fscanf(input, "%d%c", &num, &cc);
		enqueue(que, num);
		i++;
	}
}
void enqueue(queue *que, int num)
{
		que->rear = (que->rear + 1) % 10;
		que->queue[que->rear] = num;
}

int dequeue(queue *que)
{
		que->front = (que->front + 1) % 10;
		return que->queue[que->front];
}

void compare(queue *que1, queue *que2)
{
	while (1)
	{
		int as = dequeue(que1);
		int bs = dequeue(que2);
		if (as == bs)
		{
		}
		else if (as < bs)
		{
			enqueue(que2, bs);
			check2++;
		}
		else
		{
			enqueue(que1, as);
			check1++;
		}
		if (que1->rear == que1->front || que2->rear == que2->front)
		{
			break;
		}

	}
}

void result(FILE *output,queue *que1, queue *que2, int check1,int check2, char a[20],char b[20])
{
	int i = 0;
	int a1, b1;
	if (check1>check2)
	{
		for (i = 0; i < strlen(a); i++)
		{
			fprintf(output,"%c", a[i]);
		}
		fprintf(output,"\n");
		while (1)
		{
			a1 = dequeue(que1);
			
			fprintf(output, "%d ", a1);
			if (que1->rear == que1->front)
			{
				break;
			}
		}
		fprintf(output, "\n");
	}
	else if (check1<check2)
	{
		for (i = 0; i < strlen(b); i++)
		{
			fprintf(output, "%c", b[i]);
		}
		fprintf(output, "\n");
		while (1)
		{
			b1=dequeue(que2);
			fprintf(output, "%d ", b1);
			if (que2->rear == que2->front)
			{
				break;
			}
		}
		fprintf(output, "\n");
	}
	else
	{
		fprintf(output, "DRAW\n");
	}
}