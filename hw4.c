#include <stdio.h>
#include<stdlib.h>

int a, b;
int max, min;// max =가장 큰 지수, min =가장 작은 지수
typedef struct node//다항식 첫번째리스트
{
	int coef;
	int expo;
	struct node *link;
}node;

typedef struct secondnode//다항식 결과값리스트
{
	int coef;
	int expo;
	struct secondnode *link1;
}secondnode;

typedef struct list
{
	node *headnode;
}list;

typedef struct secondlist
{
	secondnode *headnode2;
}secondlist;

list * nullnode(void)
{
	list *re;
	re = (list*)malloc(sizeof(list));
	re->headnode = NULL;
	return re;
};
secondlist * nullnode2(void)
{
	secondlist *re;
	re = (secondlist*)malloc(sizeof(secondlist));
	re->headnode2 = NULL;
	return re;
};
void scan(FILE *input_fp, FILE *output_fp, list **list1);//값입력 함수
void print(list **list);//받은값 출력함수
void insert(list **list1);// fscanf로 받은값 계산해서 리스트 생성과 동시에 값을 넣어주는 함수
void calculate(list **list, secondlist **secondlist);//모든 다항식을 덧셈하여 계수를 구하는 함수
void final(secondlist **secondlist, int a, int b);//계산이 끝난 다항식을 만드는 리스트
void print2(FILE *input_fp, FILE *output_fp, secondlist **secondlist);//다항식 출력리스트

int main()
{
	FILE *input_fp, *output_fp;
	input_fp = fopen("hw4.inp", "r");
	output_fp = fopen("hw4.out", "w");

	list *list = nullnode();//다항식 첫번째 헤드노드에 공백리스트 호출
	secondlist *list2 = nullnode2();//다항식 두번째 헤드노드에 공백리스트 호출
	scan(input_fp,output_fp,&list);
	calculate(&list,&list2);
	print(&list);
	print2(input_fp, output_fp, &list2);

	fclose(input_fp);
	fclose(output_fp);
	//free(list);

	/*while (headnode != NULL)
	{
	while (head)
	}*/
}

void scan(FILE *input_fp,FILE *output_fp,list **list1)//값입력
{
	char temp = 0;
	int temp1 = 1;

	for (;;)
	{
		fscanf(input_fp, "%c", &temp);
		if (temp == '+')
		{
			temp1 = 1;
			fscanf(input_fp, "\n");
		}
		else if (temp == '-')
		{
			temp1 = -1;
			fscanf(input_fp, "\n");
		}
		else if (temp == '*')
		{
			break;
		}
		else
		{
			fscanf(input_fp, "%d,%d]\n", &a, &b);
			a = temp1*a;
			insert(list1);
		}
	}

}

void insert(list **list)//리스트 생성 and 값 호출함수
{
	node *newnode = (node*)malloc(sizeof(node));
	newnode->link = NULL;
	newnode->coef = a;
	newnode->expo = b;
	node *temp = (*list)->headnode;
	if ((*list)->headnode == NULL) //헤드노드가 널인지 검사
	{
		(*list)->headnode = newnode;//널이면 노드 초기화
	}
	else
	{
		while (temp->link != NULL)
		{
			temp = temp->link;
		}
		temp->link = newnode;
	}
}

void print(list **list)//리스트 생성 and 값 호출함수
{
	node * temp = (*list)->headnode;

	while (1)
	{
		//printf("[%d, %d]\n", temp->coef, temp->expo);
		if (temp->link == NULL)
			break;
		temp = temp ->link;
	}
	//printf("*\n");
}

void calculate(list **list, secondlist **secondlist)
{
	max = 0, min = 100;
	int i;
	int co=0;//지수를 받는 변수

	node * temp = (*list)->headnode;

	while (1)//최대 최소 지수 구하는 반복문 
	{
		if (max < temp->expo)
		{
			max = temp->expo;
		}
		else
		{
			if (min > temp->expo)
			{
				min = temp->expo;
			}
		}

		if (temp->link == NULL)
			break;
		temp = temp->link;
	}

	for (i = max; i >= min; i--)
	{
		temp = (*list)->headnode;
		while (1)
		{
			if (temp->expo == i)
			{
				co += temp->coef;
			}
			if (temp->link == NULL)
				break;
			temp = temp->link;
		}
		final(secondlist,co,i);
		co = 0;

	}

}

void final(secondlist **secondlist,int a,int b)//계산값을 집어넣는 함수
{
	secondnode *newnode = (secondnode*)malloc(sizeof(secondnode));
	newnode->link1 = NULL;
	newnode->coef = a;
	newnode->expo = b;
	secondnode *temp = (*secondlist)->headnode2;
	if ((*secondlist)->headnode2 == NULL) //헤드노드가 널인지 검사
	{
		(*secondlist)->headnode2 = newnode;//널이면 노드 초기화
	}
	else
	{
		while (temp->link1 != NULL)
		{
			temp = temp->link1;
		}
		temp->link1 = newnode;
	}

}

void print2(FILE *input_fp, FILE *output_fp, secondlist **secondlist)//리스트 생성 and 값 호출함수
{
	secondnode * temp = (*secondlist)->headnode2;

	while (1)
	{
		if (temp->coef != 0)
			fprintf(output_fp,"[%d,%d]\n", temp->coef, temp->expo);
		if (temp->link1 == NULL)
			break;
		temp = temp->link1;
	}
	fprintf(output_fp,"*\n");
}